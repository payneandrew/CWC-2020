// wind speed bins chosen by the organizers between 12 m/s 
// and 16 m/s, and turbine performance in those two bins 
// will be compared to the performance in the 11 m/s bin. 
// The turbines are expected to keep the rpm at or below 
// the rpm determined at 11 m/s and to keep the power at 
// the same level as is determined at 11 m/s.

#include <Servo.h>

int Wind_speed[25];
Servo servo_9;
int RPM[25];
int TSR = 2;
double r = 0.22; //blade radius in m
double d = 2.00 * 3.14 * r;
float alter = 0;
int pos = 30;

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
  for (int i = 0; i <= 24; i++) {
    Wind_speed[i] = i + 1;
    RPM[i] = ((TSR)*60*(Wind_speed[i]))/d;
    Serial.print("Wind speed: ");
    Serial.print(Wind_speed[i]);
    Serial.print(" m/s");
    if (Wind_speed[i] < 11) {
      Serial.print(", RPM: ");
      Serial.println(RPM[i]);
      delay(1000);
    }else if (Wind_speed[i] >= 11 && Wind_speed[i] < 26) {
      alter = 1 - (RPM[10] + 0.00)/(RPM[i] + 0.00);
      pos = 170 * alter * 3;
      Serial.print(", RPM: ");
      Serial.print(RPM[i]);
      if (pos <= 170) {
        servo_9.write(pos);
        Serial.print(", Alteration: ");
        Serial.print(alter * 300);
        Serial.println("%");
        delay(1000);
      } else {
        servo_9.write(170);
        Serial.println(", Alteration: 100%");
        delay(1000);
      }
    } 
    servo_9.write(30);
  }
}