#include <SD.h>
#include "max6675.h"


int boton_inicio = 2;
int boton_cierre = 3;

const int chipSelect = 10;

int thermoDO = 7;
int thermoCS = 6;
int thermoCLK = 5;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {

  Serial.begin(9600);
  delay(500);

  pinMode(boton_inicio, INPUT_PULLUP);
  pinMode(boton_cierre, INPUT_PULLUP);

  digitalWrite(boton_inicio, HIGH);
  digitalWrite(boton_inicio, HIGH);

  
  
  checkSD();
}  

void loop() {
  String dataString;
  String nombre = "hornos5"; 

  File archivo = createFile(nombre);
  
  dataString = createString();
  writeData(nombre,dataString);

  //archivo.println(dataString);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
//  File dataFile = SD.open("hornos3.csv", FILE_WRITE);
//  if (dataFile) {
//    dataFile.println(dataString);
//    dataFile.close();
//    // print to the serial port too:
//    Serial.println(dataString);
//    delay(5000);
//  }
//  // if the file isn't open, pop up an error:
//  else {
//    Serial.println("error opening datalog.txt");
//  }
//}
}
String createString(){
  // make a string for assembling the data to log:
  String dataString = "";
  // read three sensors and append to the string:
  for (int termopar = 0; termopar < 3; termopar++) {
    float lectura = thermocouple.readCelsius();
    dataString += String(lectura);
    if (termopar < 2) {
      dataString += ",";
    }
  }
  return dataString;
}

File createFile(String nombre){
  File dataFile = SD.open(nombre + ".csv", FILE_WRITE);
  String header = ("termopar 1,termopar 2,termopar 3");
  if (dataFile) {
    dataFile.println(header);
    dataFile.close();
    // print to the serial port too:
    Serial.println(header);
    delay(5000);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error creating datafile");
  }
  return dataFile;
}
  


File writeData(String nombre, String data){
  File dataFile = SD.open(nombre + ".csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    // print to the serial port too:
    Serial.println(data);
    delay(5000);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error creating datafile");
  }
}
  




void checkSD(){
  while (!Serial);
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
    while (true);
  }
  Serial.println("initialization done.");
}
