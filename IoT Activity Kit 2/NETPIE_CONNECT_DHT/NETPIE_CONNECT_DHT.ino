#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include <ESP_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <DHT.h>

const char* ssid     = "iGenius_01";
const char* password = "123igeniusrobot321";
int colorR = 0;
int colorB = 0;
int colorG = 0;

#define APPID   "igenius"
#define KEY     "CXeYomAGbiOY6hY"
#define SECRET  "GHYL0jb73EZMEtsBLVKBZgBPO"
#define ALIAS   "esp8266"

#define NEOPIN          10
#define NUMPIXELS       2
int delayval = 500;

#define DHTTYPE DHT11
#define DHTPIN D4

#define OLED_RESET      16
#define NUMFLAKES       10
#define XPOS            0
#define YPOS            1
#define DELTAY          2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#define DHTDATATOPIC "/dht/" ALIAS
#define LED3TOPIC "/LED3/" ALIAS
#define FEEDID   "iGeniusFeed"
#define FEEDAPI  "Ei1M5PyUNJFAdHJmtgnUmWpwAUvFRdh"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
DHT dht(DHTPIN, DHTTYPE, 15);
ESP_SSD1306 display(OLED_RESET);
WiFiClient client;
MicroGear microgear(client);
int timer = 0;

long lastDHTRead = 0;
long lastDHTPublish = 0;
long lastTimeWriteFeed = 0;
float humid, temp;
String datastring2;

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
  String color;
  color.concat((char)msg[1]);
  color.concat((char)msg[2]);
  color.concat((char)msg[3]);
  color.concat((char)msg[4]);
  color.trim();
  if (msg[0] == 'R')
  {
    Serial.println("color R =" + color);
    colorR = color.toInt();
   }
  else if (msg[0] == 'G')
  {
    Serial.println("color G =" + color);
    colorG = color.toInt(); 
  }
  else if (msg[0] == 'B')
  {
    Serial.println("color B =" + color);
    colorB = color.toInt(); 
  }
  
  datastring2 = (String)colorR + "," + (String)colorG + "," + (String)colorB;
  Serial.print("Sending --> ");
  Serial.println(datastring2);
   // DHTDATATOPIC ถูก define ไว้ข้างบน
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Found new member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Lost member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("NETPIE Connected");
  display.display();
  microgear.setAlias(ALIAS);
  delay(1000);
}

void LEDShow(int red, int green, int blue) {
  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.setPixelColor(1, pixels.Color(red, green, blue));
  pixels.show();
  delay(delayval);

}

void setup() {

  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);
  pixels.begin();       //WS2812 Init
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  Serial.begin(115200);
  LEDShow(0, 0, 0);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("IoT Activity kit");
  display.println(" ");
  display.println("NETPIE");
  display.println(" ");
  display.println("Demo By Pakpoom");
  display.display();
  display.clearDisplay();
  delay(5000);

  Serial.println("Starting...");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Connecting WiFi !!!");
  display.display();

  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      display.print(".");
      display.display();
    }
  }
  display.println("");
  display.clearDisplay();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  display.println("WiFi Connected");
  display.print("IP : ");
  display.println(WiFi.localIP());
  Serial.println(WiFi.localIP());
  display.println(" ");
  display.println("Wait NETPIE Connect");
  display.display();
  display.clearDisplay();
  delay(2000);

  microgear.init(KEY, SECRET, ALIAS);
  microgear.connect(APPID);
}

void loop() {
  display.clearDisplay();
  if (microgear.connected()) {
    microgear.loop();
    LEDShow(colorG,colorR,colorB);
    // เซนเซอร์​ DHT อ่านถี่เกินไปไม่ได้ จะให้ค่า error เลยต้องเช็คเวลาครั้งสุดท้ายที่อ่านค่า
    // ว่าทิ้งช่วงนานพอหรือยัง ในที่นี้ตั้งไว้ 2 วินาที ก
    if (millis() - lastDHTRead > 2000) {
      humid = dht.readHumidity();     // อ่านค่าความชื้น
      temp  = dht.readTemperature();  // อ่านค่าอุณหภูมิ
      lastDHTRead = millis();

      Serial.print("Humid: "); Serial.print(humid); Serial.print(" %, ");
      Serial.print("Temp: "); Serial.print(temp); Serial.println(" °C ");
      // ตรวจสอบค่า humid และ temp เป็นตัวเลขหรือไม่
      if (isnan(humid) || isnan(temp)) {
        Serial.println("Failed to read from DHT sensor!");
      }
      else {
        // เตรียมสตริงในรูปแบบ "{humid},{temp}"
        String datastring = (String)humid + "," + (String)temp;
        Serial.print("Sending --> ");
        Serial.println(datastring);
        microgear.publish(DHTDATATOPIC, datastring);  // DHTDATATOPIC ถูก define ไว้ข้างบน
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("TOPIC :");
        display.println(DHTDATATOPIC);
        display.println("");
        display.print("humid : ");
        display.println(humid);
        display.print("temp : ");
        display.println(temp);
        display.println("");
        display.print("Red   : ");display.println(colorR);
        display.print("Green : ");display.println(colorG);
        display.print("Blue  : ");display.println(colorB);
        display.display();
        display.clearDisplay();
        microgear.publish(LED3TOPIC, datastring2);
      }
      if (millis() - lastTimeWriteFeed > 15000) {
        lastTimeWriteFeed = millis();
        if (humid != 0 && temp != 0) {
          String data = "{\"Humid\":";
          data += humid ;
          data += ", \"Temp\":";
          data += temp ;
          data += "}";
          Serial.print("Write Feed --> ");
          Serial.println(data);
          microgear.writeFeed(FEEDID, data);
          //microgear.writeFeed(FEEDID,data,FEEDAPI);
        }
      }
    }
  }
  else {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("NETPIE Reconnect...");
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
}
