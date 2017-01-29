#include <Servo.h>

Servo base;
Servo clamp;
Servo armJoint;
Servo armRotation;

void setup() {
  base.attach(3);
  clamp.attach(9);
  armJoint.attach(10);
  armRotation.attach(11);
  initArm();
}

void loop() {
}

void moveArm(int rotation) {
  base.write(rotation);
  delay(500);
}

void holdObject() {
  clamp.write(100);
  delay(500);
}

void releaseObject(){
  clamp.write(50);
  delay(500);
}

void armAngle(int rotation){
  armJoint.write(rotation);
  delay(500);
}

void clampOrientation(int orientation){
  armRotation.write(orientation);  
}

void initArm(){
  moveArm(0);
  armAngle(10);
  releaseObject();
}
