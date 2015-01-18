#ifndef __PK_TDATETIME_H__
#define __PK_TDATETIME_H__

#include "PK_Consts.h"

namespace PK {

struct PK_DateTime
{
private:
    unsigned long long m_dateData;

public:
    PK_DateTime();
    PK_DateTime(unsigned long long dateData);
    PK_DateTime(int year, int month, int day);
    void AddTicks(long long value);
    void AddDays(double value);
    void AddMonths(int months);
    void AddYears(int value);
    int CompareTo(const PK_DateTime &value);

    static int Compare(const PK_DateTime &t1, const PK_DateTime &t2);
    static bool IsLeapYear(int year);
    static int DaysInMonth(int year, int month);

private:
    void Add(double value, int scale);
    int GetDatePart(int part) const;
    static long long TimeToTicks(int hour, int minute, int second);
    static long long DateToTicks(int year, int month, int day);

    inline long long GetInternalTicks() const
    {
        return (long long)(m_dateData & PK_TICKS_MASK);
    }
    inline unsigned long long GetInternalKind() const
    {
      return (m_dateData & PK_FLAGS_MASK);
    }

public:
    inline long long GetTicks() const
    {
        return GetInternalTicks();
    }
    inline int GetMillisecond() const
    {
        return (int) (GetInternalTicks() / PK_TICKS_PER_MILLISECOND % 1000L);
    }
    inline int GetSecond() const
    {
        return (int) (GetInternalTicks() / PK_TICKS_PER_SECOND % 60L);
    }
    inline int GetMinute() const
    {
        return (int) (GetInternalTicks() / PK_TICKS_PER_MINUTE % 60L);
    }
    inline int GetHour() const
    {
        return (int) (GetInternalTicks() / PK_TICKS_PER_HOUR % 24L);
    }
    inline int GetDay() const
    {
        return GetDatePart(3);
    }
    inline int GetMonth() const
    {
        return (GetDatePart(2));
    }
    inline int GetYear() const
    {
        return GetDatePart(0);
    }

};

} // Namespace
#endif
