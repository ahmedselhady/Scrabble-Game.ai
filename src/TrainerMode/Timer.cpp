#include "Timer.hpp"

TimerClock::TimerClock(unsigned long finalend)
{
	// this->Communicator = Comm;
	this->finalendtime = finalend;
	resetted = true;
	running = false;
	beg = 0;
	end = 0;
}

void TimerClock::start()
{
	if (!running)
	{
		if (resetted)
			beg = (unsigned long)clock();
		else
			beg -= end - (unsigned long)clock();
		running = true;
		resetted = false;
	}
}

void TimerClock::stop()
{
	if (running)
	{
		end = (unsigned long)clock();
		running = false;
	}
}

void TimerClock::reset()
{
	bool wereRunning = running;
	if (wereRunning)
		stop();
	resetted = true;
	beg = 0;
	end = 0;
	if (wereRunning)
		start();
}

bool TimerClock::isRunning()
{
	return running;
}

unsigned long TimerClock::getTime()
{
	if (running)
		return ((unsigned long)clock() - beg) / CLOCKS_PER_SEC;
	else
		return (end - beg) / CLOCKS_PER_SEC;
}

bool TimerClock::isOver(unsigned long seconds)
{
	return seconds >= getTime();
}

void TimerClock::SendTime()
{
	long SendTime = finalendtime - getTime();
	std::string Min_Sec;
	Min_Sec = std::to_string(SendTime / 60);
	Min_Sec += "/";
	Min_Sec += std::to_string(SendTime % 60);
	//Communicator->ReceiveTimerString(Min_Sec);
}