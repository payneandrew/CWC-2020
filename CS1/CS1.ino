const int currentPin = A0;
int sensitivity = 185;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  
  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);

  //delay(2000);

  Serial.print("\t Voltage(mV) = ");
  Serial.print(adcVoltage,3);
  
  //delay(2000);
 
  Serial.print("\t Current(A) = ");
  Serial.println(currentValue,3);
 
  delay(2500);
}
