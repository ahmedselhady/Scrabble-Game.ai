#pragma once

class AIInterface{

    public:

        /**
         * function: suggestedMove:
         *      recieves suggested move from the grammer
         * inputs:
         *      void // TODO: update if it should recieve an input
         * returns:
         *      void // OPTIONAL: return true for successful recieving and false for unsuccessful recieving
        */
        void suggestedMove();

        /**
         * function: trackMoves:
         *      keeps record of the moves made by the player and the opponnet
         * inputs:
         *      void
         * returns:
         *      void
        */
        void trackMoves();

        /**
         * function: sendPossibleMove:
         *      sends all the possible moves fro the next turn to the decision making module
         * inputs:
         *      void
         * returns:
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send
         */
        bool sendNextPossibleMove();

        /**
         * function: sendBestMove:
         *      sends the best move among all the possible moves to the decision making module
         * inputs:
         *      void
         * returns:
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send
         */
        bool sendBestMove();

    private:
        //TODO: Add data members if needed according to the integration phase
};