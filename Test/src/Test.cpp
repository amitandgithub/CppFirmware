


#include"Test.h"

static GpioInput TestGpio_WithoutInterrupt(GPIOA,GPIO_Pin_2);
static Led Led_PC13(GPIOC,GPIO_Pin_13);
static Bsp::HwButtonIntr HwButton_A2(GPIOA, GPIO_Pin_3,Bsp::GpioInput::EXTI_Trigger_Rising, Bsp::GpioInput::EXTI_Mode_Interrupt);
static I2CDriver I2C_Obj(I2CDriver::I2C1_B6_B7, nullptr, I2CDriver::Master, I2CDriver::BaudRate_100000 ); // I2C1_B6_B7

void Init_Tests()
{
  GpioInput TestGpio(GPIOA,GPIO_Pin_1, GpioInput_ISR,Bsp::GpioInput::EXTI_Trigger_Rising);

  TestGpio.HwInit();
  TestGpio_WithoutInterrupt.HwInit();
  HwButton_A2.HwInit();
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::Click,static_cast<Bsp::HwButtonIntr::BtnHandler>(ClickEvent));
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::LongPress,static_cast<Bsp::HwButtonIntr::BtnHandler>(LongPressEvent));
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::LongLongPress,static_cast<Bsp::HwButtonIntr::BtnHandler>(LongLongPressEvent));
  I2C_Obj.HwInit();

}

void GpioInput_ISR()
{
  static int i = 0;
  i++;
}

void RunTests()
{
    ButtonTest();
    I2CDriver_Test();
}

void GpioTest()
{
    static uint32_t Input_State = 0;

    if(TestGpio_WithoutInterrupt.ReadInput() == true)
    {
        Input_State = 1;
    }
    else
    {
        Input_State = 0;
    }
    Input_State = Input_State;
}


void LEDTest()
{
    Led_PC13.On();
    SysTickTimer::DelayTicks(1000);
    Led_PC13.Off();
    SysTickTimer::DelayTicks(1000);
}

void ButtonTest()
{
    HwButton_A2.RunStateMachine();

}



void ClickEvent(void)
{
    Led_PC13.MultiBlink(1);
}
void LongPressEvent(void)
{
     Led_PC13.MultiBlink(2);
}
void LongLongPressEvent(void)
{
     Led_PC13.MultiBlink(3);
}
void I2CDriver_Test()
{
    static uint8_t I2C_Devices[10];

    I2C_Obj.ScanBus(I2C_Devices,10);
}

