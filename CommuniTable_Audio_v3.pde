import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.spi.*;
import ddf.minim.ugens.*;

import processing.sound.*;
SoundFile file;

import processing.serial.*;
Serial port;    // Create an object from Serial class
String val;     // Data received from the serial port

// create a SoundFile object for each stem file
SoundFile stem1;
SoundFile stem2;
SoundFile stem3;
SoundFile stem4;
SoundFile burningSound;

// set initial volume for each stem file
float volume1;
float volume2;
float volume3;
float volume4;

void setup() {
  size(400, 400);
  port = new Serial(this, "/dev/tty.usbmodemHIDPC1", 115200);
  
  // create a SoundFile object for each stzem file
  stem1 = new SoundFile(this, "ES_Stockholm Love STEMS DRUMS.wav");
  stem2 = new SoundFile(this, "ES_Stockholm Love STEMS BASS.wav");
  stem3 = new SoundFile(this, "ES_Stockholm Love STEMS MELODY.wav");
  burningSound = new SoundFile(this, "Burning sound.WAV");
  //stem4 = new SoundFile(this, "ES_Stockholm Love STEMS INSTRUMENTS.wav");
    
  // set initial volume for each stem file
  //volume1 = 0.0;
  //volume2 = 0.0;
  //volume3 = 0.0;
  //volume4 = 0.0;

}

void draw() {
}

void keyPressed() {
  if (key == '1') { // Replace with the keystroke sent by your Arduino
    stem1.amp(0);
    stem2.amp(1);
    stem3.amp(0);
    burningSound.amp(1); //might need to adjust the volume
    
    stem1.play();
    stem2.play();
    stem3.play();
    burningSound.play();
  } else if (key == '2') {
    //unmute 2 layers
    stem1.amp(1);
    stem2.amp(1);
    stem3.amp(0);
    burningSound.play();
  } else if (key == '3') {
    //unmute 3 layers
    stem1.amp(1);
    stem2.amp(1);
    stem3.amp(1);
    burningSound.play();
  } else if (key == '0') {
    stem1.stop();
    stem2.stop();
    stem3.stop();
    burningSound.stop();
  }
}
