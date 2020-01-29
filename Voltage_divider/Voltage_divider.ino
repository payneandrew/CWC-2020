float voltage; //voltage in volts
void setup(){
  Serial.begin(9600);
  // intialize pin A1 as an input
  pinMode(A1,INPUT);
  
}

void loop(){
  voltage = Voltage();
}

float Voltage(){
  float Voltage;
  Voltage = 10.288*analogRead(A1)*5.0/1024.0;
  Serial.println(Voltage);
  return Voltage; 
}

// this is a new change
