#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET  -1
Adafruit_SSD1306 display(OLED_RESET);

#define DHTTYPE DHT22
#define DHTPIN  D4

DHT dht(DHTPIN, DHTTYPE, 15);

void setup() {
  Serial.begin(115200);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();
  if (isnan(humid) || isnan(temp)) {
    Serial.println("Fail to read from DHT sensor!");
  }
  else {
    display.setCursor(0, 0);
    display.println("Temp : " + String(temp, 2) + " C");
    display.println("Humid : " + String(humid, 2) + " %");
    display.display();
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" , Humid: ");
    Serial.println(humid);
    delay(1000);
    display.clearDisplay();

  }
}
