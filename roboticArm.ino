#include <Servo.h>
#define trigPin 5
#define echoPin 6

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
  Serial.begin(9600);
  initArm();
}

void loop() {
}

void moveArm(int rotation) {
  base.write(rotation);
  delay(1000);
}

void holdObject() {
  clamp.write(100);
  delay(1000);
}

void releaseObject(){
  clamp.write(50);
  delay(1000);
}

void armAngle(int rotation){
  armJoint.write(rotation);
  delay(1000);
}

void clampOrientation(int orientation){
  armRotation.write(orientation);  
  delay(1000);
}

void initArm(){
  moveArm(0);
  armAngle(10);
  releaseObject();
}
s
int echo(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
  return distance;  
}
