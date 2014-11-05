#ifndef bluetooth_h
#define bluetooth_h

#include "Arduino.h"
#include <SoftwareSerial.h>


class Bluetooth{
private:
    int rxPin;
    int txPin;
    SoftwareSerial *btSerial;
    char msg[1024];
    void read();
    
public:
    int getrxPin();
    void setrxPin(int rx);
    int gettxPin();
    void settxPin(int tx);
    void configuraBluetooth();
    Bluetooth();
    Bluetooth(int r, int t);
    String Ler();
    void Enviar(char c[]);
};


#endif
