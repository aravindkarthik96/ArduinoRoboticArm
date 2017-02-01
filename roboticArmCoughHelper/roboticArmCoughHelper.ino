#include <Servo.h>
#define trigPin 5
#define echoPin 6
#define ledPin 4

Servo base;
Servo clamp;
Servo armJoint;
Servo armRotation;

void setup() {
  base.attach(3);
  clamp.attach(9);
  armJoint.attach(10);
  armRotation.attach(11);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  initArm();
}

void loop() {
  int value = analogRead(A0);
  Serial.println(analogRead(A0));
  if(value > 205) {
    moveArm(90);
    armAngle(40);
    holdObject();
    armAngle(20);
    moveArm(180);
    delay(500);
    clampOrientation(180);
    int hasUserCollectedTissue = 0;
    while(hasUserCollectedTissue == 0) {
      if(echo()<12) {
        releaseObject();
        clampOrientation(90);
        delay(2000);
        hasUserCollectedTissue = 1;
      }
    }
  }
}

void moveArm(int rotation) {
  base.write(rotation);
  delay(1000);
}

void holdObject() {
  clamp.write(100);
  delay(1000);
}

void releaseObject() {
  clamp.write(50);
  delay(1000);
}

void armAngle(int rotation) {
  armJoint.write(rotation);
  delay(1000);
}

void clampOrientation(int orientation) {
  armRotation.write(orientation);
  delay(1000);
}

void initArm() {
  releaseObject();
  moveArm(180);
  armAngle(20);
  ledState(true);
  delay(300);
  ledState(false);
}

void ledState(boolean state) {
  if (state) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}

int echo() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

void moveArmToLeft(int currentPos) {
  for (int pos = currentPos; pos <= 180; pos += 1) {
    base.write(pos);
    delay(10);
  }
  Serial.println(currentPos);
}

void moveArmToCenter(int currentPos) {
  for (int pos = currentPos; pos >= 90; pos -= 1) {
    base.write(pos);
    delay(10);
  }
  Serial.println(currentPos);
}

void dropObject() {
  for (int pos = 20; pos <= 60; pos += 1) {
    armJoint.write(pos);
    delay(10);
  }
  delay(300);
  releaseObject();
  delay(300);
  for (int pos = 60; pos >= 20; pos -= 1) {
    armJoint.write(pos);
    delay(10);
  }
}
