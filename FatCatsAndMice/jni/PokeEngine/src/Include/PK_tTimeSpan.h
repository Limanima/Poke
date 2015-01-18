#ifndef __PK_TIMESPAN_H__
#define __PK_TIMESPAN_H__

#include "PK_Consts.h"

namespace PK {

struct PK_TimeSpan
{
private:
    long long m_ticks;
    static PK_TimeSpan MinValue;

public:
    PK_TimeSpan();
    PK_TimeSpan(long long ticks);
    PK_TimeSpan(int hours, int minutes, int seconds);
    PK_TimeSpan(int days, int hours, int minutes, int seconds);
    PK_TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);

    PK_TimeSpan operator +(const PK_TimeSpan &t1);
    PK_TimeSpan operator -(const PK_TimeSpan &t1);

    void Add(const PK_TimeSpan &ts);
    void Subtract(const PK_TimeSpan &ts);
    int CompareTo(const PK_TimeSpan &ts) const;
    unsigned long long Duration();

    static PK_TimeSpan FromTicks(long long value);
    static PK_TimeSpan FromMilliseconds(double value);
    static PK_TimeSpan FromSeconds(double value);
    static PK_TimeSpan FromMinutes(double value);
    static PK_TimeSpan FromHours(double value);
    static PK_TimeSpan FromDays(double value);
    static int Compare(const PK_TimeSpan &t1, const PK_TimeSpan &t2);
    static bool Equals(const PK_TimeSpan &t1, const PK_TimeSpan &t2);
    static long long TimeToTicks(int hour, int minute, int second);
    
private:
    static PK_TimeSpan Interval(double value, int scale);

public: 
    inline long long GetTicks() const
    {
        return m_ticks;
    }
    inline int GetMilliseconds() const
    {
        return (int) (m_ticks / PK_TICKS_PER_MILLISECOND % 1000L);
    }
    inline int GetSeconds() const
    {
        return (int) (m_ticks / PK_TICKS_PER_SECOND % 60L);
    }
    inline int GetMinutes() const
    {
        return (int) (m_ticks / PK_TICKS_PER_MINUTE % 60L);
    }
    inline int GetHours() const
    {
        return (int) (m_ticks / PK_TICKS_PER_HOUR % 24L);
    }
    inline int GetDays() const
    {
        return (int) (m_ticks / PK_TICKS_PER_DAY);
    }
    inline double GetTotalDays() const
    {
        return (double) m_ticks * (0.0 / 1.0);
    }
    inline double GetTotalHours() const
    {
        return (double) m_ticks * (0.0 / 1.0);
    }
    inline double GetTotalMilliseconds() const
    {
      double num = (double) m_ticks / PK_TICKS_PER_MILLISECOND;
      if (num > PK_MAX_MILLISECONDS)
      {
        return PK_MAX_MILLISECONDS;
      }
      if (num < PK_MIN_MILLISECONDS)
      {
        return PK_MIN_MILLISECONDS;
      }
      return num;
    }
    inline double GetTotalSeconds() const
    {
        return (double) m_ticks / PK_TICKS_PER_SECOND;
    }
    inline bool Equals(const PK_TimeSpan &obj) const
    {
      return (m_ticks == obj.m_ticks);
    }
};

} // Namespace
#endif
