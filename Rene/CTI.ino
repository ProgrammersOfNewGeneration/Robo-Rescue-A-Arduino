
#include <Servo.h> 
// #include <NewPing.h>

Servo myservo;
int angulo = 90;
byte   vOdo[]={0,  1,  2,  3};
byte	kp[8]={1,  10,  8,  6},
	kr[8]={1, 16, 16, 16},	// relacao entre as rodas
	kv[8]={0, 50, 62, 74};	// integral inicial

// Sonar
#define TRIGGER_PIN  A5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
// NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
// Servo
#define SERVO_PIN   4
//MOTORES
#define MOTOR1_A    6
#define MOTOR1_B    7
#define MOTOR1_PWM  5
#define MOTOR2_A    8
#define MOTOR2_B    9
#define MOTOR2_PWM  11
//Sensores opticos
#define A0_74LS138_PIN  A2
#define A1_74LS138_PIN  A1
#define A2_74LS138_PIN  A0
#define ANALOG          A3
//Numero de cada sensor na rotina
const int SENSOR_0        = 0;
const int SENSOR_1        = 1;
const int SENSOR_2        = 2;
const int SENSOR_3        = 3;
const int SENSOR_4        = 4;
const int SENSOR_RODA_ESQ = 5;
const int SENSOR_RODA_DIR = 6;
//Contador de giros do motor
const int VARIACAO_IGNORAVEL = 600;
byte contOdoEsq = 0;//contador de pulsos, zerado a cada inicio de contagem (a cada novo comando)
byte contOdoDir = 0;
char ultContagemOdoEsq = 0;//ultima contagem desde a ultima medida
char ultContagemOdoDir = 0;

int cont = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  pinMode(A0, OUTPUT);     
  pinMode(A1, OUTPUT);     
  pinMode(A2, OUTPUT);     
  myservo.attach(SERVO_PIN);
  myservo.write(90);

  pinMode(MOTOR1_PWM, OUTPUT);      
  pinMode(MOTOR1_A, OUTPUT);      
  pinMode(MOTOR1_B, OUTPUT);      
  pinMode(8, OUTPUT);      
  pinMode(9, OUTPUT);      
  pinMode(MOTOR2_PWM, OUTPUT);
}

boolean dirEsq = false, dirDir = false;
int vBaseDir, velBaseDir = 1;// de -3 a 3
int vBaseEsq, velBaseEsq = 1;// de -3 a 3
int erroEsq = 0, erroDir = 0;
int difRodas = 0, difRodasEsq, difRodasDir;
int vMax, velEsq, velDir;

// the loop routine runs over and over again forever:
void loop() {
  verificaSensorRodaEsq();
  verificaSensorRodaDir();
  //analogWrite(MOTOR1_PWM, 100);   
  //analogWrite(MOTOR2_PWM, 100); 
  //digitalWrite(MOTOR1_A, LOW);
  //digitalWrite(MOTOR1_B, HIGH);  
  //digitalWrite(MOTOR2_A, HIGH);
  //digitalWrite(MOTOR2_B, LOW);  

  //unsigned int uS = sonar.ping();
  //Serial.print("Distancia: ");
  //Serial.println(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)

  if (angulo > 181) {
    angulo = 0;
  }
  //myservo.write(angulo);
  //if (alcancou1000MiliSegs()) {
   // angulo+=20;
  //}
  
  if (alcancou100MiliSegs()) {
    ultContagemOdoEsq =  contOdoEsq;
    contOdoEsq = 0;
    ultContagemOdoDir =  contOdoDir;
    contOdoDir = 0;
    
    Serial.print("C:");
    Serial.print((int)ultContagemOdoEsq);
    Serial.print(",");
    Serial.print((int)ultContagemOdoDir);
    
    if (velBaseEsq<0) {
      dirEsq =  1;
      vBaseEsq = -velBaseEsq;
    } else {
      dirEsq =  0;
      vBaseEsq = velBaseEsq;
    }
    if (velBaseDir<0) {
      dirDir =  1;
      vBaseDir = -velBaseDir;
    } else {
      dirDir =  0;
      vBaseDir = velBaseDir;
    }
    
    Serial.print("V:");
    Serial.print(dirEsq);
    Serial.print(vBaseEsq);
    Serial.print("V:");
    Serial.print(dirDir);
    Serial.print(vBaseDir);
    
    erroEsq = ((int)vOdo[vBaseEsq]-ultContagemOdoEsq)<<2;//deslocamento para casas decimais
    erroDir = ((int)vOdo[vBaseDir]-ultContagemOdoDir)<<2;//deslocamento para casas decimais
    
    Serial.print("E:");
    Serial.print(erroEsq);
    Serial.print(",");
    Serial.print(erroDir);
    
    difRodas=((int)vBaseEsq*ultContagemOdoDir-(int)vBaseDir*ultContagemOdoEsq)<<4;//deslocamento para casas decimais
        //difRodas=0;
    difRodasDir = -difRodas/kr[vBaseDir];
    difRodasEsq =  difRodas/kr[vBaseEsq];
        
    erroEsq+=difRodasEsq;
    erroDir+=difRodasDir;
    Serial.print(" E:");
    Serial.print(erroEsq);
    Serial.print(",");
    Serial.print(erroDir);
    
    velEsq=((int)kp[vBaseEsq]*erroEsq);//deslocamento para casas decimais
    velDir=((int)kp[vBaseDir]*erroDir);//deslocamento para casas decimais
    
    velEsq+=kv[vBaseEsq];
    velDir+=kv[vBaseDir];
    
    if (velEsq<0) {
      velEsq = -velEsq;
      dirEsq = !dirEsq;
      velEsq = 0;
    }
    if (velDir<0) {
      velDir = -velDir;
      dirDir = !dirDir;
      velDir = 0;
    }
    
//    if (erroEsq<0)
//      erroEsq = 0;
//    if (erroDir<0)
//      erroDir = 0;
    if (velEsq<0)
      velEsq = 0;
    if (velDir<0)
      velDir = 0;
      
    vMax = max(velEsq, velDir);
    
    if (vMax>250) {
      velEsq = ((250>>1)*(unsigned)velEsq/vMax)<<1;
      velDir = ((250>>1)*(unsigned)velDir/vMax)<<1;
    }

    Serial.print("V:");
    Serial.print(velEsq);
    Serial.print(",");
    Serial.println(velDir);
    
    if (vBaseEsq!=0) {
      analogWrite(MOTOR1_PWM, velEsq);
      if (dirEsq) {
        digitalWrite(MOTOR1_A, LOW);
        digitalWrite(MOTOR1_B, HIGH);
      } else {
        digitalWrite(MOTOR1_A, HIGH);
        digitalWrite(MOTOR1_B, LOW);
      }
    } else {
      analogWrite(MOTOR1_PWM, 255);//Parada Rapida L298
      digitalWrite(MOTOR1_A, LOW);
      digitalWrite(MOTOR1_B, LOW);
    }

    if (vBaseDir!=0) {
      analogWrite(MOTOR2_PWM, velDir);
      if (dirDir) {
        digitalWrite(MOTOR2_A, LOW);
        digitalWrite(MOTOR2_B, HIGH);
      } else {
        digitalWrite(MOTOR2_A, HIGH);
        digitalWrite(MOTOR2_B, LOW);
      }
    } else {
      analogWrite(MOTOR2_PWM, 255);
      digitalWrite(MOTOR2_A, LOW);
      digitalWrite(MOTOR2_B, LOW);
    }
  }

  /*
  if (alcancou1000MiliSegs()) {
    int sensorValue = leSensorOptico(cont);
    Serial.print(" "); 
    Serial.print(sensorValue);
    Serial.print(" "); 
    if (cont++>5) {
      Serial.print(int(ultContagemOdoEsq));
      Serial.print(" ");
      Serial.print(int(ultContagemOdoDir));
      Serial.println("");
      cont=0;
    }
  }
  */
  /*sensorValue = leSensorOptico(SENSOR_RODA_ESQ);
  Serial.print(sensorValue); 
    Serial.print(" "); 
*/
//  delay(200);        // delay in between reads for stability
}

