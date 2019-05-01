#include"Timer.hpp"
/*
std::chrono::time_point<std::chrono::steady_clock> begTime,PausTime;

 Timer:: Timer(TrainerComm* Comm)
{
    this->Communicator = Comm;
           
    begTime = std::chrono::high_resolution_clock::now()
                + std::chrono::minutes(20);

}

void Timer::SendCurrentTime ()
{

	auto Current = std::chrono::high_resolution_clock::now();

	auto difference = std::chrono::duration_cast<std::chrono::seconds>(begTime - Current).count();

	std::cout << "Current Timer: " << difference/60<<" : "<<difference%60<<"\n";
    string Min_Sec;
    Min_Sec=std::to_string(difference/60);
    Min_Sec+="/";
    Min_Sec+=std::to_string(difference%60);
        //Communicator->ReceiveTimerString(Min_Sec);
}

void PauseTime()
{
    PausTime =std::chrono::high_resolution_clock::now();
}*/
Timer::Timer(TrainerComm* Comm,unsigned long  finalend) {
    this->Communicator = Comm;
    this->finalendtime = finalend ;
	resetted = true;
	running = false;
	beg = 0;
	end = 0;
}


void Timer::start() {
	if (!running) {
		if (resetted)
			beg = (unsigned long)clock();
		else
			beg -= end - (unsigned long)clock();
		running = true;
		resetted = false;
	}
}


void Timer::stop() {
	if (running) {
		end = (unsigned long)clock();
		running = false;
	}
}


void Timer::reset() {
	bool wereRunning = running;
	if (wereRunning)
		stop();
	resetted = true;
	beg = 0;
	end = 0;
	if (wereRunning)
		start();
}


bool Timer::isRunning() {
	return running;
}


unsigned long Timer::getTime() {
	if (running)
		return ((unsigned long)clock() - beg) / CLOCKS_PER_SEC;
	else
		return (end - beg) / CLOCKS_PER_SEC;
}


bool Timer::isOver(unsigned long seconds) {
	return seconds >= getTime();
}

void Timer::SendTime()
{
    long SendTime = finalendtime-getTime();
	string Min_Sec;
    Min_Sec=std::to_string(SendTime/60);
    Min_Sec+="/";
    Min_Sec+=std::to_string(SendTime%60);
    //Communicator->ReceiveTimerString(Min_Sec);
}