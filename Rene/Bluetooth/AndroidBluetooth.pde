import android.bluetooth.*;
import java.util.*;
import java.io.*;

class AndroidBluetooth {
  BluetoothDevice celControlador;
  BluetoothSocket sock;
  OutputStream out;
  InputStream in;
  boolean pairedFound = false;
  boolean connected = false;
  PApplet activity;

  AndroidBluetooth(PApplet activity) {
    this.activity = activity;
  }

  class Connect implements Runnable {
    String deviceName;

    Connect(String deviceName) {
      this.deviceName = deviceName;
    }

    public synchronized void run() {
      Set<BluetoothDevice> devices = BluetoothAdapter.getDefaultAdapter().getBondedDevices ();
      if (devices.size() > 0) {
        for (BluetoothDevice device : devices) {
          if (device.getName().equals(deviceName)) {
            celControlador = device;
            pairedFound = true;
            break;
          }
        }
      }
      notify();
    }

    synchronized void waitConnectionReady() throws IOException {
      try {  
        if (!pairedFound)
          wait(); //espera o metodo run(), invocado pelo runOnUiThread, terminar
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); //Standard SerialPortService ID
        sock = celControlador.createRfcommSocketToServiceRecord(uuid);
        sock.connect();
        println(">"+celControlador.getName()+"]]");
        out = sock.getOutputStream();
        in = sock.getInputStream();
        connected = true;
      } 
      catch (InterruptedException e) {
      }
    }
  }

  void connect(String deviceName) throws IOException {
    Connect r = new Connect(deviceName); 
    activity.runOnUiThread(r);
    r.waitConnectionReady();
    println("-----------");
  }
  
}
