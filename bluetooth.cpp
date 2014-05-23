#include "bluetooth.h"

int main(){
    char c;
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
