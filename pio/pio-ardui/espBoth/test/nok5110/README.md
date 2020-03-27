it works

https://github.com/mcauser/WeMos-D1-mini-Nokia-5110-PCD8544

had to edit library touchscreen.h adding defined(ESP8266) to get rid of error about RwReg

#if defined(NRF52_SERIES) || defined(ESP32) || defined(ESP8266) || defined(ARDUINO_ARCH_STM32)
typedef volatile uint32_t RwReg;
#endif
