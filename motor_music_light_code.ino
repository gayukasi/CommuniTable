/* 
  IR Breakbeam sensor demo!
*/
#include <Stepper.h>
#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 30  //Number of Neopixels
#define PIN 6 //Neopixel input data pin
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;
const int X_pin = 1; // analog pin connected to X output
int flag;
int numOfPpl;
boolean Click_1=false;
boolean Click_2=false;
boolean Click_3=false;
boolean Click_4=false;

#define SENSORPIN 8
// variables will change:
int sensorState = 0, lastState=0;         // variable for reading the pushbutton status
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);
// make HEAT INCREASE:

void HeatAnimate()
{
  for(int i=0; i<NUMPIXELS; i++)
  {
      if(i%2==0)
      {
        pixels.setPixelColor(i, pixels.Color(255,0,0)); //bright yellow
      }
      else
      {
        pixels.setPixelColor(i, pixels.Color(255, 191, 0)); //bright yellow
      }
      
  }
      pixels.show();
      delay(500);

  for(int i=0; i<NUMPIXELS; i++)
  {
      if(i%3==0)
      {
        pixels.setPixelColor(i, pixels.Color(204, 85, 0)); //bright yellow
      }
      else if(i%3==1)
      {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0)); //bright yellow
      }
      else
      {
        pixels.setPixelColor(i, pixels.Color(192, 64, 0)); //bright yellow
      }
      
  }
    pixels.show();
    delay(35);


}



void HeatIncrease()
{
        
        if (flag==0) {
          flag=1;
          numOfPpl++;
          //Serial.println(numOfPpl);
          //Make motor run
          myStepper.setSpeed(rolePerMinute);
          myStepper.step(90);
          ChangeColor(numOfPpl);   // Change colour based on number of people
          //Serial.println("Heat level increased by 200 C");
        }

        switch (numOfPpl) {
          case 1:  // your hand is close to the sensor
            if (Click_1 == false)
            {
              myStepper.setSpeed(rolePerMinute);
              myStepper.step(90);
              Keyboard.write('1');
              Click_1=true;
              delay(100);
            }
          break;
          case 2:  // your hand is a few inches from the sensor
            if (Click_2 == false)
            {
              Keyboard.write('2');
              Click_2=true;
              delay(100);
            }
          break;
          case 3:  // your hand is a few inches from the sensor
            if (Click_3 == false)
            {
              Keyboard.write('3');
              Click_3=true;
              delay(100);
            }
          break;
          case 4:  // your hand is a few inches from the sensor
            if (Click_4 == false)
            {
              Keyboard.write('2');
              Click_4=true;
              delay(100);
            }
          break;
        }
}

void ChangeColor(int n)
{   
  if(n<5){
    switch (n) {
          case 1:  // your hand is close to the sensor
          {
              for(int i=0; i<NUMPIXELS; i++)
              {
                pixels.setPixelColor(i, pixels.Color(35,19,0)); //dim yellow
              }
              pixels.show();
              delay(100);
          }
          break;
          case 2:  // your hand is close to the sensor
          {
              for(int i=0; i<NUMPIXELS; i++)
              {
                pixels.setPixelColor(i, pixels.Color(66,14,0)); //dim orange
              }
              pixels.show();
              delay(100);
          }
          break;  
          case 3:  // your hand is close to the sensor
          {
              for(int i=0; i<NUMPIXELS; i++)
              {
                pixels.setPixelColor(i, pixels.Color(28,2,0)); //dim red
              }
              pixels.show();
              delay(100);
          }
          break;  
          case 4:  // your hand is close to the sensor
          {
              for(int i=0; i<NUMPIXELS; i++)
              {
                pixels.setPixelColor(i, pixels.Color(55,55,55)); //dim white
              }
              pixels.show();
              delay(100);
          }
          break;       
        }

  }
  else
  {
    for(int i=0; i<NUMPIXELS; i++)
              {
                pixels.setPixelColor(i, pixels.Color(55,55,55)); //dim white
              }
              pixels.show();
              delay(100);
    
  }

}
// make HEAT DECREASE:
void HeatDecrease()
{
        if (flag==0)
        {
        flag=1;
        //Make motor run
        myStepper.setSpeed(rolePerMinute);
        myStepper.step(-90);
        Serial.println("Heat level decreased by 200 C");
        }
}
void setup() { 
  
  pixels.begin();
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(53,41,10));
  }
  pixels.show();
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup
  myStepper.setSpeed(rolePerMinute);
  Serial.begin(115200);
  flag=0;
}
void loop(){
  // read the state of the pushbutton value:
  sensorState = digitalRead(SENSORPIN);
  // joystick analog read:
  int a = analogRead(X_pin);
  //Serial.println("Joystick value:");
  //Serial.println(a);
  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW) {     
    // turn LED on:
    for( int i=0;i<3;i++)
    {
      HeatAnimate();
    }
    HeatIncrease();
    ChangeColor(numOfPpl);  
  } 
  else if ((a < 400) or (a > 530) ) 
  {
    // let joystick override
    Serial.println("a value"+ a);  
          if (a < 400)
          {
            HeatIncrease();
            Serial.println("Increase heat by ONE");
          }
          else if (a > 530)
          {
            HeatDecrease();       
            Serial.println("Decrease heat by ONE");     
            
          }
  }
  else
  {
        flag=0; 
  }
}
