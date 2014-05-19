import android.hardware.*;
import android.content.Context;

abstract class Sensors implements SensorEventListener {
  SensorManager mSensorManager;
  Sensor mSensor;
  Sensor mAccelerometer, mMagneticField, mOrientation;
  SensorEventListener listenerSensors;

  Sensors() {
    mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
    mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);  
    mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);  
    mMagneticField = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
    mSensorManager.registerListener(this, mMagneticField, SensorManager.SENSOR_DELAY_NORMAL);
  }

  public void onAccuracyChanged (Sensor sensor, int accuracy) {
  }

  float[] mGravity = new float[3];
  float[] mGeomagnetic = new float[3];
  float R[] = new float[9];
  float orientation[] = new float[3];
  public void onSensorChanged(SensorEvent event) {
    if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
      mGravity[0] = event.values[0];
      mGravity[1] = event.values[1];
      mGravity[2] = event.values[2];
      inclination(Math.atan2(event.values[0], event.values[2]), Math.atan2(event.values[1], event.values[2]));
    }
    if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
      mGeomagnetic[0] = event.values[0];
      mGeomagnetic[1] = event.values[1];
      mGeomagnetic[2] = event.values[2];
      if (SensorManager.getRotationMatrix(R, null, mGravity, mGeomagnetic)) {
        SensorManager.getOrientation(R, orientation);
        orientation(orientation[0], orientation[1], orientation[2]);
        //        azimut = orientation[0]; // orientation contains: azimut, pitch and roll
      }
    }
  }

  void close() {
    mSensorManager.unregisterListener(this);
  }

  abstract void inclination(double alpha, double beta);

  abstract void orientation(float azimut, float pitch, float roll);
};

