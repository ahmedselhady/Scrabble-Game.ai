#include "Logger.hpp"
#include <string>
#include <iostream>


void Logger::log(std::string message){ // log function begin    
    std::cout<<message<<std::endl; // use standard console screen instead of file output to avoid I/O bounded process
} // log function end

