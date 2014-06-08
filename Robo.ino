#include <SoftwareSerial.h>
#include "bluetooth.h"
#include "motor.h"
#include "ultrassom.h"



// Ultrassom *u = new Ultrassom();
Motor *motor = new Motor();
Bluetooth *blue = new Bluetooth();

void setup(){
	Serial.begin(9600);
	blue->configuraBluetooth();
	// m->irFrente();
	// m->setVelocidade(90);
}



void loop(){
	String msg = blue->Ler();
	Serial.println(msg);
	if(msg.length() > 1)
		lerMsg(msg);
	
}

void chamarFuncao(int cod, int arg1 = 0){
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
	      
	}
}


void lerMsg(String msg){
	String SB, TB;
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
	    		SB += msg.charAt(i);
	    	}

	    	chamarFuncao(SB.toInt());
	    
	    break;
	}
}
