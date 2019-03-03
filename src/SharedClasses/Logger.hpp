#pragma once

#include <string>

class Logger{

    public:

        /**
         * function: log
         *      prints message to log file "log.txt"
         * inputs:
         *      message: string; MESSAGE TO LOG
         * returns:
         *      void
        */
        static void log(std::string message);
        
    private:

        
        /**
         * Constructor:
         *      default private constructor: prevent instantiation of the class
         * inputs:
         *      void
         * returns:
         *      no return
        */
        Logger(){}

};