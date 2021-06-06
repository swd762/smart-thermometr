#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define T_PERIOD 90000 // transmition period in ms

// timers vars
uint32_t myTimer;
boolean firstStart = true;
// temp and hum sensors
const int dhtIndoorPin = 8;
const int dhtOutdoorPin = 9;
// button
const int buttonPin = 10;
boolean buttonState = 0;
boolean isButtonPressed = false;
// excel vars
//int row_excel = 0;
// objects declaration
LiquidCrystal_I2C lcd( 0x27 , 16 , 2 );
DHT dhtIn (dhtIndoorPin, DHT22);
DHT dhtOut (dhtOutdoorPin, DHT22);


void setup() {


  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  //  Serial.println("CLEARDATA"); // clear excel sheet
  Serial.println("LABEL,Time,Date,t Out,t In,H Out,H in"); // print headers
  dhtIn.begin();
  dhtOut.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  // all about button
  buttonState = digitalRead(buttonPin);
  if (buttonState == false) {
    isButtonPressed = !isButtonPressed;
    delay(200);
  }

  if (isButtonPressed) {
    lcd.setCursor(0, 0);
    lcd.print("(IN) Temp: ");
    lcd.print(dhtIn.readTemperature());
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(dhtIn.readHumidity());
    delay(50);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("(OUT)Temp: ");
    lcd.print(dhtOut.readTemperature());
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(dhtOut.readHumidity());
    delay(50);
  }

  // delay to send data
  if (millis() - myTimer >= T_PERIOD) {
    myTimer += T_PERIOD;
    sendData();

  }
  // send data, when arduino starts
  if (firstStart) {
    sendData();
    firstStart = false;
  }
}


// send data method
void sendData() {
//  row_excel++; // increment row
  Serial.print("DATA"); //send DATA to start logging to excel
  Serial.print(",");
  Serial.print("TIME"); // TIME
  Serial.print(","); //
  Serial.print("DATE"); // DATE
  Serial.print(","); // 
  Serial.print(dhtOut.readTemperature()); // outdoor temp
  Serial.print(",");
  Serial.print(dhtIn.readTemperature()); // indoor temp
  Serial.print(",");
  Serial.print(dhtOut.readHumidity()); // outdoor humidity
  Serial.print(",");
  Serial.print(dhtIn.readHumidity()); // indoor humidity
  Serial.print(",");
//  Serial.println(row_excel); // number of excel row
}
