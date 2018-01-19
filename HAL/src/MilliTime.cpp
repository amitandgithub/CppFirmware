

#include "MilliTime.hpp"
#include "Test.h"

namespace Utility
{

void MilliTime::Set(unsigned char hrs, unsigned char min, unsigned char sec, unsigned int millis)
{
    if(millis > 999)
    {
        millis = millis - 999;
        Sec++;
    }
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
    Millis = millis;
    Sec    = sec;
    Min    = min;
    Hrs    = hrs;
}

MilliTime::MilliTime(unsigned char hrs, unsigned char min, unsigned char sec, unsigned int millis)
{
    if(millis > 999)
    {
        millis = millis - 999;
        Sec++;
    }
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
    Millis = millis;
    Sec    = sec;
    Min    = min;
    Hrs    = hrs;
}

// Overload + for MilliTime.
MilliTime MilliTime::operator+(MilliTime t)
{
    MilliTime temp;

    temp.Millis = t.Millis + Millis;
    temp.Sec    = t.Sec + Sec;
    temp.Min    = t.Min + Min;
    temp.Hrs    = t.Hrs + Hrs;

    if(temp.Millis > 999)
    {
        temp.Millis = temp.Millis - 999;
        temp.Sec++;
    }

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

        // Overload - for MilliTime.
MilliTime MilliTime::operator-(MilliTime t)
{
    MilliTime temp;

    if( (t.Millis - Millis) >= 0 )
    {
        temp.Millis = t.Millis - Millis;
    }
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

MilliTime MilliTime::operator++()
{
    Millis++;

    if(Millis > 999)
    {
        Millis = Millis - 999;
        Sec++;
    }
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

MilliTime MilliTime::operator++(int x)
{
    Millis++;

    if(Millis > 999)
    {
        Millis = Millis - 999;
        Sec++;
    }
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

MilliTime MilliTime::operator--()
{
   unsigned char MillisCarry = 0;
   unsigned char SecCarry = 0;
   unsigned char MinCarry = 0;

    if( Millis == 0 )
    {
       Millis = 999;
       MillisCarry = 1;
    }
    else
    {
      Millis--;
    }
    if( Sec == 0 )
    {
       Sec = 59;
       SecCarry = 1;
    }
    else
    {
        Sec = Sec -1 - MillisCarry ;
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

void MilliTime::AddMillis(unsigned int millis)
{
    Millis = Millis + millis;

    if(Millis > 999)
    {
        Millis = Millis - 999;
        Sec++;
    }
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


}
void MilliTime::Get(unsigned char* hrs, unsigned char* min, unsigned char* sec, unsigned int* millis)
{
    *millis = Millis;
    *sec    = Sec;
    *min    = Min;
    *hrs    = Hrs;
}

char* MilliTime::Get(char* pBuffer)
{
    intToStr(Hrs, &pBuffer[0], 2);
    pBuffer[2] = ':';
    intToStr(Min, &pBuffer[3], 2);
    pBuffer[5] = ':';
    intToStr(Sec, &pBuffer[6], 2);
    pBuffer[8] = ':';
    intToStr(Millis, &pBuffer[9], 3);
    return pBuffer;
}

void MilliTime::IncrementTime()
{
    (*this)++;
}

bool MilliTime::Run()
{
    unsigned int ElapsedTicks;

    ElapsedTicks = GetRawMiliSecTicksSince(m_Previous_Millis);

    if( ElapsedTicks > 1)
    {
        m_Previous_Millis = GetRawMilliSecTicks();
        //IncrementTime();
        //Set(0,0,0,ElapsedTicks + Millis);
        //SetMillis(ElapsedTicks + Millis);
        AddMillis(ElapsedTicks);

        return true;
    }
    return false;
}


















}