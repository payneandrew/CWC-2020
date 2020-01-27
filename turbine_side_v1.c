// Declare states
enum State {Idle, Cutin, PowerCurve, Control, Shutdown}
State currentState;
State nextState;


void setup() {
	Serial.begin(9600);
}

// Main loop
void loop() {
	
	// Read all inputs
