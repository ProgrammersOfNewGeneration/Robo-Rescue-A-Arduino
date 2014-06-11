#include <SoftwareSerial.h>
#include <Servo.h>
#include "bluetooth.h"
#include "motor.h"
#include "ultrassom.h"
#include "obj_servo.h"



Ultrassom *ult = new Ultrassom();
Motor *motor = new Motor();
Bluetooth *blue = new Bluetooth();
ObjServo *servo = new ObjServo();

void setup(){
	Serial.begin(9600);
	blue->configuraBluetooth();
	motor->setVelocidade(150);
	servo->configura();

}


void loop(){

	if(Intervalo20()){
		String msg = blue->Ler();
		Serial.println(msg);
		if(msg.length() > 1)
			lerMsg(msg);
	}

}

boolean Intervalo500() {
  static long time = millis();
  if ((int)(millis() - time) >= 500) {
    time = millis();
    return true;
  }
  return false;
}


boolean Intervalo20() {
  static long time = millis();
  if ((int)(millis() - time) >= 20) {
    time = millis();
    return true;
  }
  return false;
}


// void chamarFuncao(int cod, int arg1 = 0, int arg2 = 0);
void chamarFuncao(int cod, int arg1){

	switch (cod) {
	    case 1: motor->setVelocidade(arg1); break;
		case 2: motor->setVelocidadeMotor1(arg1); break;
		case 3: motor->setVelocidadeMotor2(arg1); break;
		case 4: motor->irFrente(); break;
		case 5: motor->irDireita(); break;
		case 6: motor->irDireitaForte(); break;
		case 7: motor->irEsquerda(); break;
		case 8: motor->irEsquerdaForte(); break;
		case 9: motor->irRe(); break;
		case 10: motor->irParar(); break;
		case 11: ult->setT_pin(arg1); break;
	    case 12: ult->setE_pin(arg1); break;
	    case 13: ult->setM_dist(arg1); break;
	    case 14: retornarDados(arg1, ult->getT_pin()); break;
	    case 15: retornarDados(arg1, ult->getE_pin()); break;
	    case 16: retornarDados(arg1, ult->getM_dist()); break;
		case 17: 
			// float dist = ult->lerDistancia(); 
			retornarDados(arg1, (int)ult->lerDistancia());
		break;  
		case 18:
			Serial.print("delay: ");
			Serial.println(arg1);
			delay(arg1);
		break;
		case 19:
			Serial.println("ASDASDASDASDADs");
			retornarDados(arg1, Encruzilhada());
			break;

	}
}

int Encruzilhada(){
	motor->irFrente();
	delay(1000);
	motor->irDireitaForte();
	delay(1000);
	motor->irParar();
	return 1;
}

void retornarDados(int id, int valor){
	char Id[5], Val[5], msg[1024];
	sprintf(Id, "%d", id); 
	sprintf(Val, "%d", valor);
	strcpy(msg, Id);
	strcat(msg, "@");
	strcat(msg, Val);
	strcat(msg, "#");

	Serial.println(msg);
	Serial.println("########################3");
	blue->Enviar(msg);
}


void lerMsg(String msg){
	String SB, TB;
	int iSB, iTB;

	
	int i;
	switch (msg.charAt(0)) {
	    case '1':
	       
	      break;
	    case '2':
	      break;
	    case '3':
	    	for(i = 2; i < msg.length(); i++){
	    		if(msg.charAt(i) == '#')
	    			break;
	    		if(msg.charAt(i) == '@')
	    			for(int k = i+1; k < msg.length(); k++){
	    				if(msg.charAt(k) == '#')
	    					break;
	    				TB += msg.charAt(k);
	    			}
	    		SB += msg.charAt(i);
	    	}

	    	iSB = SB.toInt();
	    	iTB = TB.toInt();

	    	chamarFuncao(iSB, iTB);
	    
	    break;
	}
}
