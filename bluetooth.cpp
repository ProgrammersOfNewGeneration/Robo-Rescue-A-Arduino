#include "bluetooth.h"

int Bluetooth::getrxPin(){
    return rxPin;
}

void Bluetooth::setrxPin(int rx){
    rxPin = rx;
}

int Bluetooth::gettxPin(){
    return txPin;
}

void Bluetooth::settxPin(int tx){
    txPin = tx;
}

void Bluetooth::configuraBluetooth(){
    btSerial = new SoftwareSerial(rxPin, txPin);
    pinMode(txPin, OUTPUT);
    pinMode(rxPin, INPUT);

   // // btSerial->write("U,9600");
   //  btSerial->begin(9600); 
   //  // Configurando para 9600
   //  btSerial->write("AT+BAUD4");

   //  // // Configurando para NOME = \"unesp-cti\"
   //  btSerial->write("AT+NAMErobo-tcc");

   //  // // Configurando PIN para 9889
   //  btSerial->write("AT+PIN666");

   //  // // Versao do bluetooth
   //  btSerial->write("AT+VERSION");
    btSerial->begin(9600);

    Serial.println("Configurando para 9600");
    btSerial->write("AT+BAUD4");
    delay(1100);
    while (btSerial->available()) 
    Serial.write(btSerial->read());

    Serial.println("\nConfigurando para NOME = \"Robo-TCC\"");
    btSerial->write("AT+NAMERobo-TCC");
    delay(1100);
    while (btSerial->available()) 
    Serial.write(btSerial->read());

    Serial.println("\nConfigurando PIN para 6666");
    btSerial->write("AT+PIN6666");
    delay(1100);
    while (btSerial->available()) 
    Serial.write(btSerial->read());

    Serial.println("\nVersao do bluetooth");
    btSerial->write("AT+VERSION");
    delay(1100);
    while (btSerial->available()) 
    Serial.write(btSerial->read());
}

Bluetooth::Bluetooth(){
    setrxPin(2);
    settxPin(3);
    //ConfiguraBluetooth();
}

Bluetooth::Bluetooth(int r, int t){
    setrxPin(r);
    settxPin(t);
    configuraBluetooth();
}

char Bluetooth::Ler(){
    if(btSerial->available())
        return btSerial->read();
    
}

void Bluetooth::Enviar(char c){
    btSerial->write(c);
}