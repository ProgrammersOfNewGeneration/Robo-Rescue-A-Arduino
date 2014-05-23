
#include <Servo.h> 
#include <NewPing.h>

Servo myservo;
int angulo = 90;

// Sonar
#define TRIGGER_PIN  A5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
// Servo
#define SERVO_PIN   4
//MOTORES
#define MOTOR1_A    6
#define MOTOR1_B    7
#define MOTOR1_PWM  5
#define MOTOR2_A    8
#define MOTOR2_B    9
#define MOTOR2_PWM  1
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
const int VARIACAO_IGNORAVEL = 15;
byte contOdoEsq = 0;//contador de pulsos, zerado a cada inicio de contagem (a cada novo comando)
byte contOdoDir = 0;
char ultContagemOdoEsq = 0;//ultima contagem desde a ultima medida
char ultContagemOdoDir = 0;

int cont = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A0, OUTPUT);     
  pinMode(A1, OUTPUT);     
  pinMode(A2, OUTPUT);     
  myservo.attach(SERVO_PIN);

  pinMode(MOTOR1_PWM, OUTPUT);      
  pinMode(MOTOR1_A, OUTPUT);      
  pinMode(MOTOR1_B, OUTPUT);      
  pinMode(8, OUTPUT);      
  pinMode(9, OUTPUT);      
  pinMode(MOTOR2_PWM, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  verificaSensorRodaEsq();
  verificaSensorRodaDir();
  analogWrite(MOTOR1_PWM, 50);   
  analogWrite(MOTOR2_PWM, 50); 
  digitalWrite(MOTOR1_A, LOW);
  digitalWrite(MOTOR1_B, HIGH);  
  digitalWrite(MOTOR2_A, HIGH);
  digitalWrite(MOTOR2_B, LOW);  

  unsigned int uS = sonar.ping();
  //Serial.print("Distancia: ");
  //  Serial.println(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)

  if (angulo > 181) {
    angulo = 0;
  }
  myservo.write(angulo);
  //angulo+=20;
  
  if (alcancou1000MiliSegs()) {
    ultContagemOdoEsq = contOdoEsq;
    contOdoEsq = 0;
    ultContagemOdoDir = contOdoDir;
    contOdoDir = 0;
  //}

  //if (alcancou200MiliSegs()) {
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
  Serial.print(subindo); 
//  Serial.print(valAtual); 
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