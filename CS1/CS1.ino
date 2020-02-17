void setup() {
Serial.begin(9600);
}

void loop() {
  current();
}

int current() {
  // Declare Variables
  const int currentPin = A0;
  int sensitivity = 185;
  int adcValue= 0;
  int offsetVoltage = 2500;
  double adcVoltage = 0;
  double currentValue = 0;

  // Function
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  // Print Statements
  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);
  Serial.print("\t Voltage(mV) = ");
  Serial.print(adcVoltage,3);
  Serial.print("\t Current(A) = ");
  Serial.println(currentValue,3);
  // 2.5s delay
  delay(2500);
}
