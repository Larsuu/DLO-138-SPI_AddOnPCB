#include <EEPROM.h>

#include <Adafruit_GFX_AS.h> 
// needs to be Adafruit GFX Library v1.1.4, check/change your installed version
// otherwise you will get a black screen or compiler errors

#include <Adafruit_ILI9341_STM.h>
#include "global.h"
#include "variables.h"

#include <STM32ADC.h>

STM32ADC myADC1(ADC1), myADC2(ADC2); 


#define FIRMWARE_VERSION	"1.11"

// ------------------------
void setup()	{
// ------------------------
	
 	afio_cfg_debug_ports(AFIO_DEBUG_NONE); //added to disable the debug port. My stock DSO-138 won't allow the screen to work without this
	// see http://www.stm32duino.com/viewtopic.php?t=1130#p13919 for more info
	
	
	DBG_INIT(SERIAL_BAUD_RATE);

	// set digital and analog stuff
	initIO();
	
	// load scope config or factory reset to defaults
	loadConfig(digitalRead(BTN4) == LOW);
	
	// init the IL9341 display
	initDisplay();
  for (int i = 0; i < 20; ++i) {
    if (Serial) break;
    delay(100);
  }
  DBG_PRINT("Dual channel O Scope with two logic channels, ver: ");
  DBG_PRINTLN(FIRMWARE_VERSION);
  myADC1.attachAnalogWatchdogInterrupt(triggerISR);
//  myADC2.attachAnalogWatchdogInterrupt(triggerISR2);
}



// ------------------------
void loop()	{
// ------------------------
	controlLoop();
}
