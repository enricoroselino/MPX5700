#include <LibPrintf.h>

int sampelData = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tekananSensor();
  delay(2000);
}

void tekananSensor(){
  float sensorRead, voltageMean, voltage, kpa, psi, atm, bar, mmhg,
  offset = 0; //Adjust until the sensor output reaches 101,325 kPa or 14,69594878 psi or 1 atm
  voltage = 0.0;
  for(int i = 0; i < sampelData; i++){
    sensorRead = ((float)analogRead(A0) + 0.5) * (5.0 / 1024.0);
    voltage += sensorRead;
    delay(10);
  }
  voltageMean = (voltage / (float)sampelData) + offset;
  kpa = ((voltageMean - 0.2) / 0.006429);
  psi = kpa * 0.14503774;
  atm = kpa * 0.00986923;
  bar = kpa / 100.0;
  mmhg= kpa * 7.501;
  //printf("Change offset to = %f", abs(0.851418 - voltageMean)); //un-comment to calibrate the sensor to 1 atm
  printf("ADC Voltage = %f", voltageMean);
  printf("\nTekanan = %f kPa atau %f psi atau %f atm atau %f bar atau %f mmhg\n", kpa, psi, atm, bar, mmhg);
}
