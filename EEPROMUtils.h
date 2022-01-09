#include "EEPROM.h"

class EEPROMUtils {
  private:
    static const int EEPROM_SIZE = 256;
    
  public:
    static void init();
    static void readString(uint8_t addr, char* dest);
    static void writeString(uint8_t addr, const char* src);
    static void readInt(uint8_t addr, uint8_t* dest);
    static void writeInt(uint8_t addr, uint8_t value);
    static void readIP(uint8_t addr, uint8_t dest[4]);
    static void commit();
};
