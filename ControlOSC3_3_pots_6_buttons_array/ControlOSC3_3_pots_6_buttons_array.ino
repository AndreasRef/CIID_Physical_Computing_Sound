int pins[] = {0, 1, 2, 13, 12, 11, 10, 9, 8}; // 0-2 vol, 3-5 wave, 6-8 envelope
int options[] = {0, 0, 0, 5, 5, 5, 3, 3, 3}; // 0-2 vol, 3-5 wave, 6-8 envelope
int currReadings[] = {0,0,0,0,0,0,0,0,0};
int prevReadings[] = {0,0,0,0,0,0,0,0,0};
int values[] = {0,0,0,0,0,0,0,0,0};

boolean reset = false;

boolean currentState[] = {LOW, LOW, LOW, LOW, LOW, LOW};//stroage for current button state
boolean lastState[] = {LOW, LOW, LOW, LOW, LOW, LOW};//storage for last button state
int currentMode[] = {0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  for(int i=3; i<9; i++){
    pinMode(pins[i], INPUT);
  }
}

void loop() {
  for(int i=0; i<3; i++){
    currReadings[i] = analogRead(pins[i]);
    if (abs(currReadings[i] - prevReadings[i]) > 20){
      reset = true;
    }
  }
  for(int i=3; i<9; i++){
    readButton(i);
    if(currReadings[i] != prevReadings[i]){
      reset = true;
    }
  }
  if(reset == true){
//    Serial.print("readings: "); 
//    for(int i=0; i<9; i++){
//      Serial.print(currReadings[i]); 
//      Serial.print(","); 
//    }
//    Serial.println(); 
    parseWave(3);
    parseWave(4);
    parseWave(5);
    parseEnvelope(6);
    parseEnvelope(7);
    parseEnvelope(8);
    parseVol(0);
    parseVol(1);
    parseVol(2);

    for(int i=0; i<8; i++){
      Serial.print(values[i]);
      Serial.print(","); 
    }
    Serial.println(values[8]);

    for(int i=0; i<9; i++){
      prevReadings[i] = currReadings[i];
    }
    reset = false;
  }

}

void readButton(int number) {
  currentState[number-3] = digitalRead(pins[number]);

  if (currentState[number-3] == HIGH && lastState[number-3] == LOW) { //if button has just been pressed
    currReadings[number]++;

    if (currReadings[number] >= options[number]) {
      currReadings[number] = 0;
    }
    delay(1);//crude form of button debouncing
  } else if (currentState[number-3] == LOW && lastState[number-3] == HIGH) {
    delay(1);//crude form of button debouncing
  }
  lastState[number-3] = currentState[number-3];

}

void parseWave(int number){
  if(currReadings[number]==0 ){
    values[number] = 96; // noise
  }
  else if(currReadings[number]==1 ){
    values[number] = 90; // triangular wave
  }
  else if(currReadings[number]==2 ){
    values[number] = 65; // square wave
  }
  else if(currReadings[number]==3 ){
    values[number] = 43; // saw wave
  }
  else if(currReadings[number]==4 ){
    values[number] = 0; // sine wave
  }
  else{
    values[number] = 127;
  }
}

void parseEnvelope(int number){
  if(currReadings[number]==0 ){
    values[number] = 48; // short envelope
  }
  else if(currReadings[number]==1 ){
    values[number] = 70; // medium envelope
  }
  else if(currReadings[number]==2 ){
    values[number] = 90; // long envelope
  }
  else{
    values[number] = 0;
  }
}

void parseVol(int number){
  if(values[number+3] == 127 || values[number+6] == 0){
    values[number] = 0;
  }
  else{
    if (values[number+3] == 0){
      values[number] = currReadings[number] * 1;
    }
    else if(values[number+3] == 90){
      values[number] = currReadings[number] * 1;
    }
    else if(values[number+3] == 96){
      values[number] = currReadings[number] * 0.8;
    }
    else{
      values[number] = currReadings[number] * 0.9;
    }
    values[number] = constrain(values[number], 0, 1023);
  }
}
