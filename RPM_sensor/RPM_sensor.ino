// https://dronebotworkshop.com/rotary-encoders-arduino/

// 100 CPR quadrature encoder
#define ENC_COUNT_REV 100
 
// Encoder output to Arduino Interrupt pin
#define ENC_IN 3
 
// Pulse count from encoder
volatile long encoderValue = 0;
 
// One-second interval for measurements
int interval = 1000;
 
// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;
 
// Variable for RPM measuerment
int rpm = 0;
 
void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600); 
  
  // Set encoder as input with internal pullup  
  pinMode(ENC_IN, INPUT_PULLUP); 
  
  // Attach interrupt 
  attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);
  
  // Setup initial values for timer
  previousMillis = millis();
}
 
void loop()
{
  
  // Update RPM value every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
 
 
    // Calculate RPM
    rpm = (float)(encoderValue * 60 / ENC_COUNT_REV);
 
    // Only update display when there is a reading
    if (rpm > 0) {
      Serial.print(" PULSES: ");
      Serial.print(encoderValue);
      Serial.print('\t');
      Serial.print(" SPEED: ");
      Serial.print(rpm);
      Serial.println(" RPM");
    }
    
    encoderValue = 0;
  }
}
 
void updateEncoder()
{
  // Increment value for each pulse from encoder
  encoderValue++;
}
