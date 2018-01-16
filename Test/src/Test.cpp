


#include"Test.h"

static GpioInput TestGpio_WithoutInterrupt(GPIOA,GPIO_Pin_2);
static Led Led_PC13(GPIOC,GPIO_Pin_13);
static Bsp::HwButtonIntr HwButton_A2(GPIOA, GPIO_Pin_3,Bsp::GpioInput::EXTI_Trigger_Rising, Bsp::GpioInput::EXTI_Mode_Interrupt);
static I2CDriver INA219_I2C(I2CDriver::I2C1_B6_B7, nullptr, I2CDriver::Master, I2CDriver::BaudRate_100000 ); // I2C1_B6_B7
static INA219 INA219_Obj(&INA219_I2C,0x80);
static INA219::Power_t Power;

static SpiDriver SpiDriverLCD(SpiDriver::SPI_1_A7_A6_A5_A4);
static GpioOutput DataCommandSelectGpio(GPIOB,GPIO_Pin_1);
static GpioOutput ResetPinGpio(GPIOB,GPIO_Pin_0);
static GpioOutput BackLightGpio(GPIOB,GPIO_Pin_10);
Nokia5110LCD NokiaLCD( &SpiDriverLCD, &ResetPinGpio, &DataCommandSelectGpio, &BackLightGpio );

UI MyUI(&NokiaLCD);
Screen::Event_t gEvent = Screen::MaxEvents;
static ControlScreen MenuScreen;
static ControlScreen myControlScreen;
static Screen PowerMonitorScreen;
static Screen Aarav;
static Screen Tanya;
static UI::ScreenHandle_t MenuScreenHandle;
static UI::ScreenHandle_t myControlScreenHandle;
static UI::ScreenHandle_t AaravScreenHandle;
static UI::ScreenHandle_t TanyaScreenHandle;

uint8_t aCurrent[9];
uint8_t aVoltage[9];

void Init_Tests()
{
  GpioInput TestGpio(GPIOA,GPIO_Pin_1, GpioInput_ISR,Bsp::GpioInput::EXTI_Trigger_Rising);

  TestGpio.HwInit();
  TestGpio_WithoutInterrupt.HwInit();
  HwButton_A2.HwInit();
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::Click,static_cast<Bsp::HwButtonIntr::BtnHandler>(ClickEvent));
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::LongPress,static_cast<Bsp::HwButtonIntr::BtnHandler>(LongPressEvent));
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::LongLongPress,static_cast<Bsp::HwButtonIntr::BtnHandler>(LongLongPressEvent));
  INA219_I2C.HwInit();
  INA219_Obj.SetCalibration_32V_2A();
  MyUI.Init();
  CreateUI();

}

void GpioInput_ISR()
{
  static int i = 0;
  i++;
}

