int P_gain =1;
int cPin = A0;  //current sensor input pin
int rpmPin = 11; //rpm sensor input pin
int vPin = A1; //voltage sensor input pin
int bPin = 3; //braking output pin


//intiates all global variables
float current; //current in amps
float voltage; //voltage in volts
float RPM;     //angular velocity in RPM
float power;  ///power in watts
int brakePWM;  //braking power
int R_Power = 45; //rated power
int R_RPM = 800;  //rated RPM
int R_Voltage = 40; // rated voltage
int prev_Power;
int cutin_PWM = 2;
int p = 0;
float cutin_Power = 0.5;

void setup() {
  // intiates used digital pins as inputs and ouputs 
  pinMode(cPin,INPUT);
  pinMode(rpmPin,INPUT);
  pinMode(vPin,INPUT);
  pinMode(bPin,OUTPUT);

  //intiates braking to zero
  brakePWM = 2;
  prev_Power = 0;
  power = 0;
  Serial.begin(9600);

  //sets frequency of pin 2 to 62.5kHz
  
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS01);
  

  analogWrite(bPin,cutin_PWM);
  
}

void loop() {
  
for (int i; i<100;i++){
//gets all inputs and calculates power
voltage = Voltage();
current = Current();


//RPM = rpm();
 
power = current*voltage;
mppt(voltage);
}

//int pt;
//pt = pot();

//Serial.println(RPM);
//Serial.print("Current: ");
//Serial.println(current);
//Serial.print("Voltage: ");
//Serial.println(voltage);
//Serial.print("Power: ");
//Serial.println(power);

//Serial.print("PWM: ");
//Serial.println(analogRead(A2)/2.2);
//Serial.println();
}


float Current(){
  int y = 0;
  int n = 0;
  for(int i; i < 100; i++){
    
  y = analogRead(A0);
  n = n+y;
  
}
  return n/100.0/200.2;

}

float Voltage(){  
  float Voltage = analogRead(A1)*51.85/1023.0;
/*Serial.print("Voltage: ");
Serial.println(Voltage);
Serial.println();
Serial.println();
*/
  return Voltage;
  
}



int safety(){
  
}

int mppt(float voltage){
  

    float brake;
    
    brake = P_gain * (voltage  - 41)*3/2;    
    brakePWM = brakePWM + brake;
  //brakePWM = 83;
  if (brakePWM < 13 || brakePWM > 52 ) {
    if (brakePWM > 52){
      brakePWM = 52;
    } 
  
    else{
    brakePWM = 13;    
    }
  }
  
  else{
   
  }

brakePWM = 34;
analogWrite(bPin,brakePWM); 


Serial.print("brakePWM: ");
Serial.println(brakePWM);

}

int pot(){
  int x;
  x =  map(analogRead(A2), 0 , 600, 0,260 );
  analogWrite(3,x);
  return x;
}
