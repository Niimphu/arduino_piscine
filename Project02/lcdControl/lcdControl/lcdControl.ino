 #include <LiquidCrystal.h>
 //Initialize lib with pins numbers
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

 int  potPin = A0;
 int  ledPin = 6;
 int  potValue = 0;
 int  brightness = 0;

void setup() {
  // put your setup code here, to run once:
  //set up number of columns and rows on LCD
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);

  lcd.print("Team 5");
  //Line 1 is the second row
  lcd.setCursor(0, 1);
  lcd.print("LCD Control");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Brightness");
  lcd.setCursor(0, 1);

  potValue = analogRead(potPin);
  brightness = map(potValue, 0, 1010, 0, 255);

  analogWrite(ledPin, brightness);

  lcd.print("value: ");
  lcd.print(brightness);

  delay(250);
  }
