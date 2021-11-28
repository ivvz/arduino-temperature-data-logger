#include "max6675.h"  
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>


#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);


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

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  //display.drawBitmap(0,0,logo,128,64,1);
  //display.display();
  delay(1000);

  Serial.println("MAX6675 correct");
  delay(500);
  // wait for MAX chip to stabilize

  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(15,20);
  display.println("TERMOPAR");
  display.setCursor(50,40);
  display.setTextSize(3);
  display.println("OK");
  display.display();
  delay(1000);
  
  
}

void loop() {

  float temp_1, temp_2, temp_3; // Suponiendo 3 termopares
  
  if(millis() - termocoupleTime >= readTime){
    temp_1 = readTemperature(1);
    temp_2 = readTemperature(2);
    temp_3 = readTemperature(3);
    showTemp1(temp_1,temp_2,temp_3);
    }
}




float readTemperature(int termopar){
  temperature = thermocouple.readCelsius();
  Serial.println("Termopar " + String(termopar) + " = " + String(temperature) + " C"); 
  termocoupleTime = millis();   
  return temperature;
}


void showTemp1(float temperature1,float temperature2,float temperature3) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.println("tp1");
  display.setCursor(0,30);
  display.println("tp2");
  display.setCursor(0,55);
  display.println("tp3");
  
  display.setTextSize(2);
  display.setCursor(25,0);
  display.println(String(temperature1) + " C");
  display.setCursor(25,25);
  display.println(String(temperature2) + " C");
  display.setCursor(25,50);
  display.println(String(temperature3) + " C");
  display.display();
  delay(1000);
}
