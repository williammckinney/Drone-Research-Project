#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

float windspeed = 0.00;

unsigned long x = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

}

void loop() {

int pushed = digitalRead(2);

  if(pushed == LOW){

    x = x + 1;

  for (int i = 0; i < 10; i++){
    // make a string for assembling the data to log:
  String dataString = "";

  // read wind sensor and append to the string:
    windspeed = (analogRead(A0) * 32.6 / 1023.0);
    dataString += String(windspeed);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

  String fileName = "windlog" + String(x) + ".txt";
  
  File dataFile = SD.open(fileName, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);

    if (i==9){
      Serial.println("Measurement " + String(x) + " is done");
    }

    delay(1000);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening windlog.txt");
  }
 
 }
    
  }else{

  }
  
}
