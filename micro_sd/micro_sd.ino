#include <SD.h>
#include "max6675.h"

const int chipSelect = 4;
int boton_crear_archivo = 2;
int boton_cerrar_archivo = 3;
int numero_de_archivo = 4;

int thermoDO = 7;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {

  // Open serial communications and wait for port to open:

  Serial.begin(9600);
  pinMode(boton_crear_archivo, INPUT_PULLUP);
  pinMode(boton_cerrar_archivo, INPUT_PULLUP);

  // wait for Serial Monitor to connect. Needed for native USB port boards only:

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


 // String dataString = "";
  //String file_name = "file" + String(numero_de_archivo) + ".csv";

 void loop() {

  // make a string for assembling the data to log:

  String dataString = "";
  
  dataString += thermocouple.readCelsius();


  // open the file. note that only one file can be open at a time,

  // so you have to close this one before opening another.

  File dataFile = SD.open("hornoxx.csv", FILE_WRITE);

  // if the file is available, write to it:

  if (dataFile) {

    dataFile.println(dataString);

    dataFile.close();

    // print to the serial port too:

    Serial.println(dataString);
    delay(1000);

  }

  // if the file isn't open, pop up an error:

  else {

    Serial.println("error opening datalog.txt");

  }
}
File crearArchivo(String nombre){
  File dataFile = SD.open(nombre, FILE_WRITE);
  }

//File cerrarArchivo(String nombre){
 // File nombre.close();
//}
