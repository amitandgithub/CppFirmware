//******************
// CLASS: GpioInputTest
//
// DESCRIPTION:
//  This class is to test the GPIO Input Functionality
//
// CREATED: 13-01-2018, by Amit Chaudhary
//
// FILE: $FILE_FNAME$
//

#ifndef APP_INC_TEST_HPP_
#define APP_INC_TEST_HPP_


#include "GpioInput.hpp"
#include "Led.hpp"
#include "SysTickTimer.hpp"
#include "HwButton.hpp"
#include "HwButtonIntr.hpp"
#include <I2CDriver.hpp>
#include "INA219.hpp"
#include "SpiDriver.hpp"
#include "Nokia5110LCD.hpp"

using namespace Bsp;
using namespace App;

void Init_Tests();
void RunTests();
void GpioInput_ISR();
void LEDTest();
void GpioTest();
void ButtonTest();
void ClickEvent(void);
void LongPressEvent(void);
void LongLongPressEvent(void);
void I2CDriver_Test();
void Nokia_Display_Test();

#endif