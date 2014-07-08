#include <PololuQTRSensors.h>

#define LINE_SENSOR_PIN 6
#define NUM_SENSORS     1     // number of sensors used
#define TIMEOUT         2500  // waits for 2500 us for sensor outputs to go low

#define LINE_THRESHOLD  700   // value out of 1000 that defines the "line"

PololuQTRSensorsRC qtrrc((unsigned char[]) {6}, NUM_SENSORS, TIMEOUT); 

void calibrateLineSensor()
{
  Serial.print("Calibrating... ");
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  Serial.println("done.");
}

boolean getEdgeDetect()
{
  qtrrc.readCalibrated(sensorValues, 1);
  if (sensorValues[0] < LINE_THRESHOLD)
  {
    return true;
  }
  return false;
}

