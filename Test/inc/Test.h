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

using namespace Bsp;


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

#endif