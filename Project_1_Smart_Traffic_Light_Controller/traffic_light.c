// Project 1 – Smart Traffic Light 

#define RED     13
#define YELLOW  12
#define GREEN   11

#define SENSOR  2          // Add a push button from pin 2 → GND (you can add it in 10 sec)

unsigned long greenDuration = 8000;   // Changes dynamically
unsigned long yellowDuration = 3000;
unsigned long stateStart = 0;
int vehiclesWaiting = 0;

enum State { GREEN_PHASE, YELLOW_PHASE, RED_PHASE } currentState = GREEN_PHASE;

void setup() {
	Serial.begin(9600);
	Serial.println(F("Smart Traffic Light Started – Press button = vehicle waiting"));

	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(SENSOR, INPUT_PULLUP);

	// Start with GREEN
	digitalWrite(GREEN, HIGH);
	stateStart = millis();
}

void loop() {
	unsigned long now = millis();

	// 1. Detect vehicles (press the button you’ll add on pin 2)
	if (digitalRead(SENSOR) == LOW) {
		vehiclesWaiting++;
		Serial.print("Vehicle detected! Queue = ");
		Serial.println(vehiclesWaiting);
		delay(300); // debounce
	}

	// 2. Dynamic green time: more vehicles = longer green
	greenDuration = 5000 + (vehiclesWaiting * 1500);
	greenDuration = constrain(greenDuration, 5000, 20000);

	// 3. Non-blocking state machine using millis()
	unsigned long phaseTime = (currentState == GREEN_PHASE)  ? greenDuration :
		(currentState == YELLOW_PHASE) ? yellowDuration : 2000;

	if (now - stateStart >= phaseTime) {
		advanceState();
		stateStart = now;
	}

	// 4. Serial command: type 's' → show status
	if (Serial.available() && Serial.read() == 's') {
		Serial.println("\n=== SMART TRAFFIC STATUS ===");
		Serial.print("Current phase: ");
		switch(currentState) {
			case GREEN_PHASE:  Serial.println("GREEN"); break;
			case YELLOW_PHASE: Serial.println("YELLOW"); break;
			case RED_PHASE:    Serial.println("RED"); break;
		}
		Serial.print("Vehicles waiting: "); Serial.println(vehiclesWaiting);
		Serial.print("Next green time: "); Serial.print(greenDuration/1000); Serial.println(" seconds");
		Serial.println("============================\n");
	}
}

void advanceState() {
	// Turn everything off first
	digitalWrite(RED, LOW);
	digitalWrite(YELLOW, LOW);
	digitalWrite(GREEN, LOW);

	switch (currentState) {
		case GREEN_PHASE:
			currentState = YELLOW_PHASE;
			digitalWrite(YELLOW, HIGH);
			Serial.println("Switching to YELLOW");
			break;

		case YELLOW_PHASE:
			currentState = RED_PHASE;
			digitalWrite(RED, HIGH);
			Serial.println("Switching to RED – clearing queue");
			vehiclesWaiting = 0;           // All cars passed
			break;

		case RED_PHASE:
			currentState = GREEN_PHASE;
			digitalWrite(GREEN, HIGH);
			Serial.print("Switching to GREEN for ");
			Serial.print(greenDuration/1000);
			Serial.println(" seconds");
			break;
	}
}
