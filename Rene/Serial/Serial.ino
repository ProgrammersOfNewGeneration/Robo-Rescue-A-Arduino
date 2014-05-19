#include <SoftwareSerial.h>

const int rxPin = 2;
const int txPin = 3;
SoftwareSerial btSerial(rxPin, txPin);

void configuraBluetooth() {
  Serial.println("Configurando para 9600");
  btSerial.write("AT+BAUD4");
  delay(1100);
  while (btSerial.available()) 
    Serial.write(btSerial.read());
    
  Serial.println("\nConfigurando para NOME = \"unesp-cti\"");
  btSerial.write("AT+NAMEunesp-cti");
  delay(1100);
  while (btSerial.available()) 
    Serial.write(btSerial.read());
    
  Serial.println("\nConfigurando PIN para 9889");
  btSerial.write("AT+PIN9889");
  delay(1100);
  while (btSerial.available()) 
    Serial.write(btSerial.read());
     
  Serial.println("\nVersao do bluetooth");
  btSerial.write("AT+VERSION");
  delay(1100);
  while (btSerial.available()) 
    Serial.write(btSerial.read());
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Iniciando...");

  // set the data rate for the SoftwareSerial port
  pinMode(txPin, OUTPUT);  
  pinMode(rxPin, INPUT);    
  btSerial.begin(9600);
      
  configuraBluetooth();
  Serial.println("\nConfigurado!");
}

char c;
void loop() {
  if (btSerial.available()) {
    char c = btSerial.read();
    //Serial.print(".");
    Serial.write(c);
    //Serial.print(c, HEX);
    //delay(50);
    return;
  }
  
  if (Serial.available()) {
    char c = Serial.read();
    //if (c == '#') {
      //btSerial.write("\r\n");
      //Serial.print("#\n");
    //} else
      btSerial.write(c);
    //Serial.print(" ");
    //Serial.print(c);
    //Serial.print(c, HEX);
    //delay(50);
    return;
  }
}

