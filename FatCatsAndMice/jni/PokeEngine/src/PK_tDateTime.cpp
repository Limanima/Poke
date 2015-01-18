#include "PK_tDateTime.h"
#include "PK_tTimeSpan.h"
#include "PK_Exceptions.h"

namespace PK
{

int g_PKDaysToMonth365[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
int g_PKDaysToMonth366[13] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

//
PK_DateTime::PK_DateTime()
{
    m_dateData = 0;
}

//
PK_DateTime::PK_DateTime(unsigned long long dateData)
{
    m_dateData = dateData;
}

//
PK_DateTime::PK_DateTime(int year, int month, int day)
{
    m_dateData = (unsigned long long) PK_DateTime::DateToTicks(year, month, day);
}

//
void PK_DateTime::AddTicks(long long value)
{
    long long internalTicks = GetInternalTicks();

    if (value > PK_MAX_TICKS - internalTicks || value < -internalTicks)
    {
        throw PK_ArgumentOutOfRangeException("value", __FILE__, __LINE__);
    }
    m_dateData = (unsigned long long) (internalTicks + value) | GetInternalKind();
}

//
void PK_DateTime::AddDays(double value)
{
    Add(value, PK_MILLIS_PER_DAY);
}

void PK_DateTime::AddMonths(int months)
{
    if (months < -120000 || months > 120000)
    {
        throw PK_ArgumentOutOfRangeException("months", __FILE__, __LINE__);
    }
    int datePart1 = GetDatePart(0);
    int datePart2 = GetDatePart(2);
    int day = GetDatePart(3);
    int num1 = datePart2 - 1 + months;
    int month;
    int year;
    if (num1 >= 0)
    {
        month = num1 % 12 + 1;
        year = datePart1 + num1 / 12;
    }
    else
    {
        month = 12 + (num1 + 1) % 12;
        year = datePart1 + (num1 - 11) / 12;
    }

    if (year < 1 || year > 9999)
    {
        throw new PK_ArgumentOutOfRangeException("months", __FILE__, __LINE__);
    }

    int num2 = PK_DateTime::DaysInMonth(year, month);
    if (day > num2)
    {
        day = num2;
    }

    m_dateData = (unsigned long long) (PK_DateTime::DateToTicks(year, month, day) + GetInternalTicks() % PK_TICKS_PER_DAY) | GetInternalKind();
}

//
void PK_DateTime::AddYears(int value)
{
    if (value < -10000 || value > 10000)
    {
        throw PK_ArgumentOutOfRangeException("years", __FILE__, __LINE__);
    }
      
    AddMonths(value * 12);
}

//
int PK_DateTime::CompareTo(const PK_DateTime &value)
{
    return Compare(*this, value);
}

//
void PK_DateTime::Add(double value, int scale)
{
    long long num = (long long) (value * (double) scale + (value >= 0.0 ? 0.5 : -0.5));
      
    if (num <= -PK_MAX_MILLIS || num >= PK_MAX_MILLIS)
    {
        throw new PK_ArgumentOutOfRangeException("value", __FILE__, __LINE__);
    }

    AddTicks(num * PK_TICKS_PER_MILLISECOND);
}

//
int PK_DateTime::GetDatePart(int part) const
{
    int num1 = (int) (GetInternalTicks() / PK_TICKS_PER_DAY);
    int num2 = num1 / PK_DAYS_PER_400_YEARS;
    int num3 = num1 - num2 * PK_DAYS_PER_400_YEARS;
    int num4 = num3 / PK_DAYS_PER_100_YEARS;
    if (num4 == 4)
    {
        num4 = 3;
    }
    int num5 = num3 - num4 * PK_DAYS_PER_100_YEARS;
    int num6 = num5 / PK_DAYS_PER_4_YEARS;
    int num7 = num5 - num6 * PK_DAYS_PER_4_YEARS;
    int num8 = num7 / PK_DAYS_PER_YEAR;
    if (num8 == 4)
    {
        num8 = 3;
    }
    if (part == 0)
    {
        return num2 * 400 + num4 * 100 + num6 * 4 + num8 + 1;
    }
    int num9 = num7 - num8 * PK_DAYS_PER_YEAR;
    if (part == 1)
    {
        return num9 + 1;
    }
    int *pNumArray = (num8 == 3 && (num6 != 24 || num4 == 3)) ? g_PKDaysToMonth366 : g_PKDaysToMonth365;
    int index = num9 >> 6;
    while (num9 >= pNumArray[index])
    {
        ++index;
    }
    if (part == 2)
    {
    return index;
    }
      
    return num9 - pNumArray[index - 1] + 1;
}

// static 
int PK_DateTime::Compare(const PK_DateTime &t1, const PK_DateTime &t2)
{
    long long internalTicks1 = t1.GetInternalTicks();
    long long internalTicks2 = t2.GetInternalTicks();
    if (internalTicks1 > internalTicks2)
    {
        return 1;
    }

    return (internalTicks1 < internalTicks2 ? -1 : 0);
}

// static 
bool PK_DateTime::IsLeapYear(int year)
{
    if (year < 1 || year > 9999)
    {
        throw PK_ArgumentOutOfRangeException("year", __FILE__, __LINE__);
    }

    if (year % 4 != 0)
    {
        return false;
    }
    if (year % 100 == 0)
    {
        return year % 400 == 0;
    }

    return true;
}

// static
int PK_DateTime::DaysInMonth(int year, int month)
{
  if (month < 1 || month > 12)
  {
     throw PK_ArgumentOutOfRangeException("month", __FILE__, __LINE__);
  }
  int *pNumArray = (PK_DateTime::IsLeapYear(year) ? g_PKDaysToMonth366 : g_PKDaysToMonth365);
  return pNumArray[month] - pNumArray[month - 1];
}

// static 
long long PK_DateTime::TimeToTicks(int hour, int minute, int second)
{
    if (hour >= 0 && hour < 24 && (minute >= 0 && minute < 60) && (second >= 0 && second < 60))
    {
        return PK_TimeSpan::TimeToTicks(hour, minute, second);
    }
    throw PK_ArgumentOutOfRangeException("hour,minute,second", __FILE__, __LINE__);
}

// static 
long long PK_DateTime::DateToTicks(int year, int month, int day)
{
  if (year >= 1 && year <= 9999 && (month >= 1 && month <= 12))
  {
    int *pNumArray = (PK_DateTime::IsLeapYear(year) ? g_PKDaysToMonth366 : g_PKDaysToMonth365);
    if (day >= 1 && day <= pNumArray[month] - pNumArray[month - 1])
    {
        int num = year - 1;
        return (long long)(num * 365 + num / 4 - num / 100 + num / 400 + pNumArray[month - 1] + day - 1) * PK_TICKS_PER_DAY;
    }
  }
  throw PK_ArgumentOutOfRangeException("year,month,day", __FILE__, __LINE__);
}    

} // namespace
