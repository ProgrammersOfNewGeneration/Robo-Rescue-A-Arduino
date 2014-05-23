#ifndef bluetooth_h
#define bluetooth_h

#include "Arduino.h"
#include "SoftwareSerial"

class Bluetooth{
private:
    int rxPin;
    int txPin;
    SoftwareSerial btSerial(rxPin,txPin);
public:
    int getrxPin();
    void setrxPin(int rx);
    int gettxPin();
    void settxPin(int tx);
    void ConfiguraBluetooth();
    Bluetooth();
    Bluetooth(int r, int t);
};

Bluetooth::getrxPin(){
    return rxPin;
}

Bluetooth::setrxPin(int rx){
    rxPin = rx;
}

Bluetooth::gettxPin(){
    return txPin;
}

Bluetooth::settxPin(int tx){
    txPin = tx;
}

Bluetooth::ConfiguraBluetooth(){
    // Configurando para 9600
    btSerial.write("AT+BAUD4");
    delay(1100);
    while (btSerial.available())
        Serial.write(btSerial.read());

    // Configurando para NOME = \"unesp-cti\"
    btSerial.write("AT+NAMEunesp-cti");
    delay(1100);
    while (btSerial.available())
        Serial.write(btSerial.read());

    // Configurando PIN para 9889
    btSerial.write("AT+PIN9889");
    delay(1100);
    while (btSerial.available())
        Serial.write(btSerial.read());

    // Versao do bluetooth
    btSerial.write("AT+VERSION");
    delay(1100);
    while (btSerial.available())
        Serial.write(btSerial.read());
}

Bluetooth::Bluetooth(){
    setrxPin(2);
    settxPin(3);
    Serial.begin(9600);
    pinMode(txPin, OUTPUT);
    pinMode(rxPin, INPUT);
    btSerial.begin(9600);
    ConfiguraBluetooth();
}

Bluetooth::Bluetooth(int r, int t){
    setrxPin(r);
    settxPin(t);
    Serial.begin(9600);
    pinMode(txPin, OUTPUT);
    pinMode(rxPin, INPUT);
    btSerial.begin(9600);
    ConfiguraBluetooth();
}

#endif
