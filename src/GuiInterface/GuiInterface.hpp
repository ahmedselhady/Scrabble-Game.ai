#pragma once

class GuiInterface{

    public:

        /**
         * function: sendBoard:
         *      sends updated board to the gui module
         * inputs: 
         *      void
         * returns:
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send  
        */
        // TODO: add input of class type Board
        bool sendBoard();

        /**
         * function: sendScore:
         *      sends my new score to gui module
         * inputs:
         *      void
         * returns:
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send
        */
        bool sendMyScore();

        /**
         * function: sendOpponentScore:
         *      sends opponent's new score to gui module
         * inputs:
         *      void
         * returns:
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send
        */
        void sendOpponentScore();

        /**
         * function: sendTilesRack
         *      sends the updated rack of tiles of mine
         * inputs:
         *      void
         * returns: 
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send
        */
        bool sendTilesRack();

        /**
         * function: sendTurn
         *      sends the current turn; Mine or Opponent's 
         * inputs:
         *      void
         * returns:
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send        
        */
        bool sendTurn();

        /**
         * function: chooseMode
         *      updates the global flag of GameMode as selected from GUI Starting Screen
         * inputs:
         *      void
         * returns:
         *      void
        */
        void chooseMode();

        /**
         * function: draggedTile
         *      Note: For Teacher Mode only
         *      receives the tile being dragged from rack and dropped at position i,j
         *      it then updates the board state, and the local score of this move
         * inputs:
         *      void // TODO: update if it should receive an input
         * returns:
         *      void
        */
        void draggedTile();

        /**
         * function: sendLocalScore
         *      Note: For Teacher Mode only         
         *      sends the Local updated score for the dragged tile in Teacher Mode
         * inputs:
         *      void // TODO: update if it should receive an input
         * returns: 
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send        
        */
        bool sendLocalScore();

        /**
         * function: sendAgentResponse
         *      Note: For Teacher Mode only         
         *      sends the agent response to the played move by Human from AgentResponse Enumerator defined in Defiitions.hpp
         * inputs:
         *      void // TODO: update if it should receive an input
         * returns:
         *      flag: boolean; True for successful send
         *                     False for unsuccessful send        
        */
        bool sendAgentResponse();

        
    private:
        // TODO: Add data members: board, tiles,my score, opponent's score, turn, Mode 
};