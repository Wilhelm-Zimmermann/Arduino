// LEDS
const int LED_01 = 2;
const int LED_02 = 3;
const int LED_03 = 4;

// PUSH BUTTONS
const int PUSH_BTN_01 = 12;
const int PUSH_BTN_02 = 11;
const int PUSH_BTN_03 = 10;

// BUZZER SOUND
const int TONE_GREEN = 415;
const int TONE_RED = 310;
// tenho que comprar um led azul pra deixar o jogo mais interessante
const int TONE_BLUE = 209;
const int TONE_YELLOW = 252;

// LOGIC VARS
const int BUZZER = 9;
bool isGameOver = true;
bool isGuessing = false;
bool isMountingSequence = true;
int ledPos = 0;
int guessPos = 0;
int simonLeds[10];
void buttonLedMap();
void initialConfig();
void pushSimonLed();
void blinkLedSequence();
void handleGameWon();
void handleGameOver();
void clearSimonSequence();
void generateRandomSequence();
void guessSequence(int value);
void buzzerToneSound(int value);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initialConfig();
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonLedMap();
  if(!isGuessing && !isGameOver) {
    // pushSimonLed();
    generateRandomSequence();
  }
}

void buttonLedMap() {
  int button1 = digitalRead(PUSH_BTN_01);
  int button2 = digitalRead(PUSH_BTN_02);
  int button3 = digitalRead(PUSH_BTN_03);
  bool anyButtonHasPressed = (button1 == HIGH || button2 == HIGH || button3 == HIGH);
  if(isGuessing && !isMountingSequence) {
    digitalWrite(LED_01, button1);
    digitalWrite(LED_02, button2);
    digitalWrite(LED_03, button3);
  }

  int sequenceValue = button1 == HIGH ? 2
    : button2 == HIGH ? 3
    : button3 == HIGH ? 4
    : 0;

  if(anyButtonHasPressed) {
    buzzerToneSound(sequenceValue);
  }
  if(isGuessing && !isGameOver && !isMountingSequence && anyButtonHasPressed) {
    guessSequence(sequenceValue);
  }
  if(isGameOver && anyButtonHasPressed){
    isGameOver = false;
  }
}

void pushSimonLed() {
  isMountingSequence = true;
  int arrLength = sizeof(simonLeds)/sizeof(simonLeds[0]);
  if(ledPos >= arrLength) {
    handleGameWon();
    isGameOver = true;
    isGuessing = false;
    return;
  }
  int randomNumber = random(2, 5);
  simonLeds[ledPos] = randomNumber;
  ledPos += 1;
  blinkLedSequence();
}

void blinkLedSequence() {
  digitalWrite(LED_01, LOW);
  digitalWrite(LED_02, LOW);
  digitalWrite(LED_03, LOW);
  delay(1000);
  int arrLength = sizeof(simonLeds)/sizeof(simonLeds[0]);
  for(int i = 0; i < arrLength;i++) {
    if(simonLeds[i] == 0) {
      break;
    }
    buzzerToneSound(simonLeds[i]);
    digitalWrite(simonLeds[i], HIGH);
    delay(300);
    digitalWrite(simonLeds[i], LOW);
    delay(300);
  }
  isGuessing = true;
  isMountingSequence = false;
}

void generateRandomSequence() {
  isMountingSequence = true;
  int arrLength = sizeof(simonLeds)/sizeof(simonLeds[0]);
  if(ledPos >= arrLength) {
    handleGameWon();
    isGameOver = true;
    isGuessing = false;
    return;
  }
  for(int i = 0; i <= ledPos; i++) {
    int randomNumber = random(2, 5);
    Serial.println(randomNumber);
    simonLeds[i] = randomNumber;
  }
  ledPos += 1;
  blinkLedSequence();
}

void initialConfig() {
  randomSeed(analogRead(0));
  pinMode(PUSH_BTN_01, INPUT);
  pinMode(PUSH_BTN_02, INPUT);
  pinMode(PUSH_BTN_03, INPUT);
  pinMode(LED_01, OUTPUT);
  pinMode(LED_02, OUTPUT);
  pinMode(LED_03, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void guessSequence(int value){
  if(simonLeds[guessPos] != value) {
    handleGameOver();
    return;
  }

  if(guessPos < ledPos) {
    guessPos += 1;
  } 
  if(guessPos == ledPos) {
    guessPos = 0;
    isGuessing = false;
    delay(100);
  }
  delay(500);
}

void buzzerToneSound(int value) {
  if(value == 2) tone(BUZZER, TONE_RED, 500);
  if(value == 3) tone(BUZZER, TONE_GREEN, 500);
  if(value == 4) tone(BUZZER, TONE_YELLOW, 500);
}

void handleGameOver() {
  clearSimonSequence();
  Serial.println("GAME OVERRR LOOOOOOSER!!!");
  digitalWrite(BUZZER, HIGH);
  delay(2000);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_01, HIGH);
  digitalWrite(LED_02, HIGH);
  digitalWrite(LED_03, HIGH);
  delay(2000);
  digitalWrite(LED_01, LOW);
  digitalWrite(LED_02, LOW);
  digitalWrite(LED_03, LOW);
}

void handleGameWon(){
  clearSimonSequence();
  Serial.println("YOU WON THE GAME, BUT NOBODY CARES ABOUT IT!!!!");
  for(int i = 0; i < 10; i++) {
    digitalWrite(LED_01, HIGH);
    digitalWrite(LED_02, HIGH);
    digitalWrite(LED_03, HIGH);
    delay(300);
    digitalWrite(LED_01, LOW);
    digitalWrite(LED_02, LOW);
    digitalWrite(LED_03, LOW);
    delay(300);
  }
}

void clearSimonSequence(){
  isGuessing = false;
  guessPos = 0;
  ledPos = 0;
  int arrLength = sizeof(simonLeds)/sizeof(simonLeds[0]);
  for(int i = 0; i < arrLength;i++) {
    simonLeds[i] = 0;
  }
  isGameOver = true;
}
