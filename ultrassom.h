#ifndef ultrassom_h
#define ultrassom_h

#include "Arduino.h"

class Ultrassom{
private:
	int TRIGGER_PIN;
	int ECHO_PIN;
	int MAX_DISTANCE;

public:
	Ultrassom();
	Ultrassom(int T_PIN, int E_PIN, int M_DIST);
	void configuraPinos();
	void setT_pin(int T_PIN);
	void setE_pin(int E_PIN);
	void setM_dist(int M_DIST);
	int getT_pin();
	int getE_pin();
	int getM_dist();
	float lerDistancia();
	

};

#endif
