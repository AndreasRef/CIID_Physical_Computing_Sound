int pins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // 0-2 vol, 3-5 wave, 6-8 envelope
int currReadings[] = {0,0,0,0,0,0,0,0,0};
int prevReadings[] = {0,0,0,0,0,0,0,0,0};
int values[] = {0,0,0,0,0,0,0,0,0};

boolean reset = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i=0; i<9; i++){
    currReadings[i] = analogRead(pins[i]);
    if (abs(currReadings[i] - prevReadings[i]) > 20){
      reset = true;
    }
  }
  if(reset == true){
    Serial.print("readings: "); 
    for(int i=0; i<9; i++){
      Serial.print(currReadings[i]); 
      Serial.print(","); 
    }
    Serial.println(); 
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

void parseWave(int number){
  if(currReadings[number]>70 && currReadings[number]<95 ){
    values[number] = 96; // noise
  }
  else if(currReadings[number]>125 && currReadings[number]<160 ){
    values[number] = 90; // triangular wave
  }
  else if(currReadings[number]>453 && currReadings[number]<514 ){
    values[number] = 65; // square wave
  }
  else if(currReadings[number]>515 && currReadings[number]<660 ){
    values[number] = 43; // saw wave
  }
  else if(currReadings[number]>720 && currReadings[number]<845 ){
    values[number] = 0; // sine wave
  }
  else{
    values[number] = 127;
  }
}

void parseEnvelope(int number){
  if(currReadings[number]>70 && currReadings[number]<95 ){
    values[number] = 55; // short envelope
  }
  else if(currReadings[number]>453 && currReadings[number]<514 ){
    values[number] = 70; // medium envelope
  }
  else if(currReadings[number]>720 && currReadings[number]<845 ){
    values[number] = 90; // long envelope
  }
  else{
    values[number] = 0;
  }
}

void parseVol(int number){
  if(values[number+3] == 127 || values[number+6] == 0){
    values[number] = 0;
    Serial.println("invalid wave or length");
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
