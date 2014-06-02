#include <SoftwareSerial.h>
#include "bluetooth.h"


Bluetooth *blue = new Bluetooth();

void setup(){
	Serial.begin(9600);
	blue->configuraBluetooth();
}
void loop(){
	Serial.write(blue->Ler());
	delay(500);

	if(Serial.available()){
		blue->Enviar(Serial.read());
	}
}