#include "EEPROMUtils.h"

void EEPROMUtils::init() {
   EEPROM.begin(EEPROM_SIZE);
}

void EEPROMUtils::readString(uint8_t addr, char* dest) {
  for (uint8_t i = 0; i < 64; i++) {
    uint8_t readValue = EEPROM.read(addr + i);
    if (readValue == 0 || char(readValue) == '\0') {
      dest[i] = '\0';
      break;
    }
    dest[i] = char(readValue);
  }
}

void EEPROMUtils::writeString(uint8_t addr, const char* src) {
  for (uint8_t i = 0; i < strlen(src); i++) {
      EEPROM.write(addr + i, src[i]);
  }
  EEPROM.write(addr + strlen(src), '\0');
}

void EEPROMUtils::readInt(uint8_t addr, uint8_t* dest) {
  *dest = EEPROM.read(addr);
}

void EEPROMUtils::writeInt(uint8_t addr, uint8_t value) {
  EEPROM.write(addr, value);
}

void EEPROMUtils::readIP(uint8_t addr, uint8_t dest[4]) {
  for (uint8_t i = 0; i < 4; i++)
    dest[i] = EEPROM.read(addr + i);
}

void EEPROMUtils::commit() {
  EEPROM.commit();
}
