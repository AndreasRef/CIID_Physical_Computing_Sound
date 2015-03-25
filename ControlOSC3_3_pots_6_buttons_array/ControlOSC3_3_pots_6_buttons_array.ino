int buttonPin[] = {13, 12, 11, 10, 9, 8};     // the number of the pushbutton pin

int const potCh1 = A0; // analog pin used to connect the potentiometer
int const potCh2 = A1; // analog pin used to connect the potentiometer
int const potCh3 = A2; // analog pin used to connect the potentiometer


boolean currentState[] = {LOW, LOW, LOW, LOW, LOW, LOW};//stroage for current button state

boolean lastState[] = {LOW, LOW, LOW, LOW, LOW, LOW};//storage for last button state

int currentMode[] = {0, 0, 0, 0, 0, 0};

int potVal1;  // variable to read the value from the analog pin
int potVal2;  // variable to read the value from the analog pin
int potVal3;  // variable to read the value from the analog pin

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin[0], INPUT);
  pinMode(buttonPin[1], INPUT);
  pinMode(buttonPin[2], INPUT);
  pinMode(buttonPin[3], INPUT);
  pinMode(buttonPin[4], INPUT);
  pinMode(buttonPin[5], INPUT);
}

void loop() {
  buttonPress(0, 5);
  buttonPress(1, 5);
  buttonPress(2, 5);
  buttonPress(3, 3);
  buttonPress(4, 3);
  buttonPress(5, 3);
  potVal1 = analogRead(potCh1);
  potVal2 = analogRead(potCh2);
  potVal3 = analogRead(potCh3);

  Serial.print(potVal1);
  Serial.print(",");                   
  Serial.print(potVal2);
  Serial.print(",");                   
  Serial.print(potVal3);
  Serial.print(",");                   
  Serial.print(currentMode[0]);
  Serial.print(",");   
  Serial.print(currentMode[1]);
  Serial.print(",");   
  Serial.print(currentMode[2]);
  Serial.print(",");    
  Serial.print(currentMode[3]);
  Serial.print(",");   
  Serial.print(currentMode[4]);
  Serial.print(",");   
  Serial.println(currentMode[5]);
  delay(10);                           // delay before sending the next set

}

void buttonPress(int buttonNumber, int options) {
  currentState[buttonNumber] = digitalRead(buttonPin[buttonNumber]);

  if (currentState[buttonNumber] == HIGH && lastState[buttonNumber] == LOW) { //if button has just been pressed
    currentMode[buttonNumber]++;
    if (currentMode[buttonNumber] >= options) {
      currentMode[buttonNumber] = 0;
    }
    delay(1);//crude form of button debouncing
  } else if (currentState[buttonNumber] == LOW && lastState[buttonNumber] == HIGH) {
    delay(1);//crude form of button debouncing
  }
  lastState[buttonNumber] = currentState[buttonNumber];
}

