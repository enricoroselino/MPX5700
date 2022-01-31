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
  long voltage;
  int sensorRead, voltageMap,
  VCC = 5000,
  fullScale = 4700; //Sensor fullscale voltage 4700
  float voltageMean, kpa, psi, atm, bar,
  offset = 0; //Adjust until the sensor output reaches 101,325 kPa or 14,69594878 psi or 1 atm
  voltage = 0.0;
  for(int i = 0; i < sampelData; i++){
    sensorRead = (analogRead(A0) + 0.5) * (VCC / 1024);
    //map the "ADC voltage" output from the ADC default reading by Vref (VCC at 1024) to sensor fullscale (4.7V at 963)
    voltageMap = map(sensorRead, 0, VCC, 0, fullScale);
    voltage += voltageMap;
    delay(10);
  }
  voltageMean = ((voltage / sampelData) / 1000.0) + offset;
  kpa = ((voltageMean - 0.2) / 0.006429);
  if(kpa <= 0){
    kpa = 0.0;
  }
  psi = kpa * 0.14503774;
  atm = kpa * 0.00986923;
  bar = kpa / 100.0;
  printf("ADC Voltage = %f", voltageMean);
  printf("\nTekanan = %f kPa atau %f psi atau %f atm atau %f bar\n", kpa, psi, atm, bar);
}
