#include <OneWire.h>
#include <DallasTemperature.h>

const int BUZZ_PIN = 18;
const int TDS_PIN = 32;
const int ONE_WIRE_BUS = 4; 

const int FREQ_HIGH = 4000; 
const int FREQ_LOW = 3000;  
const int BIT_TIME = 1000;  // 1 bit per second

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();
  pinMode(BUZZ_PIN, OUTPUT);
}

void transmitFSK(char c) {
  Serial.print("Next Char: "); Serial.println(c);

  // 1. READY WAIT: 2 Seconds of High Tone
  tone(BUZZ_PIN, FREQ_HIGH);
  delay(2000); 

  // 2. DATA BITS: 8 bits @ 1 second each
  for (int i = 7; i >= 0; i--) {
    bool bit = (c >> i) & 0x01;
    tone(BUZZ_PIN, bit ? FREQ_HIGH : FREQ_LOW);
    delay(BIT_TIME);
  }

  noTone(BUZZ_PIN);
  delay(500); // Short silence between characters
}

void loop() {
  sensors.requestTemperatures(); 
  float temp = sensors.getTempCByIndex(0);
  float tds = analogRead(TDS_PIN) * 0.5; 

  String payload = String(temp, 1) + "@" + String(tds, 0) + "\n";
  
  for (int i = 0; i < payload.length(); i++) {
    transmitFSK(payload[i]);
  }
  delay(10000); 
}