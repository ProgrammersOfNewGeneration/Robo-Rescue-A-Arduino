#include "motor.h"


Motor::Motor(){
	setVelocidade(100);
	configuraPinos();
}

Motor::Motor(byte m1_a, byte m1_b, byte m1_pwm, byte m2_a, byte m2_b, byte m2_pwm){
	configuraPinos();
	setVelocidade(100);
	setPinos(m1_a, m1_b, m1_pwm, m2_a, m2_b, m2_pwm);
}

void Motor::configuraPinos(){
	pinMode(MOTOR1_A, OUTPUT);
	pinMode(MOTOR1_B, OUTPUT);
	pinMode(MOTOR1_PWM, OUTPUT);
	pinMode(MOTOR2_A, OUTPUT);
	pinMode(MOTOR2_B, OUTPUT);
	pinMode(MOTOR2_PWM, OUTPUT);
}

void Motor::setPinos(byte m1_a, byte m1_b, byte m1_pwm, byte m2_a, byte m2_b, byte m2_pwm){
	MOTOR1_A = m1_a;
	MOTOR1_B = m1_b;
	MOTOR1_PWM = m1_pwm;
	MOTOR2_A = m2_a;
	MOTOR2_B = m2_b;
	MOTOR2_PWM = m2_pwm;
}

void Motor::setVelocidade(byte v){
	if((v <=0 ) || (v >= 255))
		return;
	analogWrite(MOTOR1_PWM, v);
	analogWrite(MOTOR2_PWM, v);
}

void Motor::setVelocidadeMotor1(byte v){
	if((v <=0 ) || (v >= 255))
		return;
		analogWrite(MOTOR1_PWM, v);
}

void Motor::setVelocidadeMotor2(byte v){
	if((v <=0 ) || (v >= 255))
		return;
	analogWrite(MOTOR2_PWM, v);
}

void Motor::irMotor(byte m1_a, byte m1_b, byte m2_a, byte m2_b){
	digitalWrite(MOTOR1_A, m1_a);
	digitalWrite(MOTOR1_B, m1_b);
	digitalWrite(MOTOR2_A, m2_a);
	digitalWrite(MOTOR2_B, m2_b);
	/*
esq-esq-dir-dir
1-0 = esq frente
0-1 = esq tras
0-1 = dir frente
1-0 = dir tras
*/

}

void Motor::irFrente(){
	irMotor(1, 0, 0, 1);
}

void Motor::irDireita(){
	irMotor(1, 0, 0, 0);
}

void Motor::irDireitaForte(){
	irMotor(1, 0, 1, 0);
}

void Motor::irEsquerda(){
	irMotor(0, 0, 0, 1);
}

void Motor::irEsquerdaForte(){
	irMotor(0, 1, 0, 1);
}

void Motor::irRe(){
	irMotor(0, 1, 1, 0);
}

void Motor::irParar(){
	irMotor(0, 0, 0, 0);
}

