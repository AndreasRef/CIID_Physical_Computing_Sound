import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

import processing.serial.*;              // import the Serial library
Serial myPort;        // The serial port

int values[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0
};


void setup() {

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
  OscMessage volumeMessage = new OscMessage("/volume");
  volumeMessage.add(values[0]); /* add an int to the osc message */
  volumeMessage.add(values[1]); /* add an int to the osc message */
  volumeMessage.add(values[2]); /* add an int to the osc message */
  /* send the message */
  oscP5.send(volumeMessage, myRemoteLocation);


  OscMessage wavesMessage = new OscMessage("/waves");
  wavesMessage.add(values[3]); /* add an int to the osc message */
  wavesMessage.add(values[4]); /* add an int to the osc message */
  wavesMessage.add(values[5]); /* add an int to the osc message */
  /* send the message */
  oscP5.send(wavesMessage, myRemoteLocation);

  OscMessage envelopeMessage1 = new OscMessage("/envelope1");
  envelopeMessage1.add(values[6]); /* add an int to the osc message */
  /* send the message */
  oscP5.send(envelopeMessage1, myRemoteLocation);
  
  OscMessage envelopeMessage2 = new OscMessage("/envelope2");
  envelopeMessage2.add(values[7]); /* add an int to the osc message */
  /* send the message */
  oscP5.send(envelopeMessage2, myRemoteLocation);
  
  OscMessage envelopeMessage3 = new OscMessage("/envelope3");
  envelopeMessage3.add(values[8]); /* add an int to the osc message */
  /* send the message */
  oscP5.send(envelopeMessage3, myRemoteLocation);
  
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
      for (int i=0; i<9; i++) {
        values[i] = sensors[i];
      }
    }
  }
}

