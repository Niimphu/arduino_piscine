#include <Servo.h>

Servo leftright;  // first motor
Servo updown;  // second motor

void setup() {
  leftright.attach(4); //attach output for motors to pins 3 and 4
  updown.attach(3);

  leftright.write(0); //set motors in default position at 0 degrees
  updown.write(0);
}

void loop() {
  // read analog values from the three sensors
  int lightValue1 = analogRead(A0);
  int lightValue2 = analogRead(A1);
  int lightValue3 = analogRead(A2);

  // find the maximum light value and corresponding sensor
  int maxLightValue = max(lightValue1, max(lightValue2, lightValue3));

  //motors continiously move until we can determine where it is
  if (lightValue1 < 100 && lightValue2 < 100 && lightValue3 < 100) {
    leftright.write(0);
    updown.write(0);
    delay(700);
    leftright.write(90);
    updown.write(90);
    delay(700);
    leftright.write(180);
    updown.write(180);
    delay(700);
    leftright.write(90);
    updown.write(90);
    delay(700);
  }

  //motor 1: works horisontally, shows which sensor is closest to light source
  if (maxLightValue >= 800) {
    if (maxLightValue == lightValue1) {
      // turn leftrights towards sensor 1 (right one on the breadboard)
      leftright.write(0);
    }
    else if (maxLightValue == lightValue2) {
      // turn leftrights towards sensor 2 (middle one on the breadboard)
      leftright.write(90);
    }
    else {
      // turn leftrights towards sensor 3 (left one on the breadboard)
      leftright.write(180);
    }
  }

  //motor 2: works vertically, shows how far is the light source from the sensor
    if (maxLightValue < 800){
      updown.write(0);
    }
    else if (maxLightValue < 1000){
      updown.write(45);
    }
    else if (maxLightValue < 1100){
      updown.write(90);
    }
    else if (maxLightValue < 1300){
      updown.write(135);
    }
    else {
      updown.write(180);
    }

    delay(700);  // delay before checking input again
  }
