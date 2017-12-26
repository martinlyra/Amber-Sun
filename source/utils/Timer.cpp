//
// Created by Martin Lyrå on 2017-12-18.
//

#include "Timer.h"

#include <cstdio>
#include <sys/time.h>

#ifdef DEBUG
ScopeTimer::ScopeTimer(const char *description)
{
    this->description = description;
    timestamp = Time::Now();
}

ScopeTimer::~ScopeTimer()
{
    const double t1 = Time::Now();
    const double diff = t1 - timestamp;
    std::printf("Timer | %s : %f ms\n", description, diff);
}
#endif

double Time::Now()
{
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec*1e3 + tv.tv_usec*1e-3;
}