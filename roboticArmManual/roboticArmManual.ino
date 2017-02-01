#include <Servo.h>
#define trigPin 5
#define echoPin 6
#define ledPin 4

Servo base;
Servo clamp;
Servo armJoint;
Servo armRotation;
int angle;
int rotation;
int orientation;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  initArm();
  angle = 20;
  rotation = 180;
  orientation = 0;
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 's' & angle < 90) {
      angle = angle + 10;
      armAngle(angle);
      Serial.print("changing arm angle to ");
      Serial.println(angle);
    }
    else if (command == 'w' & angle > 20) {
      angle = angle - 10;
      armAngle(angle);
      Serial.print("changing arm angle to ");
      Serial.println(angle);
    }
    else if (command == 'd' & rotation > 0) {
      rotation = rotation - 10;
      moveArm(rotation);
      Serial.print("rotating arm to ");
      Serial.println(rotation);
    }
    else if (command == 'a' & rotation < 180) {
      rotation = rotation + 10;
      moveArm(rotation);
      Serial.print("rotating arm to ");
      Serial.println(rotation);
    }
    else if (command == 'c' & rotation > 0) {
      rotation = rotation - 20;
      moveArm(rotation);
      Serial.print("rotating arm to ");
      Serial.println(rotation);
    }
    else if (command == 'z' & rotation < 180) {
      rotation = rotation + 20;
      moveArm(rotation);
      Serial.print("rotating arm to ");
      Serial.println(rotation);
    }
    else if (command == 'e' & orientation > 0) {
      orientation = orientation - 20;
      clampOrientation(orientation);
      Serial.print("rotating arm to ");
      Serial.println(orientation);
    }
    else if (command == 'q' & orientation < 90) {
      orientation = orientation + 20;
      clampOrientation(orientation);
      Serial.print("orienting arm to ");
      Serial.println(orientation);
    }
    else if (command == 'f') {
      holdObject();
    }
    else if (command == 'r') {
      releaseObject();
    }
    else if (command == 'o') {
      powerOff();
    }
    else if (command == 'p') {
      init();
    }
    else {
      Serial.println("Sorry, cannot move further");
    }
  }
}

void moveArm(int rotation) {
  base.write(rotation);
  delay(100);
}

void holdObject() {
  clamp.write(100);
  delay(100);
}

void releaseObject() {
  clamp.write(50);
  delay(100);
}

void armAngle(int rotation) {
  armJoint.write(rotation);
  delay(100);
}

void clampOrientation(int orientation) {
  armRotation.write(orientation);
  delay(1000);
}

void initArm() {
  base.attach(3);
  clamp.attach(9);
  armJoint.attach(10);
  armRotation.attach(11);
  moveArm(180);
  armAngle(20);
  releaseObject();
  ledState(true);
  delay(300);
  ledState(false);
}

void detachServos() {
  base.detach();
  clamp.detach();
  armJoint.detach();
  armRotation.detach();
}

void powerOff(){
  ledState(false);
  holdObject();
  moveArm(0);
  armAngle(90);  
  delay(2000);
  detachServos();
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
