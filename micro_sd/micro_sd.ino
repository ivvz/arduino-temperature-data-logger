#include <SD.h>
#include "max6675.h"

const int chipSelect = 4;

void setup() {

  // Open serial communications and wait for port to open:

  Serial.begin(9600);

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

void loop() {

  // make a string for assembling the data to log:

  String dataString = "";

  // read three sensors and append to the string:

  for (int analogPin = 0; analogPin < 3; analogPin++) {

    int sensor = analogRead(analogPin);

    dataString += String(sensor);

    if (analogPin < 2) {

      dataString += ",";

    }

  }

  // open the file. note that only one file can be open at a time,

  // so you have to close this one before opening another.

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:

  if (dataFile) {

    dataFile.println(dataString);

    dataFile.close();

    // print to the serial port too:

    Serial.println(dataString);

  }

  // if the file isn't open, pop up an error:

  else {

    Serial.println("error opening datalog.txt");

  }
}
