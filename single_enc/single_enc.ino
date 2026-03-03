#include <Wire.h>

#define MT6701_ADDR 0x06   // Default I2C address

float initial_degrees = -1.0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(MT6701_ADDR);
  // Wire.write(0x03);  // Angle register (high byte)
  Wire.write(0x03);  // Angle register (high byte)
  Wire.endTransmission(false);
  Wire.requestFrom(MT6701_ADDR, 2);

  
  if (Wire.available() == 2) {
    uint16_t read_angle = Wire.read() << 8;
    read_angle |= Wire.read();

    read_angle = read_angle & 0x3FFF;   // 14-bit angle value (0–16383)

    float read_degrees = read_angle * (360.0 / 16384.0);
    // read_degrees = read_degrees / 4; // idk why
    if (initial_degrees == -1.0) {
      initial_degrees = read_degrees;  
    }

    float output_degrees = 0.0;
    if (read_degrees >= initial_degrees) {
      output_degrees = read_degrees - initial_degrees;
    } else {
      output_degrees = 360 - initial_degrees + read_degrees;
    }

    Serial.print(initial_degrees);
    Serial.print(", ");
    Serial.print(read_degrees);
    Serial.print(", ");
    Serial.println(output_degrees);
  }

  delay(16);
}