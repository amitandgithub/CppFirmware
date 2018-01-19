


#include "Time.hpp"
#include "Test.h"

namespace Utility
{


void Time::Set(unsigned char hrs, unsigned char min, unsigned char sec)
{
    if(sec > 59)
    {
        sec = sec - 59;
        min++;
    }

    if(min > 59)
    {
        min = min - 59;
        hrs++;
    }

    Sec = sec;
    Min = min;
    Hrs = hrs;
}

Time::Time(unsigned char hrs, unsigned char min, unsigned char sec, unsigned int update_frequency)
{
    if(sec > 59)
    {
        sec = sec - 59;
        min++;
    }

    if(min > 59)
    {
        min = min - 59;
        hrs++;
    }

    Sec = sec;
    Min = min;
    Hrs = hrs;
    m_UpdateFrequencyInMillis = update_frequency;
}

// Overload + for Time.
Time Time::operator+(Time t)
{
    Time temp;
    temp.Sec = t.Sec + Sec;
    temp.Min = t.Min + Min;
    temp.Hrs = t.Hrs + Hrs;

    if(temp.Sec > 59)
    {
        temp.Sec = temp.Sec - 59;
        temp.Min++;
    }

    if(temp.Min > 59)
    {
        temp.Min = temp.Min - 59;
        Hrs++;
    }
    return temp;
}

        // Overload - for Time.
Time Time::operator-(Time t)
{
    Time temp;

    if( (t.Sec - Sec) >= 0 )
    {
        temp.Sec = t.Sec - Sec;
    }
    else
    {
        temp.Sec = Sec - t.Sec;
        Min = Min -1;
    }

    if( (t.Min - Min) >= 0 )
    {
        temp.Min = t.Min - Min;
    }
    else
    {
        temp.Min = Min - t.Min;
        Hrs = Hrs -1;
    }

    temp.Hrs = (t.Hrs - Hrs) >= 0 ? (t.Hrs - Hrs):( Hrs - t.Hrs);

    return temp;
}

Time Time::operator++()
{
    Sec++;

    if(Sec > 59)
    {
        Sec = Sec - 59;
        Min++;
    }

    if(Min > 59)
    {
        Min = Min - 59;
        Hrs++;
    }
    return *this;
}

Time Time::operator++(int x)
{
    Sec++;

    if(Sec > 59)
    {
        Sec = Sec - 59;
        Min++;
    }

    if(Min > 59)
    {
        Min = Min - 59;
        Hrs++;
    }
    return *this;
}

Time Time::operator--()
{
   unsigned char SecCarry = 0;
   unsigned char MinCarry = 0;

    if( Sec == 0 )
    {
       Sec = 59;
       SecCarry = 1;
    }
    else
    {
        Sec--;
    }

    if( Min == 0 )
    {
       Min = 59;
       MinCarry = 1;
    }
    else
    {
        Min = -1 - SecCarry ;
    }

    Hrs = -1 - MinCarry ;

    return *this;
}

void Time::Get(unsigned char* hrs, unsigned char* min, unsigned char* sec)
{
    *sec = Sec;
    *min = Min;
    *hrs = Hrs;
}

char* Time::Get(char* pBuffer)
{
    intToStr(Hrs, &pBuffer[0], 2);
    pBuffer[2] = ':';
    intToStr(Min, &pBuffer[3], 2);
    pBuffer[5] = ':';
    intToStr(Sec, &pBuffer[6], 2);
    return pBuffer;
}

void Time::IncrementTime()
{
    (*this)++;
}
bool Time::Update()
{
    static unsigned int TickDifference = 0;
    unsigned int elapsed_ticks;

    TickDifference = TickDifference; // To avoid compiler warning

    elapsed_ticks = GetRawMiliSecTicksSince(m_Previous_Millis);

    if( elapsed_ticks >= m_UpdateFrequencyInMillis -1UL )
    {
        m_Previous_Millis = GetRawMilliSecTicks();
        IncrementTime();
        TickDifference =  m_Previous_Millis - elapsed_ticks;
        return true;
    }
    return false;

}

bool Time::Run()
{
    unsigned int current_ticks = GetRawMilliSecTicks();

    if(  (current_ticks - m_Previous_Millis) > 0)
    {
        if( (current_ticks - m_Previous_Millis) >= m_UpdateFrequencyInMillis)
        {
           return Update();
        }
    }
    else
    {
        if( (m_Previous_Millis - current_ticks + 0xFFFFFFFF ) >= m_UpdateFrequencyInMillis)
        {
          return Update();
        }
    }

    return false;
}





}