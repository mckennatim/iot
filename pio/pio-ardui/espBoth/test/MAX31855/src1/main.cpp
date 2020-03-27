#include <Arduino.h>
  

#include <MAX31855.h> // Include MAX31855 Sensor library
/*******************************************************************************************************************
** Declare all program constants                                                                                  **
*******************************************************************************************************************/
const uint32_t SERIAL_SPEED     = 115200; ///< Set the baud rate for Serial I/O
const uint8_t  SPI_CHIP_SELECT  =      2; ///< Chip-Select PIN for SPI
const uint8_t  SPI_MISO         =   12; ///< Master-In, Slave-Out PIN for SPI
const uint8_t  SPI_SYSTEM_CLOCK =    14; ///< System Clock PIN for SPI

/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
MAX31855_Class MAX31855; ///< Create an instance of MAX31855


void setup()
{
  Serial.begin(SERIAL_SPEED);
  Serial.println(F("Starting software SPI demo program for MAX31855"));
  Serial.print(F("Initializing MAX31855 sensor\n"));
  /********************************************************************************************
  ** Uncomment out either the hardware or software SPI call, depending upon which is in use  **
  ********************************************************************************************/
  // while (!MAX31855.begin(SPI_CHIP_SELECT))                            // Hardware SPI for MAX31855
while (!MAX31855.begin(SPI_CHIP_SELECT,SPI_MISO,SPI_SYSTEM_CLOCK)) // Software SPI for MAX31855
  {
    
    Serial.println(F("Unable to start MAX31855. Waiting 3 seconds."));
    delay(3000);
  } // of loop until device is located
 Serial.println();
} // of method setup()

void loop()
{
  int32_t ambientTemperature = MAX31855.readAmbient(); // retrieve MAX31855 die ambient temperature
  int32_t probeTemperature   = MAX31855.readProbe();   // retrieve thermocouple probe temp
  uint8_t faultCode          = MAX31855.fault();       // retrieve any error codes
  if ( faultCode )                                     // Display error code if present
  {
    Serial.print("Fault code ");
    Serial.print(faultCode);
    Serial.println(" returned.");
  }
  else
  {
    Serial.print("Ambient Temperature is ");
    Serial.print((float)ambientTemperature/1000,3);
    Serial.println("\xC2\xB0""C");
    Serial.print("Probe Temperature is   ");
    Serial.print((float)probeTemperature/1000,3);
    Serial.println("\xC2\xB0""C\n");
  } // of if-then-else an error occurred
  delay(5000);
} // of method loop()

