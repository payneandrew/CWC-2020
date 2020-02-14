// https://dronebotworkshop.com/rotary-encoders-arduino/

// 100 CPR quadrature encoder
int cpr = 100;
 
// Encoder output to Arduino Interrupt pin
int rPin = 3;

unsigned long t_pulse; // in microseconds

int rpm = 0;

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600); 
  pinMode(rPin,INPUT);
}

void loop(){
  rpm();

}
int rpm(){
  t_pulse = pulseIn(rPin,HIGH);
  rpm = (60/(t_pulse * 2 * cpr));
  //Serial.println(t_pulse);
  Serial.println(rpm);
  delay(100); // delay for stability
  return rpm;
}
