#include <LibPrintf.h>

#define sampelData 5
#define pin A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tekananSensor();
  delay(2000);
}

void tekananSensor(){
  /*
   * Sensor full-scale = 4.7V
   * Max = 700 KPa
   * Datasheet formula :
   * VS = 5V
   * Vout = VS * (0.0012858*P + 0.04)
   * Vout = 0.006429*P + 0.2
   * P = (Vout - 0.2) / 0.006429
   * Calibration Value :
   * Vout = (0.006429 * 101.325) + 0.2
   * Vout = 0.851418425
   */
  int sensorRead,
  fullScale = 4700;
  float voltageMean, voltageMap, kpa, psi, atm, bar, mmhg,
  calValue = 0.851418425,
  offset = 0; //Adjust until the sensor output reaches 101,325 kPa
  sensorRead = 0;
  analogRead(pin);
  for(int i = 0; i < sampelData; i++){
    sensorRead += analogRead(pin);
  }
  voltageMean = (sensorRead / (float)sampelData) * (5000.0 / 1024.0);
  voltageMap = (map((int)round(voltageMean), 0, 5000, 0, fullScale) / 1000.0) + offset;
  kpa = ((voltageMap - 0.2) / 0.006429);
  psi = kpa * 0.14503774;
  atm = kpa * 0.00986923;
  bar = kpa / 100.0;
  mmhg= kpa * 7.501;
  //printf("Change offset to = %f", abs(calValue - voltageMap)); //un-comment to calibrate the sensor to 101,325 kPa
  printf("ADC Voltage = %f", voltageMap);
  printf("\nTekanan = %f kPa atau %f psi atau %f atm atau %f bar atau %f mmhg\n", kpa, psi, atm, bar, mmhg);
}
