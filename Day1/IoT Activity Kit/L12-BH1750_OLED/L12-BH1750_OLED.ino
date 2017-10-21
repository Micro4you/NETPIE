#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET  -1
BH1750 lightMeter;
Adafruit_SSD1306 display(OLED_RESET);

void setup(){
  Serial.begin(115200);
  Wire.begin(); 
  lightMeter.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  Serial.println(F("BH1750 Test"));
}

void loop() {
  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}
