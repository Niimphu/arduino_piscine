#define BUTTON 2
#define GREEN 3
#define YELLOW 4
#define RED 5

static bool     greenMode = true;
unsigned long   redDelay = 1000;
unsigned long   yellowDelay = 1000;
int             defaultRedMode = LOW;
int             defaultYellowMode = LOW;
int             redMode = defaultRedMode;
int             yellowMode = defaultYellowMode;

//setup runs once on program start
void  setup() {
  pinMode(BUTTON,INPUT); //pinMode() sets the mode of a digital pin on the Arduino board
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(RED,OUTPUT);
  startupFlash();
  bonus(0); //0 for mandatory, 1 and 2 for the bonus parts
}

//loops during runtime of program
void  loop() {
  int buttonState = digitalRead(BUTTON);

  if (buttonState == HIGH)
    buttonPressed();
  if (!greenMode)
    redYellowPartyWoo();
}

void  buttonPressed() {
  static unsigned long  lastPressedTime = 0;
  const unsigned long   buttonCooldown = 300;

  if (!isCooldownOver(lastPressedTime, buttonCooldown))
    return ;
  lastPressedTime = getCurrentTime();
  changeMode();
}

void  changeMode() {
  greenMode = !greenMode;
  if (greenMode)
  {  
    digitalWrite(GREEN, HIGH); //digitalWrite writes digital values(HIGH,LOW) to the digital pins(like our LEDs and BUTTON) on the Arduino board
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
  }
  else
  {
    digitalWrite(GREEN, LOW);
    yellowMode = defaultYellowMode;
    redMode = defaultRedMode;
  }
}

void  redYellowPartyWoo() {
  redParty();
  yellowParty();
}

void  redParty() {
  static unsigned long  lastChangeTime = 0;

  if (!isCooldownOver(lastChangeTime, redDelay))
    return ;
  lastChangeTime = getCurrentTime();
  redMode = !redMode;
  digitalWrite(RED, redMode);
}

void  yellowParty() {
  static unsigned long  lastChangeTime = 0;

  if (!isCooldownOver(lastChangeTime, yellowDelay))
    return ;
  lastChangeTime = getCurrentTime();
  yellowMode = !yellowMode;
  digitalWrite(YELLOW, yellowMode);
}

int getCurrentTime() {
  return(millis());
}

bool  isCooldownOver(unsigned long lastTime, const unsigned long cooldown) {
  return (getCurrentTime() - lastTime > cooldown);
}

void  bonus(int bonusEx) {
  if (bonusEx == 1 || bonusEx == 2)
    yellowDelay = 2000;
  if (bonusEx == 1)
  {
    defaultYellowMode = HIGH;
    redDelay = 2000;
  }
  if (bonusEx == 2)
    redDelay = 500;
}

//fun flashy colours :))))
void  startupFlash() {
  int i = 5;

  while (i--)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    delay(100);
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    delay(100);
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    delay(100);
  }
}
