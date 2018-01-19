//******************
// CLASS: Time
//
// DESCRIPTION:
//  This class is meant for the Time related operations
//
// CREATED: 18-01-2018, by Amit Chaudhary
//
// FILE: $FILE_FNAME$
//
#ifndef TIME_HPP_
#define TIME_HPP_



namespace Utility
{

class Time
{
public:
    Time():Sec(0),Min(0),Hrs(0){};
    Time(unsigned char hrs, unsigned char min, unsigned char sec);
    ~Time(){};
    Time operator+(Time t);
    Time operator-(Time t);
    Time operator++();
    Time operator++(int x);
    Time operator--();
    void Get(unsigned char* hrs, unsigned char* min, unsigned char* sec);
    char* Get(char* pBuffer);
    unsigned char GetSec(){return Sec;}
    unsigned char GetMin(){return Min;}
    unsigned char GetHrs(){return Hrs;}
    void SetSec(unsigned char sec){Sec = sec;}
    void SetMin(unsigned char min){Min = min;}
    void SetHrs(unsigned char hrs){Hrs = hrs;}
    void Set(unsigned char hrs, unsigned char min, unsigned char sec);

private:
        unsigned char Sec;
        unsigned char Min;
        unsigned char Hrs;

};

}


#endif // TIME_HPP_