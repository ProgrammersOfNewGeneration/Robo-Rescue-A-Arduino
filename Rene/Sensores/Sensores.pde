float azimute = 0;

class S extends Sensors {
  void inclination(double alpha, double beta) {
    //print((int)(alpha*180/PI)+"º "+(int)(beta*180/PI)+"º");
  }
  void orientation(float azimut, float pitch, float roll) {
    print((int)(azimut*180/PI)+"º "+(int)(pitch*180/PI)+"º "+(int)(roll*180/PI)+"º");
    azimute = azimut+PI/2;
  }
}

Sensors s;
void setup() {
  s = new S();
}

void stop() {
  s.close();
  print("stop");
} 

void draw() {
  background(226);
  desenha();
}

void desenha() {
  int centerx = width/2;
  int centery = height/2;
  line(centerx, centery, cos(azimute)*100+centerx, centery-sin(azimute)*100);
}

