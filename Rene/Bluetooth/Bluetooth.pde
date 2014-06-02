AndroidBluetooth bt = new AndroidBluetooth(this); 

void setup() {
  textFont(createFont("Georgia", 36));
  textSize(36);
  try {
    bt.connect("Robo-TCC");
  } 
  catch (IOException e) {
  }
}


void draw() {
  try {
    if (bt.in != null) {
      text("!", 50, 50);
      if (bt.in.available() > 0) {
        background(0);
        text((char)bt.in.read(), 100, 100);
      }
    } 
//    else
      //print("?");
  } 
  catch(Exception e) {
    e.printStackTrace();
  }
}
