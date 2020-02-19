//https://github.com/jonblack/arduino-fsm
#include <Fsm.h>
// declare states

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read all inputs
  windspeed();
  voltage();
}



float voltage(){
  float voltage;
  voltage = 10.288*analogRead(A1)*5.0/1024.0;
  Serial.println(voltage);
  return voltage; 
}

int windspeed(){
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
