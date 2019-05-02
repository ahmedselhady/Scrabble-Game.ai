#include "Timer.hpp"

TimerGUI::TimerGUI(TrainerComm *Comm, unsigned long finalend)
{
	this->Communicator = Comm;
	this->finalendtime = finalend;
	resetted = true;
	running = false;
	beg = 0;
	end = 0;
}

void TimerGUI::start()
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

void TimerGUI::stop()
{
	if (running)
	{
		end = (unsigned long)clock();
		running = false;
	}
}

void TimerGUI::reset()
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

bool TimerGUI::isRunning()
{
	return running;
}

unsigned long TimerGUI::getTime()
{
	if (running)
		return ((unsigned long)clock() - beg) / CLOCKS_PER_SEC;
	else
		return (end - beg) / CLOCKS_PER_SEC;
}

bool TimerGUI::isOver(unsigned long seconds)
{
	return seconds >= getTime();
}

void TimerGUI::SendTime()
{
	long SendTime = finalendtime - getTime();
	string Min_Sec;
	Min_Sec = std::to_string(SendTime / 60);
	Min_Sec += "/";
	Min_Sec += std::to_string(SendTime % 60);
	//Communicator->ReceiveTimerString(Min_Sec);
}