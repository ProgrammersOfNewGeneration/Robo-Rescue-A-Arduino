#ifndef bluetooth_h
#define bluetooth_h

#include "Arduino.h"
#include <SoftwareSerial.h>


class Bluetooth{
private:
    int rxPin = 2;
    int txPin = 3;
    SoftwareSerial *btSerial = new SoftwareSerial(2, 3);
    
public:
    int getrxPin();
    void setrxPin(int rx);
    int gettxPin();
    void settxPin(int tx);
    void configuraBluetooth();
    Bluetooth();
    Bluetooth(int r, int t);
    char Ler();
    void Enviar(char c);
};


#endif
