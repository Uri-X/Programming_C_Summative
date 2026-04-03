// Project 1 – Smart Traffic Light Controller (TWO Intersections)
// Philbert Kuria – Summative 2025
// Intersection A: RED=13, YELLOW=12, GREEN=11, BUTTON=3
// Intersection B: RED=7,  YELLOW=6,  GREEN=5,  BUTTON=4

#define RED_A     13
#define YELLOW_A  12
#define GREEN_A   11
#define SENSOR_A  3

#define RED_B     7
#define YELLOW_B  6
#define GREEN_B   5
#define SENSOR_B  4

unsigned long yellowDuration = 3000;
unsigned long redDuration    = 2000;

unsigned long greenDuration_A = 8000;
unsigned long stateStart_A    = 0;
int vehiclesWaiting_A         = 0;

unsigned long greenDuration_B = 8000;
unsigned long stateStart_B    = 0;
int vehiclesWaiting_B         = 0;

enum State { GREEN_PHASE, YELLOW_PHASE, RED_PHASE };
State stateA = GREEN_PHASE;
State stateB = RED_PHASE;

void advanceState_A();
void advanceState_B();
void showStatus();

void setup() {
  Serial.begin(9600);
  Serial.println("Smart Traffic Light – 2 Intersections Started");
  Serial.println("Press D3 = vehicle at A  |  Press D4 = vehicle at B");
  Serial.println("Type 's' to see status");

  pinMode(RED_A,    OUTPUT);
  pinMode(YELLOW_A, OUTPUT);
  pinMode(GREEN_A,  OUTPUT);
  pinMode(SENSOR_A, INPUT_PULLUP);

  pinMode(RED_B,    OUTPUT);
  pinMode(YELLOW_B, OUTPUT);
  pinMode(GREEN_B,  OUTPUT);
  pinMode(SENSOR_B, INPUT_PULLUP);

  // A starts GREEN, B starts RED — never both green at same time
  digitalWrite(GREEN_A, HIGH);
  digitalWrite(RED_B,   HIGH);

  stateStart_A = millis();
  stateStart_B = millis();
}

void loop() {
  unsigned long now = millis();

  if (digitalRead(SENSOR_A) == LOW) {
    vehiclesWaiting_A++;
    Serial.print("Vehicle at A! Queue = ");
    Serial.println(vehiclesWaiting_A);
    delay(300);
  }

  if (digitalRead(SENSOR_B) == LOW) {
    vehiclesWaiting_B++;
    Serial.print("Vehicle at B! Queue = ");
    Serial.println(vehiclesWaiting_B);
    delay(300);
  }

  greenDuration_A = constrain(5000 + (vehiclesWaiting_A * 1500), 5000, 20000);
  greenDuration_B = constrain(5000 + (vehiclesWaiting_B * 1500), 5000, 20000);

  unsigned long phaseTime_A = (stateA == GREEN_PHASE)  ? greenDuration_A :
                              (stateA == YELLOW_PHASE) ? yellowDuration : redDuration;
  if (now - stateStart_A >= phaseTime_A) {
    advanceState_A();
    stateStart_A = now;
  }

  unsigned long phaseTime_B = (stateB == GREEN_PHASE)  ? greenDuration_B :
                              (stateB == YELLOW_PHASE) ? yellowDuration : redDuration;
  if (now - stateStart_B >= phaseTime_B) {
    advanceState_B();
    stateStart_B = now;
  }

  if (Serial.available() && Serial.read() == 's') {
    showStatus();
  }
}

void advanceState_A() {
  digitalWrite(RED_A, LOW); digitalWrite(YELLOW_A, LOW); digitalWrite(GREEN_A, LOW);
  switch (stateA) {
    case GREEN_PHASE:
      stateA = YELLOW_PHASE;
      digitalWrite(YELLOW_A, HIGH);
      Serial.println("A → YELLOW");
      break;
    case YELLOW_PHASE:
      stateA = RED_PHASE;
      digitalWrite(RED_A, HIGH);
      Serial.println("A → RED");
      vehiclesWaiting_A = 0;
      break;
    case RED_PHASE:
      stateA = GREEN_PHASE;
      digitalWrite(GREEN_A, HIGH);
      Serial.print("A → GREEN for ");
      Serial.print(greenDuration_A / 1000);
      Serial.println("s");
      break;
  }
}

void advanceState_B() {
  digitalWrite(RED_B, LOW); digitalWrite(YELLOW_B, LOW); digitalWrite(GREEN_B, LOW);
  switch (stateB) {
    case GREEN_PHASE:
      stateB = YELLOW_PHASE;
      digitalWrite(YELLOW_B, HIGH);
      Serial.println("B → YELLOW");
      break;
    case YELLOW_PHASE:
      stateB = RED_PHASE;
      digitalWrite(RED_B, HIGH);
      Serial.println("B → RED");
      vehiclesWaiting_B = 0;
      break;
    case RED_PHASE:
      stateB = GREEN_PHASE;
      digitalWrite(GREEN_B, HIGH);
      Serial.print("B → GREEN for ");
      Serial.print(greenDuration_B / 1000);
      Serial.println("s");
      break;
  }
}

void showStatus() {
  Serial.println("\n=== TRAFFIC STATUS ===");
  Serial.print("A: "); Serial.println(stateA == GREEN_PHASE ? "GREEN" : stateA == YELLOW_PHASE ? "YELLOW" : "RED");
  Serial.print("  Vehicles: "); Serial.println(vehiclesWaiting_A);
  Serial.print("B: "); Serial.println(stateB == GREEN_PHASE ? "GREEN" : stateB == YELLOW_PHASE ? "YELLOW" : "RED");
  Serial.print("  Vehicles: "); Serial.println(vehiclesWaiting_B);
  Serial.println("======================\n");
}