#include"Timer.hpp"

 Timer:: Timer(TrainerComm* Comm)
{
    this->Communicator = Comm;
}

void Timer::SendCurrentTime ()
{
        auto Timer = std::chrono::high_resolution_clock::now()+ std::chrono::minutes(20);

	auto Current = std::chrono::high_resolution_clock::now();

	auto difference = std::chrono::duration_cast<std::chrono::seconds>(Timer - Current).count();

	std::cout << "Current Timer: " << difference/60<<" : "<<difference%60<<"\n";
    string Min_Sec;
    Min_Sec=std::to_string(difference/60);
    Min_Sec+="/";
    Min_Sec+=std::to_string(difference%60);
        //Communicator->ReceiveTimerString(Min_Sec);
}