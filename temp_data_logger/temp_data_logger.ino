// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

int buttonCreate = 2;
int buttonClose = 3;
int led =7;

unsigned long termocoupleTime;
unsigned long readTime = 500;

float temperature;

int lastStateCreateButton;
int lastStateCloseButton;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);

  pinMode(buttonCreate, INPUT_PULLUP); 
  pinMode(buttonClose, INPUT_PULLUP);
  digitalWrite(buttonCreate, HIGH);
  digitalWrite(buttonClose, HIGH);

  pinMode(led, OUTPUT);
  


  lastStateCreateButton = digitalRead(buttonCreate);
  lastStateCloseButton = digitalRead(buttonClose);
  
  Serial.println("MAX6675 correct");
  // wait for MAX chip to stabilize
  delay(500);
  
}

void loop() {

  if(millis() - termocoupleTime >= readTime){
    continuousTermocoupleRead();  
    }

  int buttonState = digitalRead(buttonCreate);
  
  if(digitalRead(buttonState == LOW)){
   //Serial.println("no apretaste el boton");
   digitalWrite(led, LOW);
  } else{
    digitalWrite(7,HIGH);
    Serial.println("creatting file");
    delay(1000);
  }



}

void continuousTermocoupleRead(){
   Serial.print("C = "); 
   readTemperature();
   //delay(250);
   termocoupleTime = millis();
   
}

void readTemperature(){
  temperature = thermocouple.readCelsius();
  Serial.println(temperature);
  
}
