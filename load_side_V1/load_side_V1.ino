int cPin = A0;  //current sensor input pin
int rpmPin = 11; //rpm sensor input pin
int wsPin = 10;  //windspeed sensor input
int vPin = A1; //voltage sensor input pin
int bPin = 3; //braking output pin

void setup() {
  // intiates used digital pins as inputs and ouputs 
  pinMode(cPin,INPUT);
  pinMode(rpmPin,INPUT);
  pinMode(vPin,INPUT);
  pinMode(wsPin,INPUT);
  pinMode(bPin,OUTPUT);


  Serial.begin(9600);

}

void loop() {


}
