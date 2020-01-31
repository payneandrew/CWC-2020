// https://dronebotworkshop.com/rotary-encoders-arduino/

// 100 CPR quadrature encoder
int cpr = 100;
 
// Encoder output to Arduino Interrupt pin
int rPin = 3;

unsigned long duration; // in microseconds

int rpm = 0;

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600); 
  pinMode(rPin,INPUT);
}

void loop(){
  duration = (pulseIn(rPin,HIGH) * 2)/1000; // counts = pulses x 2
  rpm = (60/(duration * cpr));
  //Serial.println(duration);
  Serial.println(rpm);

}
