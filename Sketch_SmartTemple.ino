#define TRIG 8
#define ECHO 9
#define PIR_PIN 12
#define LDR_PIN A0

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int relays[6] = {2, 3, 4, 5, 6, 7};
int relayCount = sizeof(relays) / sizeof(relays[0]);

// Relay ON schedule (milliseconds after cycle starts)
unsigned long relayOnTimes[6] = {
  100,        // Relay 1 -> start
  62000,      // Relay 2 -> after 1 min 2 sec
  135000,     // Relay 3 -> after 2 min 15 sec
  180000,     // Relay 4 -> after 3 min
  200000,     // Relay 5 -> after 3 min 20 sec
  240000      // Relay 6 -> after 4 min
};

bool relayState[6] = {false, false, false, false, false, false};
bool cycleRunning = false;
unsigned long cycleStartTime = 0;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PIR_PIN, INPUT);

  for (int i = 0; i < relayCount; i++) {
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH); // OFF initially
  }

  mySerial.begin(9600);
  if (myDFPlayer.begin(mySerial)) {
    myDFPlayer.volume(25); // Set volume
  }
}

void loop() {
  // ---- Read sensors ----
  int ldrValue = analogRead(LDR_PIN);  // smaller value = darker
  bool motion = digitalRead(PIR_PIN);

  // Ultrasonic
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 20000);
  int distance = duration * 0.034 / 2;

  // ---- Start cycle if dark + motion + object detected ----
  if (ldrValue < 500 && motion && distance > 0 && distance < 30 && !cycleRunning) {
    cycleRunning = true;
    cycleStartTime = millis();
    for (int i = 0; i < relayCount; i++) relayState[i] = false;
    myDFPlayer.play(1); // play first track
  }

  // ---- Cycle running ----
  if (cycleRunning) {
    unsigned long elapsed = millis() - cycleStartTime;

    // Turn on relays according to schedule
    for (int i = 0; i < relayCount; i++) {
      if (!relayState[i] && elapsed >= relayOnTimes[i]) {
        digitalWrite(relays[i], LOW); // ON
        relayState[i] = true;
      }
    }

    // After 4 minutes stop everything
    if (elapsed >= 240000) {
      for (int i = 0; i < relayCount; i++) {
        digitalWrite(relays[i], HIGH); // OFF
        relayState[i] = false;
      }
      myDFPlayer.stop();
      cycleRunning = false;
    }
  }
}
