#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int MIC_PIN = 34;
const int FREQ_LIMIT = 3500; 

String incomingBuffer = "";
String finalTemp = "--.-";
String finalTDS = "---";

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ready-Wait Mode");
}

float getFreq() {
  unsigned long start = micros();
  long cycles = 0;
  int lastState = 0;
  while (micros() - start < 100000) { // 100ms sample
    int v = analogRead(MIC_PIN);
    int state = (v > 2048) ? 1 : 0; 
    if (state != lastState) {
      cycles++;
      lastState = state;
    }
  }
  return (cycles / 2.0) / 0.1;
}

void loop() {
  float f = getFreq();

  if (f > FREQ_LIMIT) {
    Serial.println("Sound Detected! Waiting 2s for Ready Tone...");
    
    // SYNC: 2s (Ready Tone) + 0.5s (Half of Bit 7) = 2500ms
    delay(1900); 

    byte resultByte = 0;
    for (int i = 7; i >= 0; i--) {
      float bitF = getFreq();
      bool bit = (bitF > FREQ_LIMIT);
      if (bit) resultByte |= (1 << i);
      
      Serial.print("Bit "); Serial.print(i); Serial.println(bit ? ": 1" : ": 0");
      
      // Wait for next bit center (1000ms - 100ms sample)
      delay(900); 
    }

    char c = (char)resultByte;
    Serial.println("Decoded: " + String(c));

    if (isDigit(c) || c == '.') {
      incomingBuffer += c;
    } 
    else if (c == '@') {
      finalTemp = incomingBuffer;
      incomingBuffer = "";
    }
    else if (c == '\n' || resultByte == 0x0A) {
      finalTDS = incomingBuffer;
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp : "); lcd.print(finalTemp); lcd.print(" C");
      lcd.setCursor(0, 1);
      lcd.print("TDS  : "); lcd.print(finalTDS); lcd.print(" ppm");

      incomingBuffer = ""; 
    }
    
    delay(600); // Reset for next character
  }
}