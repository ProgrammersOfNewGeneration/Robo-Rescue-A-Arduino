#ifndef motor_h
#define motor_h

#include "Arduino.h"

class Motor{
private:
	byte MOTOR1_A = 6;
	byte MOTOR1_B = 7;
	byte MOTOR1_PWM = 5;
	byte MOTOR2_A = 8;
	byte MOTOR2_B = 9;
	byte MOTOR2_PWM = 11;
	void configuraPinos();
	void irMotor(byte m1_a, byte m1_b, byte m2_a, byte m2_b);

public:
	Motor();
	Motor(byte m1_a, byte m1_b, byte m1_pwm, byte m2_a, byte m2_b, byte m2_pwm);
	void setPinos(byte m1_a, byte m1_b, byte m1_pwm, byte m2_a, byte m2_b, byte m2_pwm);
	void setVelocidade(byte v);
	void setVelocidadeMotor1(byte v);
	void setVelocidadeMotor2(byte v);
	void irFrente();
	void irDireita();
	void irDireitaForte();
	void irEsquerda();
	void irEsquerdaForte();
	void irRe();
	void irParar();

};


#endif