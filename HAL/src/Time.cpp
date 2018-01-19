


#include "Time.hpp"
#include "Test.h"

namespace Utility
{


void Time::Set(unsigned char hrs, unsigned char min, unsigned char sec)
{
    if(sec > 60)
    {
        sec = sec - 60;
        min++;
    }

    if(min > 60)
    {
        min = min - 60;
        hrs++;
    }

    Sec = sec;
    Min = min;
    Hrs = hrs;
}

Time::Time(unsigned char hrs, unsigned char min, unsigned char sec)
{
    if(sec > 60)
    {
        sec = sec - 60;
        min++;
    }

    if(min > 60)
    {
        min = min - 60;
        hrs++;
    }

    Sec = sec;
    Min = min;
    Hrs = hrs;
}

// Overload + for Time.
Time Time::operator+(Time t)
{
    Time temp;
    temp.Sec = t.Sec + Sec;
    temp.Min = t.Min + Min;
    temp.Hrs = t.Hrs + Hrs;

    if(temp.Sec > 60)
    {
        temp.Sec = temp.Sec - 60;
        temp.Min++;
    }

    if(temp.Min > 60)
    {
        temp.Min = temp.Min - 60;
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

    if(Sec > 60)
    {
        Sec = Sec - 60;
        Min++;
    }

    if(Min > 60)
    {
        Min = Min - 60;
        Hrs++;
    }
    return *this;
}

Time Time::operator++(int x)
{
    Sec++;

    if(Sec > 60)
    {
        Sec = Sec - 60;
        Min++;
    }

    if(Min > 60)
    {
        Min = Min - 60;
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







}