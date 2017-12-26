//
// Created by Martin Lyrå on 2017-12-18.
//

#ifndef AMBER_SUN_TIMER_H
#define AMBER_SUN_TIMER_H

#define P3H__(a,b,c) a ## b ## c
#define P3__(a,b,c) P3H__(a,b,c)
#define UID__ P3__(LINE_, __LINE__, _)

#ifdef DEBUG
class ScopeTimer
{
public:
    ScopeTimer(const char* description);
    ~ScopeTimer();

private:
    double timestamp;
    const char* description;
};

#define TIMER(desc) ScopeTimer UID__(desc)
#else
#define TIMER(desc) ;
#endif

namespace Time
{
    struct TimeSpan {
        long seconds;
        long microseconds; // 10*e-06

        TimeSpan(long sec, long usec)
                : seconds(sec), microseconds(usec)
        {}
    };

    double Now();

}

#endif //AMBER_SUN_TIMER_H
