#include <OPL3Duo.h>

#define BAUD 1000000

OPL3Duo opl3Duo;

void setup() {
  Serial.begin(BAUD);
  opl3Duo.begin();
}

void loop() {
  if(Serial.available()) {
    uint8_t c = Serial.read();
    if(c & 0x80) {
      opl3Duo.reset();
      return;
    }
    uint8_t synthUnit = (c & 0x40) >> 6;

    uint8_t theRest[2];
    if(Serial.readBytes(theRest, 2) != 2) {
      return;
    }
    short reg = ((c & 1) << 8) | theRest[0];
    uint8_t value = theRest[1];
    opl3Duo.setChipRegister(synthUnit, reg, value);
  }
}