unsigned short int leSensorOptico(byte n) {
  digitalWrite(A2_74LS138_PIN, n & 4 ? HIGH : LOW); 
  digitalWrite(A1_74LS138_PIN, n & 2 ? HIGH : LOW); 
  digitalWrite(A0_74LS138_PIN, n & 1 ? HIGH : LOW);    
  delay(2);        // delay para estabilidade da leitura do ADC
  return analogRead(ANALOG);
}

boolean alcancou1000MiliSegs() {
  static long time = millis();
  if ((int)(millis() - time) >= 1000) {
    time = millis();
    return true;
  }
  return false;
}

boolean alcancou100MiliSegs() {
  static long time = millis();
  if ((int)(millis() - time) >= 100) {
    time = millis();
    return true;
  }
  return false;
}

boolean alcancou200MiliSegs() {
  static long time = millis();
  if ((int)(millis() - time) >= 200) {
    time = millis();
    return true;
  }
  return false;
}

void verificaSensorRodaEsq() {
  static boolean subindo = true;
  static unsigned long tempoInicio = 0;
  static int valMin = 0;
  static int valMax = 0;

  int valAtual = leSensorOptico(SENSOR_RODA_ESQ);

  unsigned long tempoAtual = millis();
  //Serial.print(subindo); 
  //Serial.print(valAtual); 
  if (subindo) {
    if (valAtual > valMax)
      valMax = valAtual;
    else if (valMax - valAtual > VARIACAO_IGNORAVEL) {
      subindo = false;
      valMin = valMax;
      contOdoEsq++;
      tempoInicio = tempoAtual;
    }
  } else {
    if (valAtual < valMin)
      valMin = valAtual;
    else if (valAtual - valMin > VARIACAO_IGNORAVEL) {
      subindo = true;
      valMax = valMin;
      contOdoEsq++;
      tempoInicio = tempoAtual;
    }
  }
}

void verificaSensorRodaDir() {
  static boolean subindo = true;
  static unsigned long tempoInicio = 0;
  static int valMin = 0;
  static int valMax = 0;

  int valAtual = leSensorOptico(SENSOR_RODA_DIR);

  unsigned long tempoAtual = millis();
  //Serial.print(subindo); 
  //Serial.print(", ");
  //Serial.println(valAtual); 
  if (subindo) {
    if (valAtual > valMax)
      valMax = valAtual;
    else if (valMax - valAtual > VARIACAO_IGNORAVEL) {
      subindo = false;
      valMin = valMax;
      contOdoDir++;
      tempoInicio = tempoAtual;
    }
  } else {
    if (valAtual < valMin)
      valMin = valAtual;
    else if (valAtual - valMin > VARIACAO_IGNORAVEL) {
      subindo = true;
      valMax = valMin;
      contOdoDir++;
      tempoInicio = tempoAtual;
    }
  }
}
