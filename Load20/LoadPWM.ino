int mos=10;
int knob=0;

void setup()
{
  Serial.begin(9600);
 
  pinMode(mos, OUTPUT);
 TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz
}

void loop()
{
  int knobValue=analogRead(knob);
  int DutyCycle=map(knobValue,1,1024,1,255);
  analogWrite(mos,DutyCycle);
  Serial.println(DutyCycle);
 
  
}
