import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

import processing.serial.*;              // import the Serial library
Serial myPort;        // The serial port
int reciveVal0 = 0;
int reciveVal1 = 0;
int reciveVal2 = 0;

int reciveVal3 = 0;
int reciveVal4 = 0;
int reciveVal5 = 0;

int reciveVal6 = 0;
int reciveVal7 = 0;
int reciveVal8 = 0;


int wave1 = 0;
int wave2 = 0;
int wave3 = 0;
int waveVal[] = {0, 43, 65, 90, 96};



int decay1 = 0;
int decay2 = 0;
int decay3 = 0;
int decayVal[] = {55,70,90};


void setup() {
  size(640, 480);       // set the size of the applet window

  frameRate(25);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 12000);
  myRemoteLocation = new NetAddress("127.0.0.1", 9001);

  // List all the available serial ports
  println(Serial.list());
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[2], 9600); // 
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);


//add wave presets to Channel 1
switch(reciveVal3) {
  case 0: 
    wave1 = waveVal[0];
    break;
  case 1: 
    wave1 = waveVal[1];
    break;
  case 2:  
    wave1 = waveVal[2];
    break;
  case 3:  
    wave1 = waveVal[3];
    break;
  case 4:  
    wave1 = waveVal[4];
    break;
}


//add wave presets to Channel 2
switch(reciveVal4) {
  case 0: 
    wave2 = waveVal[0];
    break;
  case 1: 
    wave2 = waveVal[1];
    break;
  case 2:  
    wave2 = waveVal[2];
    break;
  case 3:  
    wave2 = waveVal[3];
    break;
  case 4:  
    wave2 = waveVal[4];
    break;
}


//add wave presets to Channel 3
switch(reciveVal5) {
  case 0: 
    wave3 = waveVal[0];
    break;
  case 1: 
    wave3 = waveVal[1];
    break;
  case 2:  
    wave3 = waveVal[2];
    break;
  case 3:  
    wave3 = waveVal[3];
    break;
  case 4:  
    wave3 = waveVal[4];
    break;
}



//add envelope presets to Channel 1
switch(reciveVal6) {
  case 0: 
    decay1 = decayVal[0];
    break;
  case 1: 
    decay1 = decayVal[1];
    break;
  case 2:  
    decay1 = decayVal[2];
    break;
}

switch(reciveVal7) {
  case 0: 
    decay2 = decayVal[0];
    break;
  case 1: 
    decay2 = decayVal[1];
    break;
  case 2:  
    decay2 = decayVal[2];
    break;
}

switch(reciveVal8) {
  case 0: 
    decay3 = decayVal[0];
    break;
  case 1: 
    decay3 = decayVal[1];
    break;
  case 2:  
    decay3 = decayVal[2];
    break;
}


  OscMessage volumeMessage = new OscMessage("/volume");
  volumeMessage.add(reciveVal0); /* add an int to the osc message */
  volumeMessage.add(reciveVal1); /* add an int to the osc message */
  volumeMessage.add(reciveVal2); /* add an int to the osc message */
    /* send the message */
  oscP5.send(volumeMessage, myRemoteLocation);
  
  
  OscMessage wavesMessage = new OscMessage("/waves");
  wavesMessage.add(wave1); /* add an int to the osc message */
  wavesMessage.add(wave2); /* add an int to the osc message */
  wavesMessage.add(wave3); /* add an int to the osc message */
    /* send the message */
  oscP5.send(wavesMessage, myRemoteLocation);
  
//    myMessage.add(mouseX/4); /* add an int to the osc message */
//    myMessage.add(mouseY/4); /* add an int to the osc message */
//    myMessage.add((mouseX+mouseY)/8); /* add an int to the osc message */
//    myMessage.add(abs(mouseX-mouseY)/4); /* add an int to the osc message */

  OscMessage envelopeMessage = new OscMessage("/envelope");
    envelopeMessage.add(decay1); /* add an int to the osc message */
    envelopeMessage.add(decay2); /* add an int to the osc message */
    envelopeMessage.add(decay3); /* add an int to the osc message */
      /* send the message */
  oscP5.send(envelopeMessage, myRemoteLocation);


//    myMessage.add(attack2); /* add an int to the osc message */
//    myMessage.add(decay2); /* add an int to the osc message */
//    myMessage.add(sustain2); /* add an int to the osc message */
//    myMessage.add(release2); /* add an int to the osc message */
  

  

  
  
}

// serialEvent  method is run automatically whenever the buffer reaches the byte value set by bufferUntil():
void serialEvent(Serial thisPort) { 

  // read the serial buffer:
  String inputString = thisPort.readStringUntil('\n');

  //try to get something out
  println(inputString);

  if (inputString != null)
  {
    // trim the carrige return and linefeed from the input string:
    inputString = trim(inputString);

    // split the input string at the commas
    // and convert the sections into integers:
    int sensors[] = int(split(inputString, ','));

    // if we have received all the sensor values, use them:
    if (sensors.length == 9) {
      reciveVal0 = sensors[0];
      reciveVal1 = sensors[1];
      reciveVal2 = sensors[2];
      reciveVal3 = sensors[3];
      reciveVal4 = sensors[4];
      reciveVal5 = sensors[5];
      reciveVal6 = sensors[6];
      reciveVal7 = sensors[7];
      reciveVal8 = sensors[8];


      println(reciveVal0);
      println(reciveVal1);
      println(reciveVal2);
      println(reciveVal3);
      println(reciveVal4);
      println(reciveVal5);
      println(reciveVal6);
      println(reciveVal7);
      println(reciveVal8);
    }
  }
}

