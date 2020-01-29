#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int prev;
int potpin = 0;  // analog pin used to connect the potentiometer
int val = 30;    // variable to read the value from the analog pin


int cPin;  //current sensor input pin
int rpmPin = 7; //rpm sensor input pin
int vPin; //voltage sensor input pin
int bPin = 3; //braking output pin
float brakePWM;
float brake;

int P_gain = 1;
//intiates all global variables
float current; //current in amps
float voltage; //voltage in volts
int RPM;     //angular velocity in RPM
float power;  ///power in watts
//int brakePWM;  //braking power
int R_Power = 0; //rated power
int R_RPM = 1700;  //rated RPM
int R_Voltage = 42.0; // rated voltage
void setup() {
  // intiates used digital pins as inputs and ouputs 
  pinMode(cPin,INPUT);
  pinMode(rpmPin,INPUT);
  pinMode(vPin,INPUT);
  pinMode(8,INPUT);
  pinMode(6,INPUT);
  pinMode(bPin,OUTPUT);

  //intiates braking to zero
  brakePWM = 0;
  Serial.begin(9600);

  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS00);
  pinMode(3,OUTPUT);
  analogWrite(3,0);

   myservo.attach(6);

}

void loop() {


//gets all inputs and calculates power
 //current = Current();
 voltage = Voltage();
 //RPM = rpm();
 power = current*voltage;

//check to see if the load is disconnected
//if so go to the safety procedure
 
for(int i;i<5;i++){
 
/*brakePWM = 2 * (RPM - R_RPM); 
 

 if (brakePWM > 255){
  brakePWM = 255;
 }
 else if(brakePWM<0){
  brakePWM = 0;  
 }
 
 else{
  
 } 
 analogWrite(3,brakePWM);
*/



//Serial.print("RPM: ");
//Serial.println(RPM);

//Serial.print("brakePWM: ");
//Serial.println(brakePWM);

//Serial.print("Current: ");
//Serial.println(current);

Serial.println(brakePWM);
//safety(RPM);
mppt(voltage);
}
mppt(voltage);

}

float Current(){
   int x = 0;
  int n = 0;
  for(int i; i < 100; i++){
    
  x = analogRead(A0);
  n = n+x;
  
}
  return n/100.0/200.2;
 
}

float Voltage(){
  float Voltage;
  Voltage = 10.288*analogRead(A1)*5.0/1024.0;
  Serial.println(Voltage);
  return Voltage; 
}

float rpm(){
  
  int prev_RPM;
  float rpm = 0.0;
  int i = 0;
  int x;
  unsigned long tTime = 0;
  unsigned long duration = 0;
 
  for( int i; i<4; i=i+x) {    
    duration = pulseIn(rpmPin,LOW,500000);
  
           power = current*voltage;
           current = Current();
           voltage = Voltage();
                
                       
           mppt(voltage);
           //safety(RPM);
             
          if (duration > 1000 & duration< 1000000){
            tTime = duration + tTime;           
            duration = 0;
            x=1;  
          }    
        else {
          x=0;
          }
     }
     
          /* brakePWM =  (RPM - R_RPM)*2; 

           if (brakePWM > 255){
              brakePWM = 255;
             }
             else if(brakePWM<0){
              brakePWM = 0;  
             }
             else{              
             } 
             
             analogWrite(3,brakePWM);*/

  tTime = tTime/2;
  rpm = 1000000.0/tTime * 60.0;
  if(rpm > 3000){
    rpm = 0;
  }
  else{
    
  }
  

  return rpm;
}     
     
int safety(int RPM){
  
    float brake;
    brake = (RPM - R_RPM)/300;    
    brakePWM = brakePWM + brake*2/3;
  //brakePWM = 83;
  if (brakePWM < 0 || brakePWM > 255 ) {
    if (brakePWM > 255){
      brakePWM = 255;
    }
  
    else{
    brakePWM = 0;    
    }
  }
  
  else{
   
  }

 //analogWrite(3,brakePWM);// sets the servo position according to the scaled value
        
  }
  

int mppt ( float voltage){
    

    int x;
    int y;
    int w = 48  ;
    brake = P_gain * (voltage - w); 
    if(voltage -  w> 1){
      x = 1;
      y = 10;
    }
   else if(voltage - w < 2){
            x = 1;
            y = 32;
    }
    else{

    }
    brakePWM = brakePWM + brake*x/y;
  //brakePWM = 83;
  if (brakePWM < 70 || brakePWM > 180 ) {
    if (brakePWM > 180){
      brakePWM = 180;
    }
  
    else{
    brakePWM = 70;    
    }
  }
  
  else{
   
  }
Serial.println(brakePWM);
myservo.write(brakePWM); 

 
  
}





