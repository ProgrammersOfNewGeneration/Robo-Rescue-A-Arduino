AndroidBluetooth bt = new AndroidBluetooth(this); 

void setup() {
  try {
    bt.connect("unesp-cti");
  } 
  catch (IOException e) {
  }
}


void draw() {
  try {
    if (bt.in != null) {
      //print("!");
      if (bt.in.available() > 0) {
        print((char)(bt.in.read()));
      }
    } 
//    else
      //print("?");
  } 
  catch(Exception e) {
    e.printStackTrace();
  }
}