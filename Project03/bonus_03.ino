#include <Servo.h>

Servo vroom;  // first servo motor
Servo turbo;  // second servo motor

void setup() {
  vroom.attach(3);
  turbo.attach(4);

// spin  motors three times on start up 
  for (int i = 0; i < 3; i++) {
    vroom.write(0);
    turbo.write(0);
    delay(300);
    vroom.write(180);
    turbo.write(180);
    delay(300);
  }

  vroom.write(0);
  turbo.write(0);
}

void loop() {
  // read analog values from the three sensors
  int lightValue1 = analogRead(A0);
  int lightValue2 = analogRead(A1);
  int lightValue3 = analogRead(A2);

  // find the maximum light value and corresponding sensor
  int maxLightValue = max(lightValue1, max(lightValue2, lightValue3));

  if (maxLightValue == lightValue1) {
    // turn motors towards sensor 1 (right one on the breadboard)
    vroom.write(0);  
    turbo.write(0);  
  }
  else if (maxLightValue == lightValue2) {
    // turn motors towards sensor 2 (middle one on the breadboard)
    vroom.write(90); 
    turbo.write(90); 
  }
  else {
    // turn motors towards sensor 3 (left one on the breadboard)
    vroom.write(180);
    turbo.write(180);
  }

  delay(1000);  // delay before checking again
}
