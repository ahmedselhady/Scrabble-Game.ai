#pragma once

#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include"../SharedClasses/TrainerComm.hpp"


class  Timer
{
private:
    TrainerComm* Communicator;
public:
    Timer(TrainerComm*);

    void SendCurrentTime();
};

 Timer:: Timer(/* args */)
{
}
