// https://makersportal.com/blog/2019/02/06/arduino-pitot-tube-wind-speed-theory-and-experiment
//https://forum.arduino.cc/index.php?topic=226279.0
// pressure differential datasheet https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS4515%7FB2%7Fpdf%7FEnglish%7FENG_DS_MS4515_B2.pdf%7FCAT-BLPS0040

float V_S = 5.0; // supply voltage from arduino
float rho = 1.204; // density of air
float p_min = -497.68; // minimium pressure in pa
float p_max = 497.68; // maximum pressure in pa
float veloc = 0; // velocity
float v_out = 0; // voltage
float pressure = 0; //pressure



void setup() {
  Serial.begin(9600);

}

void loop() {
  float sensorValue = analogRead(A1);
  // convert bits to voltage
  v_out = (float)sensorValue / 1023.0 *5.0;
  // solve for pressure difference from datasheet equation
  pressure = (v_out - 0.5)*(p_max - p_min)/(0.8 * V_S) + p_min;
  // equation for wind velocity
  veloc = sqrt((2*pressure)/rho);
  
  
  
  Serial.println(veloc); // print velocity
  delay(100); // delay for stability
}