#include <DHT.h>
#include <LCD_I2C.h>
#include <SoftwareSerial.h>

#define  outPin 2
#define dhtType DHT11
LCD_I2C lcd(0x27);
DHT d(outPin, dhtType);
struct CursorPosition {
  int col;
  int row;

  CursorPosition(int c, int r): col(c), row(r){}
};

SoftwareSerial bluetooth(10,11);

void setup() {
    lcd.begin();
    lcd.backlight();
    d.begin();

    // pinMode(9, OUTPUT);
    // digitalWrite(9, HIGH);

    Serial.begin(9600);
    bluetooth.begin(9600);
}

void loop() {
    float t = d.readTemperature();
    float h = d.readHumidity();

    if(!isnan(t)){
        print(CursorPosition(0,0), "Temp.: ", String(t) + (char)223 + "C");
        bluetooth.println("Temp.: "+ String(t) + (char)223 + "C");
    }

    if(!isnan(h)){
        print(CursorPosition(0,1), "Humi.: ", String(h) +"%");
        bluetooth.println("Humi.: "+ String(h) +"%");
    }

    delay(500);
}

void print(CursorPosition pos, String title, String value) {
    lcd.setCursor(pos.col, pos.row);
    lcd.print(title);
    lcd.print(value);
  }