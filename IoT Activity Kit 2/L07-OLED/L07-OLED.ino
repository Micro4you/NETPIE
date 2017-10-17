#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define OLED_RESET  -1

Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawPixel(127, 63, WHITE);
  display.drawLine(0, 63, 127, 21, WHITE);
  display.drawCircle(110, 50, 12, WHITE);
  display.fillCircle(45, 50, 8, WHITE);
  display.drawRect(115,3,10,10,WHITE);
  display.fillRect(115,13,10,10,WHITE);
  display.drawTriangle(70, 60, 90, 60, 80, 46, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Welcome All to");
  display.setTextSize(2);
  display.println("iGenius");
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(1);
  display.println("IGENIUS ROBOT");
  display.setTextColor(WHITE, BLACK);
  display.display();
  
}

void loop() {


}