void RunTests()
{
   // ButtonTest();
   // I2CDriver_Test();
   // INA219_Obj.Run(&Power);
   // Nokia_Display_Test();
    HwButton_A2.RunStateMachine();
    MyUI.EventHamdler(gEvent);
    MyUI.Run();
    INA219_Obj.Run(&Power);

    ftoa(Power.Voltage, (char*)aVoltage, 6);
    ftoa(Power.Current, (char*)aCurrent, 6);

    PowerMonitorScreen.SetText(1, 0, "V = ", 4);
    PowerMonitorScreen.SetText(1, 4,  (char*)aVoltage, 7);

    PowerMonitorScreen.SetText(2, 0, "I = ", 4);
    PowerMonitorScreen.SetText(2, 4,  (char*)aCurrent,7);

    ftoa(Power.Power, (char*)aCurrent, 6);
    PowerMonitorScreen.SetText(3, 0, "P = ", 4);
    PowerMonitorScreen.SetText(3, 4,  (char*)aCurrent, 7);
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



void ClickEvent1(void)
{
    Led_PC13.MultiBlink(1);
    NokiaLCD.DrawLine(1, 0, "Click");
}
void LongPressEvent1(void)
{
    Led_PC13.MultiBlink(2);
    NokiaLCD.DrawLine(1, 0, "Long Press");
}
void LongLongPressEvent1(void)
{
    Led_PC13.MultiBlink(3);
    NokiaLCD.DrawLine(1, 0, "Long Long Pres");
}
void I2CDriver_Test()
{
    static uint8_t I2C_Devices[10];

    INA219_I2C.ScanBus(I2C_Devices,10);
}

void Nokia_Display_Test()
{
    static const char Array[] = {'-','\\','|','/','-','\\','|','/'};
    static char index;
    HwButton_A2.RunStateMachine();
    NokiaLCD.DrawChar(0, 0, Array[index % sizeof(Array)]);
    NokiaLCD.DrawChar(0, 2, Array[index % sizeof(Array)]);
    NokiaLCD.DrawChar(0, 4, Array[index % sizeof(Array)]);
    NokiaLCD.DrawChar(0, 6, Array[index % sizeof(Array)]);
    NokiaLCD.DrawChar(0, 8, Array[index % sizeof(Array)]);
    NokiaLCD.DrawChar(0, 10,Array[index % sizeof(Array)]);
    NokiaLCD.DrawChar(0, 12,Array[index++ % sizeof(Array)]);
    SysTickTimer::DelayTicks(150);
}
void CreateUI()
{
    Aarav.AddText( (char *)
                       "Aarav         "
                       "Aarav         "
                       "Aarav         "
                       "Aarav         "
                       "Aarav         "
                       "Aarav         "
                       );

    MenuScreen.AddText( (char *)
                       ">Menu1        "
                       " Menu2        "
                       " Menu3        "
                       " Menu4        "
                       " Menu5        "
                       " Next Menu    "
                       );

    Tanya.AddText( (char *)
                       "Tanya         "
                       "Tanya         "
                       "Tanya         "
                       "Tanya         "
                       "Tanya         "
                       "Tanya         "
                       );

    PowerMonitorScreen.AddText( (char *)
                       "< Live Power >"
                       "              "
                       "              "
                       "              "
                       "              "
                       "              "
                       );

    myControlScreen.AddText( (char *)
                       ">Live Power   "
                       " Aarav,Avni   "
                       " Tanya,Dog    "
                       " Rudransh,    "
                       " Amit,sumit   "
                       " Next Menu    "
                       );
   myControlScreen.AddHandler(0,Line0Menu0LongTouchHandler,Line0Menu0LongLongTouchHandler);
   myControlScreen.AddHandler(1,Line1AaravLongTouchHandler,Line0Menu0LongLongTouchHandler);
   myControlScreen.AddHandler(2,Line2TanyaLongTouchHandler,Line0Menu0LongLongTouchHandler);
   myControlScreen.AddHandler(5,Line5Menu0LongTouchHandler,nullptr);
   MenuScreen.AddHandler(5,Line5MenuScreenLongTouchHandler,nullptr);

   MyUI.AddScreen(&PowerMonitorScreen);
   AaravScreenHandle = MyUI.AddScreen(&Aarav);
   TanyaScreenHandle = MyUI.AddScreen(&Tanya);
   myControlScreenHandle = MyUI.AddScreen(&myControlScreen);
   MenuScreenHandle = MyUI.AddScreen(&MenuScreen);
}

void ClickEvent(void)
{
	gEvent = Screen::Touch;
}
void LongPressEvent(void)
{
	gEvent = Screen::LongTouch;
}
void LongLongPressEvent(void)
{
	gEvent = Screen::LongLongTouch;
}

void Line0Menu0LongTouchHandler()
{
  UI::SetActiveScreen(0);
}

void Line1AaravLongTouchHandler()
{
  UI::SetActiveScreen(AaravScreenHandle);
}
void Line2TanyaLongTouchHandler()
{
  UI::SetActiveScreen(TanyaScreenHandle);
}
void Line5Menu0LongTouchHandler()
{
  UI::SetActiveScreen(MenuScreenHandle);
}
void Line5MenuScreenLongTouchHandler()
{
  UI::SetActiveScreen(myControlScreenHandle);
}
void Line0Menu0LongLongTouchHandler()
{
	Led_PC13.Toggle();
	SysTickTimer::DelayTicks(200);
	Led_PC13.Toggle();
}



// reverses a string 'str' of length 'len'

void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}
// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10.0, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}