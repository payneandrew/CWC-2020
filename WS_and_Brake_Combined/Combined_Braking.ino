// wind speed bins chosen by the organizers between 12 m/s 
// and 16 m/s, and turbine performance in those two bins 
// will be compared to the performance in the 11 m/s bin. 
// The turbines are expected to keep the rpm at or below 
// the rpm determined at 11 m/s and to keep the power at 
// the same level as is determined at 11 m/s.

#include <Servo.h>

int Wind_speed[200];
Servo servo_9;
int RPM[200];
int TSR = 2;
double r = 0.22; //blade radius in m
double d = 2.00 * 3.14 * r;
float alter = 0;
int pos = 30;
int stay_rpm = 0;

void setup()
{
  Serial.begin(9600);
  servo_9.attach(9);
  servo_9.write(30);
  
  // TSR = 2(pi)r(RPM)/60(Wind_speed)
  // RPM = (TSR)60(Wind_speed)/2(pi)r
}

void loop()
{
  Serial.println("New Trial");
  for (int i = 0; i <= 200; i++) {
    Wind_speed[i] = windspeed();
    RPM[i] = ((TSR)*60*(Wind_speed[i]))/d;
    Serial.print("Wind speed: ");
    Serial.print(Wind_speed[i]);
    Serial.print(" m/s");
    if (Wind_speed[i] == 11) {
      Serial.print(", RPM: ");
      Serial.println(RPM[i]);
      stay_rpm = RPM[i];
      return stay_rpm;
      
    }
    if (Wind_speed[i] > 11 && Wind_speed[i] <= 16) {
      alter = 1 - stay_rpm/Wind_speed[i];
      pos = 170 * alter * 3;
      Serial.print(", RPM: ");
      Serial.print(RPM[i]);
      if (pos <= 170) {
        servo_9.write(pos);
        Serial.print(", Alteration: ");
        Serial.print(alter * 300);
        Serial.println("%");
        
      } else {
        servo_9.write(170);
        Serial.println(", Alteration: 100%");
        
      }
    } 
    delay(500);
    servo_9.write(30);
  }
}

int windspeed(){
  // declare variables
  float V_S = 5.0; // supply voltage from arduino
  float rho = 1.204; // density of air
  float p_min = -497.68; // minimium pressure in pa
  float p_max = 497.68; // maximum pressure in pa
  int velocity = 0; // velocity
  float pressure = 0; //pressure
  float v_out = 0; // voltage
  
  // convert bits to voltage
  v_out = analogRead(A1) / 1023.0 *5.0;
  // solve for pressure difference from datasheet equation
  pressure = (v_out - 0.5)*(p_max - p_min)/(0.8 * V_S) + p_min;
  // equation for wind velocity
  velocity = sqrt((2*pressure)/rho);
  
  Serial.println(velocity); // print velocity
  delay(100); // delay for stability
  return velocity;
}
