


#include"Test.h"

GpioInput TestGpio_WithoutInterrupt(GPIOA,GPIO_Pin_2);

void Init_Tests()
{
  GpioInput TestGpio(GPIOA,GPIO_Pin_1, GpioInput_ISR,Bsp::GpioInput::EXTI_Trigger_Rising);

  TestGpio.HwInit();
  TestGpio_WithoutInterrupt.HwInit();
  
}

void GpioInput_ISR()
{
  static int i = 0;
  i++;
}

void RunTests()
{
  static uint32_t Input_Count = 0;
  
  if(TestGpio_WithoutInterrupt.ReadInput() == true)
  {
    Input_Count = 1;
  }
  else
  {
    Input_Count = 0;
  }
}