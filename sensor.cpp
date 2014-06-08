#include "sensor.h"

Sensor::Sensor(){
	configuraPinos();
}

void Sensor::configuraPinos(){
	pinMode(A0_74LS138_PIN, OUTPUT);     
  	pinMode(A1_74LS138_PIN, OUTPUT);     
  	pinMode(A2_74LS138_PIN, OUTPUT);  
}

unsigned short int Sensor::lerSensor(byte n){
	digitalWrite(A2_74LS138_PIN, n & 4 ? HIGH : LOW); 
	digitalWrite(A1_74LS138_PIN, n & 2 ? HIGH : LOW); 
	digitalWrite(A0_74LS138_PIN, n & 1 ? HIGH : LOW);    
	delay(2);        // delay para estabilidade da leitura do ADC
	return analogRead(ANALOG);
}

unsigned short int Sensor::lerRodaEsquerda(){
	return lerSensor(SENSOR_RODA_ESQ);
}
unsigned short int Sensor::lerRodaDireita(){
	return lerSensor(SENSOR_RODA_DIR);
}