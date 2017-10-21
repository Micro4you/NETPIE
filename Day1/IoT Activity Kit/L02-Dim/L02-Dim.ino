int brightness = 0;
int fadeAmount = 10;

void setup() {
  pinMode(D7, OUTPUT);
}

void loop() {
  analogWrite(D7, brightness);
  brightness = brightness + fadeAmount;
  
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  
  delay(100);
}
