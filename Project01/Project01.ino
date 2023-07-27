#define SWITCH 2
#define GREEN 3
#define YELLOW 4
#define RED 5

int         switchState = LOW;
static bool greenMode = true;

//setup runs once on start
void  setup() {
  pinMode(SWITCH,INPUT); //pinMode() sets the mode of a digital pin on the Arduino board
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(RED,OUTPUT);
}

//loops during runtime of program
void  loop() {
  switchState = digitalRead(SWITCH);
  if (switchState == HIGH)
    switchPressed();
  if (greenMode)
    greeen();
  else
    redYellowPartyWoo();
}

void  switchPressed() {
  static unsigned long  lastSwitchPressedTime = 0;
  const unsigned long   buttonCooldown = 600;

  if (!isCooldownOver(lastSwitchPressedTime, buttonCooldown))
    return ;
  lastSwitchPressedTime = getCurrentTime();
  greenMode = (greenMode == true) ? false : true;
}

void  greeen() {
  digitalWrite(GREEN, HIGH); //digitalWrite writes digital values(HIGH,LOW) to the digital pins(like our LEDs and switch) on the Arduino board
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
}

void  redYellowPartyWoo() {
  digitalWrite(GREEN, LOW);
  redParty();
  yellowParty();
}

void  redParty() {
  static unsigned long  lastChangeTime = 0;
  const unsigned long   delay = 1000;
  static int            mode = HIGH;

  if (!isCooldownOver(lastChangeTime, delay))
    return ;
  lastChangeTime = getCurrentTime();
  mode = (mode == HIGH) ? LOW : HIGH;
  digitalWrite(RED, mode);
}

void  yellowParty() {
  static unsigned long  lastChangeTime = 0;
  const unsigned long   delay = 1000;
  static int            mode = HIGH;

  if (!isCooldownOver(lastChangeTime, delay))
    return ;
  lastChangeTime = getCurrentTime();
  mode = (mode == HIGH) ? LOW : HIGH;
  digitalWrite(YELLOW, mode);
}

bool  isCooldownOver(unsigned long lastTime, const unsigned long cooldown) {
  return (millis() - lastTime > cooldown);
}

int getCurrentTime() {
  return(millis());
}
