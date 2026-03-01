#include <Wire.h>

#define MT6701_ADDR 0x06   // Default I2C address

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(MT6701_ADDR);
  Wire.write(0x03);  // Angle register (high byte)
  Wire.endTransmission(false);
  Wire.requestFrom(MT6701_ADDR, 2);

  if (Wire.available() == 2) {
    uint16_t angle = Wire.read() << 8;
    angle |= Wire.read();

    angle = angle & 0x3FFF;   // 14-bit angle value (0–16383)

    float degrees = angle * 360.0 / 16384.0;
    
    Serial.println(degrees);
  }

  delay(100);
}