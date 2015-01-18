#include "PK_tTimeSpan.h"
#include "PK_Exceptions.h"


namespace PK
{

PK_TimeSpan PK_TimeSpan::MinValue(-0xFFFFFFFFFFFFFFF); // FIXME - colocar minimo de um long long

//
PK_TimeSpan::PK_TimeSpan()
{
    m_ticks = 0;
}

//
PK_TimeSpan::PK_TimeSpan(long long ticks)
{
    m_ticks = ticks;
}

//
PK_TimeSpan::PK_TimeSpan(int hours, int minutes, int seconds)
{
    m_ticks = PK_TimeSpan::TimeToTicks(hours, minutes, seconds);
}

//
PK_TimeSpan::PK_TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds)
{
    long long num = ((long long) days * 3600L * 24L + (long long) hours * 3600L + (long long) minutes * 60L + (long long) seconds) * 1000L + (long) milliseconds;
    if (num > PK_MAX_MILLISECONDS || num < PK_MIN_MILLISECONDS)
    {
        throw PK_ArgumentOutOfRangeException("days,hours,minutes,seconds,milliseconds", "Cannot create TimeSpan because size would be too long.", __FILE__, __LINE__);
    }
    m_ticks = num * PK_TICKS_PER_MILLISECOND;
}

//
PK_TimeSpan::PK_TimeSpan(int days, int hours, int minutes, int seconds)
{
    long long num = ((long) days * 3600L * 24L + (long) hours * 3600L + (long) minutes * 60L + (long) seconds) * 1000L + (long) 0;
    if (num > PK_MAX_MILLISECONDS || num < PK_MIN_MILLISECONDS)
    {
        throw PK_ArgumentOutOfRangeException("days,hours,minutes,seconds", "Cannot create TimeSpan because size would be too long.", __FILE__,__LINE__);
    }
    m_ticks = num * PK_TICKS_PER_MILLISECOND;
}

//
PK_TimeSpan PK_TimeSpan::operator +(const PK_TimeSpan &t1)
{
    PK_TimeSpan t = *this;
    t.Add(t1);
    return t;
}

//
PK_TimeSpan PK_TimeSpan::operator -(const PK_TimeSpan &t1)
{
    PK_TimeSpan t = *this;
    t.Subtract(t1);
    return t;
}

//
void PK_TimeSpan::Add(const PK_TimeSpan &ts)
{
    long long ticks = m_ticks + ts.m_ticks;
    if (m_ticks >> 63 == ts.m_ticks >> 63 && m_ticks >> 63 != ticks >> 63)
    {
        throw PK_OverflowException("TimeSpan overflow.", __FILE__, __LINE__);
    }
    m_ticks = ticks;
}

//
void PK_TimeSpan::Subtract(const PK_TimeSpan &ts)
{
    long long ticks = m_ticks - ts.m_ticks;
    if (m_ticks >> 63 != ts.m_ticks >> 63 && m_ticks >> 63 != m_ticks >> 63)
    {
         throw PK_OverflowException("TimeSpan overflow.", __FILE__, __LINE__);
    }
    m_ticks = ticks;
}

//
int PK_TimeSpan::CompareTo(const PK_TimeSpan &ts) const
{
    long long num = ts.m_ticks;
    if (m_ticks > num)
    {
        return 1;
    }
    return (m_ticks < num ? -1 : 0);
}

//
unsigned long long PK_TimeSpan::Duration()
{
    if (m_ticks == PK_TimeSpan::MinValue.GetTicks())
    {
        throw PK_OverflowException("TimeSpan duration overflow.", __FILE__, __LINE__);
    }
    return (m_ticks >= 0L ? m_ticks : -m_ticks);
}

// static
PK_TimeSpan PK_TimeSpan::FromTicks(long long value)
{
    return PK_TimeSpan(value);
}

// static
PK_TimeSpan PK_TimeSpan::FromMilliseconds(double value)
{
    return PK_TimeSpan::Interval(value, 1);
}

// static
PK_TimeSpan PK_TimeSpan::FromSeconds(double value)
{
    return PK_TimeSpan::Interval(value, PK_MILLIS_PER_SECOND);
}

// static
PK_TimeSpan PK_TimeSpan::FromMinutes(double value)
{
    return PK_TimeSpan::Interval(value, PK_MILLIS_PER_MINUTE);
}

// static 
PK_TimeSpan PK_TimeSpan::FromHours(double value)
{
    return PK_TimeSpan::Interval(value, PK_MILLIS_PER_HOUR);
}

// static
PK_TimeSpan PK_TimeSpan::FromDays(double value)
{
    return PK_TimeSpan::Interval(value, PK_MILLIS_PER_DAY);
}

// static 
int PK_TimeSpan::Compare(const PK_TimeSpan &t1, const PK_TimeSpan &t2) 
{
    if (t1.m_ticks > t2.m_ticks)
    {
        return 1;
    }
    return (t1.m_ticks < t2.m_ticks ? -1 : 0);
}

// static 
bool PK_TimeSpan::Equals(const PK_TimeSpan &t1, const PK_TimeSpan &t2) 
{
    return (t1.m_ticks == t2.m_ticks);
}

// static
long long PK_TimeSpan::TimeToTicks(int hour, int minute, int second)
{
    long long num = ((long) hour * 3600L) + ((long) minute * 60L) + (long) second;
    if (num > PK_MAX_SECONDS || num < PK_MIN_SECONDS)
    {
        throw PK_ArgumentOutOfRangeException("hour,minute,second", "Cannot create TimeSpan because size would be too long.", __FILE__, __LINE__);
    }
    return num * PK_TICKS_PER_SECOND;
}

// static
PK_TimeSpan PK_TimeSpan::Interval(double value, int scale)
{
    double num = value * (double) scale + (value >= 0.0 ? 0.5 : -0.5);
    if (num > (double)PK_MAX_MILLISECONDS || num < (double)PK_MIN_MILLISECONDS)
    {
        throw PK_OverflowException("TimeSpan overflow.", __FILE__, __LINE__);
    }
    return PK_TimeSpan((long) num * PK_TICKS_PER_MILLISECOND);
}

} // namespace
