#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include <ESP_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <DHT.h>

const char* ssid     = "iGenius_01";
const char* password = "123igeniusrobot321";

#define APPID   "igenius"
#define KEY     "CXeYomAGbiOY6hY"
#define SECRET  "GHYL0jb73EZMEtsBLVKBZgBPO"
#define ALIAS   "esp8266"

#define DHTTYPE DHT11
#define DHTPIN D4

#define OLED_RESET  16
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16 

DHT dht(DHTPIN, DHTTYPE, 15);
ESP_SSD1306 display(OLED_RESET);
WiFiClient client;
MicroGear microgear(client);
int timer = 0;

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("NETPIE Connected");
    display.display();
    microgear.setAlias(ALIAS);
    delay(1000);
}

void setup() {
  microgear.on(MESSAGE,onMsghandler);
  microgear.on(CONNECTED,onConnected);
  
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  Serial.begin(115200);
  
  Serial.println("Starting...");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Connecting WiFi !!!");
  display.display();
  display.clearDisplay();
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  display.println("WiFi Connected");
  display.print("IP : ");
  display.println(WiFi.localIP());
  Serial.println(WiFi.localIP());
  display.display("");
  display.println("Wait for NETPIE Connect");
  display.display();
  display.clearDisplay();
  
  microgear.init(KEY,SECRET,ALIAS);
  microgear.connect(APPID);
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
