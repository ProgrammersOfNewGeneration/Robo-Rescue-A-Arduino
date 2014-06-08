#include <SoftwareSerial.h>
#include "bluetooth.h"
#include "motor.h"
#include "ultrassom.h"



Ultrassom *u = new Ultrassom();
//Motor *m = new Motor();
// Bluetooth *blue = new Bluetooth();

void setup(){
	Serial.begin(9600);
	// blue->configuraBluetooth();
	// m->irFrente();
	// m->setVelocidade(90);
}
void loop(){
	Serial.println(u->lerDistancia());
	delay(500);
	// m->irFrente();
	// delay(1000);
	// m->irDireita();
	// delay(1000);
	// m->irEsquerda();
	// delay(1000);
	// m->irRe();
	// delay(1000);
	// m->irParar();
	// delay(1000);
	// Serial.write(blue->Ler());
	// delay(500);

	// if(Serial.available()){
	// 	blue->Enviar(Serial.read());
	// }
}