#ifndef sensor_h
#define sensor_h

#include "Arduino.h"


#define A0_74LS138_PIN  A2
#define A1_74LS138_PIN  A1
#define A2_74LS138_PIN  A0
#define ANALOG          A3
//Numero de cada sensor na rotina
const int SENSOR_0        = 0;
const int SENSOR_1        = 1;
const int SENSOR_2        = 2;
const int SENSOR_3        = 3;
const int SENSOR_4        = 4;
const int SENSOR_RODA_ESQ = 5;
const int SENSOR_RODA_DIR = 6;


class Sensor{
private:
	int maior[5] = {0,0,0,0,0}; //armazenar valores para calibrar
	int menor[5] = {9999, 9999, 9999, 9999, 9999}; // valores para calibrar
	int limite[5] = {500, 500, 500, 500, 500}; //limite de cada sensor, dizendo se eh preto ou branco
	void configuraPinos();


public:
	Sensor();//inicializa sensor
	unsigned short int lerSensor(byte n);
	unsigned short int lerRodaEsquerda();
	unsigned short int lerRodaDireita();

};

#endif