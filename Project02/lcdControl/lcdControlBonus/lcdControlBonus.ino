 #include <LiquidCrystal.h>
 //Initialize lib with interface pins
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

 int  potPin = A0;
 int  ledPin = 6;
//  int  potValue = 0;
 int  brightness = -1;

void setup() {
  // put your setup code here, to run once:
  //set up number of columns and rows on LCD
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  lcd.begin(16, 2);
  Serial.println("Enter a value from 0 to 255");
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("We're Team 5");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Input value");
  lcd.setCursor(0, 1);
  lcd.print("from 0 to 255");
}


void loop()
{
  while (!Serial.available()){ // This while loop helps us to wait until the first value is given
  }

  brightness = Serial.parseInt();
  if (brightness >= 0 && brightness < 256)
  {
    brightness;
    lcd.clear();
    analogWrite(ledPin, brightness);
    Serial.print("LED Brightness is set to: ");
    Serial.println(brightness);
    lcd.print("Brightness");
    lcd.setCursor(0, 1);
    lcd.print("value: ");
    lcd.print(brightness);
  }
  else
  {
    lcd.clear();
    Serial.println("Input valid number");
    lcd.setCursor(0, 0);
    lcd.print("Please input");
    lcd.setCursor(0, 1);
    lcd.print("valid number");
  }
  while (Serial.available())
  {
  Serial.read(); // This while loop helps us to wait until a new value is given
  }
}
