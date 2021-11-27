#include "max6675.h"


int thermoDO = 7;
int thermoCS = 6;
int thermoCLK = 5;

int buttonCreate = 2;
int buttonClose = 3;
int led = 4;

unsigned long termocoupleTime;
unsigned long readTime = 1000;

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
  float temp_1;
  
  if(millis() - termocoupleTime >= readTime){
    continuousTermocoupleRead();  
    }

   temp_1 = thermocouple.readCelsius();



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
