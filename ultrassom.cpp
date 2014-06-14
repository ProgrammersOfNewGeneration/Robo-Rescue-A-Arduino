#include "ultrassom.h"

Ultrassom::Ultrassom(){
	configuraPinos();
}

Ultrassom::Ultrassom(int T_PIN, int E_PIN, int M_DIST){
	setT_pin(T_PIN);
	setE_pin(E_PIN);
	setM_dist(M_DIST);
	configuraPinos();
}

void Ultrassom::configuraPinos(){
	pinMode(TRIGGER_PIN,OUTPUT);
	pinMode(ECHO_PIN,INPUT);	
}

void Ultrassom::setT_pin(int T_PIN){
	TRIGGER_PIN = T_PIN;
}

void Ultrassom::setE_pin(int E_PIN){
	ECHO_PIN = E_PIN;
}

void Ultrassom::setM_dist(int M_DIST){
	MAX_DISTANCE = M_DIST;
}

int Ultrassom::getT_pin(){
	return TRIGGER_PIN;
}

int Ultrassom::getE_pin(){
	return ECHO_PIN;
}

int Ultrassom::getM_dist(){
	return MAX_DISTANCE;
}

float Ultrassom::lerDistancia(){
	digitalWrite(TRIGGER_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIGGER_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER_PIN, LOW);
	long duracao = pulseIn(ECHO_PIN, HIGH);
	Serial.begin(9600);
	Serial.println(duracao/29/2);
	return(duracao/29/2);
}