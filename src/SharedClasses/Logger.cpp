#include "Logger.hpp"
#include <string>
#include <fstream>
#include <iostream>


void Logger::log(std::string message){ // log function begin
    
    std::ofstream logFile; // local scope instance of output file
    logFile.open("log.txt",std::ios::app); // open log.txt file in write/append mode

    if(logFile.is_open()){ // if begin
        logFile<<message<<std::endl; // print the log message in a separate line
        logFile.close(); // close file to free resources
    } // if end
    else{ // else begin
        std::cout<<"Error: could NOT open log file...\n";
    } // else end

} // log function end

