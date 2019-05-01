#pragma once

#include <conio.h>
#include <time.h>
#include <string>

class TimerClock
{
private:
    bool resetted;
    bool running;
    unsigned long beg;
    unsigned long end;
    unsigned long finalendtime;

public:
    TimerClock(unsigned long);
    void start();
    void stop();
    void reset();
    bool isRunning();
    unsigned long getTime();
    bool isOver(unsigned long seconds);
    void SendTime();
};
