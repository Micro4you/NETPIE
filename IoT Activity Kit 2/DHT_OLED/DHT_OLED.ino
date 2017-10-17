
#include <ESP_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN D4
DHT dht(DHTPIN, DHTTYPE, 15);

#define OLED_RESET  16
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16 
ESP_SSD1306 display(OLED_RESET);

void setup() {
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  Serial.begin(115200);
}

void loop() {
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Temp  : ");
  display.println(temp);
  display.print("Hunid : ");
  display.println(humid);
  display.display();
  display.clearDisplay();
  
  
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" , Humid: ");
  Serial.println(humid);
  delay(1000); 
}
