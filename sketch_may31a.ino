#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
const int dhtIndoorPin = 8;
const int dhtOutdoorPin = 9;
const int buttonPin = 10;
int buttonState = 0;
boolean isButtonPressed = false;
int row_excel = 0;
LiquidCrystal_I2C lcd( 0x27 , 16 , 2 );
DHT dhtIn (dhtIndoorPin, DHT22);
DHT dhtOut (dhtOutdoorPin, DHT22);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  //  Serial.begin(9600);
  //  Serial.println("CLEARDATA"); // очистка листа excel
  //  Serial.println("LABEL,Time,Out Temp, Out Hum, Num Rows"); // заголовки столбцов
  dhtIn.begin();
  dhtOut.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  // устанавливаем курсор в позицию (0,0):
  //lcd.setCursor(0, 0);
  // выводим цифры от 0 до 9:
  //for (int thisChar = 0; thisChar < 10; thisChar++) {
  //    lcd.print("hello");
  //    delay(500);
  //}
  buttonState = digitalRead(buttonPin);
  if (buttonState == false) {
    isButtonPressed = !isButtonPressed;
    delay(200);
  }
  //lcd.print(isButtonPressed);
  //if (buttonState = false) {
  //  lcd.clear();
  //
  //  }
  if (isButtonPressed) {
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("(IN) Temp: ");
    lcd.print(dhtIn.readTemperature());
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(dhtIn.readHumidity());
    delay(50);
  } else {
    //  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("(OUT)Temp: ");
    lcd.print(dhtOut.readTemperature());
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(dhtOut.readHumidity());
    delay(50);
  }

  //  row_excel++; // номер строки + 1
  //  Serial.print("DATA,TIME,"); // запись в excel текущей даты и времени
  //  Serial.print(dhtOut.readTemperature());
  //  Serial.print(",");
  //  Serial.print(dhtOut.readHumidity());
  //  Serial.print(",");
  //  Serial.println(row_excel);
  //  delay(600000);




  //delay(500);
  //;


  // устанавливаем курсор в (16,1):
  //lcd.setCursor(16, 1);
  // включаем автоматическую прокрутку
  //lcd.autoscroll();
  // печатаем от 0 до 9:
  //for (int thisChar = 0; thisChar < 10; thisChar++) {
  //    lcd.print(thisChar);
  //    delay(500);
  //}
  // выключаем автоматическую прокрутку
  //lcd.noAutoscroll();

  // очищаем экран для следующей итерации
  //lcd.clear();
}
