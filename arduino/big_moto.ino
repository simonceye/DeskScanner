#include "EasyStepper.h"
 
// define the pins
#define STEP_PIN 4
#define DIR_PIN 3
#define EN_PIN 2
 
// define the inverted
#define DIR_PIN_INVERTED true
#define EN_PIN_INVERTED false
 
// the EasyStepper instance
EasyStepper stepper1(STEP_PIN, DIR_PIN, EN_PIN, DIR_PIN_INVERTED, EN_PIN_INVERTED);
 
// the stepps to rotate
int stepps = 200;
 
// run times
int times = 0;
 
String inputString = "";
boolean stringComplete = false;
void setup(){
  Serial.begin(9600);
  stepper1.debugMode(false);
  stepper1.startup();
  inputString.reserve(100);
}
 
void loop(){
  stepper1.run();
  if(stringComplete){
    if(inputString.charAt(0) == 's') {
      int degree = inputString.substring(1).toInt();
      stepper1.rotate(50.0, degree / 1.8);
    }else if(inputString.charAt(0) == 'd') {
      String dir = inputString.substring(1, 2);
      Serial.println(dir);
      if(dir == "1") {
        Serial.println("xxxx1");
        stepper1.setDirection(1);
      }else {
        Serial.println("xxxx2");
        stepper1.setDirection(2);
      }
    }else if(inputString.charAt(0) == 'e') {
      String command = inputString.substring(1, 2);
      if(command == "0") {
        stepper1.shutdown();
      }else {
        stepper1.startup();
      }
    }
    //Serial.println(degree);
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while(Serial.available()) {
    char inChar = (char) Serial.read();
    inputString += inChar;
    if(inChar == '\n') {
      stringComplete = true;
    }
  }
}

