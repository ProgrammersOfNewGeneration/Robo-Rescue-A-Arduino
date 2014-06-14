#ifndef OBJ_SERVO_H
#define OBJ_SERVO_H

#include "Arduino.h"
#include "Servo.h"

class ObjServo{
private:
	int Pino = 4;
	Servo servo;

public:
	ObjServo();
	ObjServo(int P);
	void setPin(int P);
	int getPin();
	void girar(int d);
	void configura();

};

#endif // OBJ_SERVO_H