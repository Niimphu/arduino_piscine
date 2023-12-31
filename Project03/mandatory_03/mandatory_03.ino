#include <Servo.h>

Servo motor;

void setup() {
  motor.attach(4); // first motor
  motor.write(0); // second motor
}

void loop() {
  // read analog values from the three sensors
  int lightValue1 = analogRead(A0);
  int lightValue2 = analogRead(A1);
  int lightValue3 = analogRead(A2);

  // find the maximum light value and corresponding sensor
  int maxLightValue = max(lightValue1, max(lightValue2, lightValue3));

  //motor continiously moves until we can determine where is the light source
  if (lightValue1 < 250 && lightValue2 < 250 && lightValue3 < 250) {
    motor.write(0);
    delay(700);
    motor.write(90);
    delay(700);
    motor.write(180);
    delay(700);
    motor.write(90);
    delay(700);
  }

//show which sensor is closest to light source
  if (maxLightValue >= 800) {
	if (maxLightValue == lightValue1) {
	// turn motor towards sensor 1 (right one on the breadboard)
	motor.write(180);
	}
	else if (maxLightValue == lightValue2) {
	// turn motor towards sensor 2 (middle one on the breadboard)
	motor.write(90);
	}
	else {
	// turn motor towards sensor 3 (left one on the breadboard)
	motor.write(0);
	}

  delay(700);  // delay before checking again
  }
}
