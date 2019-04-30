
//TODO: Completion of Move Generation Algorithm.
#include "MoveGenerate.h"
#include "LoadGaddag.h"
#include "Gaddag.h"
#include <iostream>

using namespace std;

//This Function it takes a Reference to the Board.
WordGenerate::WordGenerate(BoardToGrammer *board, Node *root, int bagSize, bool isEmptyBoard, bool bagSizeGreaterThanZero /*,Evaluator *EvalCalculator*/)
{
    this->board = board; // catching a boardcomm. verison object.
    this->root = root;
    //  this->EvalCalculator = EvalCalculator;
    this->bagSize = bagSize;
    this->isEmptyBoard = isEmptyBoard;
    this->bagSizeGreaterThanZero = bagSizeGreaterThanZero;
}

/*
This Function iterates on each sqaure in the board and performing the algo. Taking the board 2-Dimensions into Consideration.
and it iterates on each sqaure in the board and performing the algo.
*/
void WordGenerate::generateWords()
{
    bool isAnchorSquare = false;
    countRoomLeft = 0;
    string word;

    moves.clear(); // clear all moves. Later on paramters(BOOL) can be passsed to shape the needed return.

    //countTilesRack(NULL);
    for (int indexRow = 0; indexRow < MAX_BOARD_ROWS; ++indexRow)
    {
        for (int indexCol = 0; indexCol < MAX_BOARD_COLS; ++indexCol)
        {
            word = "";

            //Horizonatal Move Generation:
            setDirectionOptions(indexRow, indexCol, true); // true -> horizontal.
            //currCrossSet.reset();
            isAnchorSquare = isAnchor(indexRow, indexCol);
            if (isAnchorSquare)
            {
                //currCrossSet.set();
                countRoomLeft = roomLeftCount(indexRow, indexCol);
                anchorRow = indexRow;
                anchorCol = indexCol;
                gen(0, word, this->root);
            }

            word = "";
            //Vertical Move Generation:
            setDirectionOptions(indexRow, indexCol, false); // false -> vertical.
            //currCrossSet.reset();
            isAnchorSquare = isAnchor(indexRow, indexCol);
            if (isAnchorSquare)
            {
                //currCrossSet.set();
                countRoomLeft = roomLeftCount(indexRow, indexCol);
                anchorRow = indexRow;
                anchorCol = indexCol;
                gen(0, word, this->root);
            }
        }
    }
}

//This Function is this square given row and col an anchor sqaure.
bool WordGenerate::isAnchor(int row, int col)
{
    // NOTE: GADDAG algo. works from the left to right. it can be reversed but also need reverse of the structure itself DAGGAD.

    // what is an anchor square:
    /*
       1- if it has a letter on the square and its right sqaure doesn't.
        this means that "log" anchor's is 'g'. beacuse no need of 'o' or 'l' as anchors giving same repeated results.
       2- if it doesnot have a letter but it should at least have an opposite cross set to its current direction.
        this means that if a vertical word directly above a square i can attach a word to this square but hoirz.
     
    */

    if (board->hasaTile(row, col) && (currDirection == maxBorder - 1 || !board->hasaTile(row + rowOffset, col + colOffset)))
    {

        //char L = board->getTileAtPosition(row,col);
        return true;
    } // when there is a char.

    if (!board->hasaTile(row, col) && !(*currCrossSet)[row][col].all())
    {

        if ((currDirection == 0 || !board->hasaTile(row - rowOffset, col - colOffset)) && ((currDirection == maxBorder - 1) || !board->hasaTile(row + rowOffset, col + colOffset)))
        {
            return true;
        }
    } // when no char. on this square.

    return false;
} // is this square given row and col an anchor sqaure? Offsets used to make the function works in 2D (vert./horiz.)

//This Function it's important to stop right before a letter found while travesring the board leftward generating possible moves.
int WordGenerate::roomLeftCount(int row, int col)
{
    // count include the first char (itself).
    int countRoomLeft = 0;
    for (int offsetLeft = 0; offsetLeft <= currDirection; ++offsetLeft)
    { // CHANGED
        if (board->hasaTile(row - cancelIndex * (offsetLeft), col - (1 - cancelIndex) * (offsetLeft)))
        {
            countRoomLeft++;
        }
        else
        {
            break;
        }
    }

    for (int offsetLeft = currDirection - countRoomLeft - 1; offsetLeft >= 0; --offsetLeft)
    {
        if (((*currCrossSet)[(1 - cancelIndex) * row + cancelIndex * (offsetLeft)][cancelIndex * col + (1 - cancelIndex) * (offsetLeft)].all()) && !board->hasaTile((1 - cancelIndex) * row + cancelIndex * ((offsetLeft)), cancelIndex * col + (1 - cancelIndex) * (offsetLeft)))
        {
            if (offsetLeft == 0)
            {
                countRoomLeft++;
            }
            else
            {
                if (!board->hasaTile((1 - cancelIndex) * row + cancelIndex * (offsetLeft - 1), cancelIndex * col + (1 - cancelIndex) * (offsetLeft - 1)))
                {
                    countRoomLeft++;
                }
            }
        }
        else
        {

            break; // example: if you have a horizontally placed word "Log"  assume there are 2 valid words called "report" and "elog" for simplicity.
            /* 1-      *
                         R 
                   _ _ _ _ L O G _ _ _ 
                         P
                         O
                         R
                         T
                         _

                2-
                         R 
                   _ _ _ _ _ L O G _ _ _ 
                         P
                         O
                         R
                         T
                         _
                    .....
                    Where the '_' is space and '*' is a char.
                    So, in no. 1 here characters that would be taken into account are the spaces after the intersection between the two words as the RoomLeft = 6.
                    -> in the no. 2 example is "tricky" as the the anchor squares are 2 not one
                    to eliminate the duplicate words the RoomLeft of the 'G' anchor would be 3 only.
              */
        }
    }
    return countRoomLeft; // left count.
}

//This Gen funtion first function in Move Generation Algo.
void WordGenerate::gen(int pos, string word, Node *gaddagNode)
{
    char childLetter; // init.
    char boardLetter;
    Node *childNode;
    bitset<27> defaultCrossSet;
    // if(cancelIndex == 0){
    //     defaultCrossSet = Horiz_crossset[anchorRow][anchorCol+pos];
    // }
    // else{
    //     defaultCrossSet = Vertical_crossset[anchorRow+pos][anchorCol];
    // }

    if (board->hasaTile(anchorRow + (pos) * (cancelIndex), anchorCol + (pos) * (1 - cancelIndex)))
    {
        boardLetter = board->getTileAtPosition(anchorRow + (pos) * (cancelIndex), anchorCol + (pos) * (1 - cancelIndex));
        childNode = gaddagNode->findChildChar(boardLetter);
        if (childNode == NULL)
        {
            return;
        }
        goOn(pos, boardLetter, word, childNode);
    }
    else
    {
        childNode = gaddagNode->getFirstChild();
        while (childNode != NULL)
        {

            childLetter = childNode->getNodeLetter();
            if ((tilesCount[childLetter - CHAR_OFFSET] > 0) && (emptyBoard || (*currCrossSet)[anchorRow + (pos) * (cancelIndex)][anchorCol + (pos) * (1 - cancelIndex)].test(childLetter - CHAR_OFFSET)))
            {

                usedTiles++;                             // counting tiles used.
                tilesCount[childLetter - CHAR_OFFSET]--; // meaning that a letter has been taken into consideration dont repeat it.
                goOn(pos, childLetter, word, childNode);
                tilesCount[childLetter - CHAR_OFFSET]++; // Make it re-usable again.
                usedTiles--;
            }

            childNode = childNode->getNextChild();
        }

        if (tilesCount[BLANK - CHAR_OFFSET] > 0)
        { // consider all chars if BLANK tile.

            childNode = gaddagNode->getFirstChild();
            while (childNode != NULL)
            {

                childLetter = childNode->getNodeLetter();
                if ((childLetter != GADDAG_DELIMITER) && (emptyBoard || (*currCrossSet)[anchorRow + (pos) * (cancelIndex)][anchorCol + (pos) * (1 - cancelIndex)].test(childLetter - CHAR_OFFSET)))
                {

                    usedTiles++;                            // counting tiles used.
                    tilesCount[BLANK - CHAR_OFFSET]--;      // meaning that a letter has been taken into consideration dont repeat it.
                    childLetter = childLetter - BLANK_CHAR; // to mark this letter as a BLANK USED.
                    goOn(pos, childLetter, word, childNode);
                    tilesCount[BLANK - CHAR_OFFSET]++; // Make it re-usable again.
                    usedTiles--;                       // counting tiles used.
                }

                childNode = childNode->getNextChild();
            }
        }
    }
}

//This Function it sets the Options needed for transforming from Horiz. to vertical and vice versa.
void WordGenerate::setDirectionOptions(int row, int col, bool isHorizontal)
{
    if (isHorizontal)
    {
        maxBorder = MAX_BOARD_COLS;
        currDirection = col;
        cancelIndex = 0;
        colOffset = 1;
        rowOffset = 0;
        currCrossSet = &Vertical_crossset; //VerticalCrossSet;// dummy pass to it Vericrossset[row][col] .
    }
    else
    {
        maxBorder = MAX_BOARD_ROWS;
        currDirection = row;
        cancelIndex = 1;
        colOffset = 0;
        rowOffset = 1;
        currCrossSet = &Horiz_crossset; //HorizCrossSet;// dummy pass to it Horizcrossset[row][col] .
    }
}

//This Function GO ON funtion first function in Move Generation Algo.
void WordGenerate::goOn(int pos, char boardLetter, string word, Node *gaddagNode)
{
    //TODO: Complete The Algo. + Add any Helping Functions that may be Needed During Implementation.
    //cout<<"HI GADDAD"<<endl;
    if (pos <= 0)
    {
        bool roomLeft = true;
        bool boardEdge = false;
        bool directlyLeft = false;
        //al ahly

        if (board->hasaTile(anchorRow + pos * (cancelIndex), anchorCol + pos * (1 - cancelIndex)))
        {
            boardLetter -= ON_BOARD_CHAR;
        }
        word = boardLetter + word;

        if (((anchorCol + pos) * (1 - cancelIndex) + (anchorRow + pos) * (cancelIndex)) <= 0)
        {
            boardEdge = true;
        } // board edge reached whehter from above or left.
        else
        {

            //
            if (!board->hasaTile(anchorRow + pos * (cancelIndex), anchorCol + pos * (1 - cancelIndex)) && board->hasaTile(anchorRow + (pos - 1) * (cancelIndex), anchorCol + (pos - 1) * (1 - cancelIndex)))
            { // does it have a letter left (above) to this square
                roomLeft = false;
            }

            if (board->hasaTile(anchorRow + (pos - 1) * (cancelIndex), anchorCol + (pos - 1) * (1 - cancelIndex)))
            { // does it have a letter left (above) to this square
                directlyLeft = true;
            }
        }

        // Move Score Calculations and adding to move list:
        if (gaddagNode->isEndOfWord() && usedTiles != 0 && (emptyBoard || roomLeft)) // a move is FOUND if : end of a word is found (in GADDAG) and atleast a tile was used and.
        {
            // create,calculate and add a new move in MOVE LIST.
            // using the class or struct(for now).
            bool bingoMove = false;

            Move *newMove = new Move();
            newMove->word = word;
            newMove->horizontal = (cancelIndex == 0 ? true : false);
            newMove->startPosition.ROW = anchorRow + (pos) * (cancelIndex);
            newMove->startPosition.COL = anchorCol + (pos) * (1 - cancelIndex);

            if (usedTiles == 7)
            { // BINGO
                bingoMove = true;
            }

            //CALCULATE SCORE:
            //--HERE
            //int score = 22;
            newMove->moveUsedTiles = usedTiles;
            newMove->moveScore = board->calculateScore(newMove->word, newMove->startPosition.ROW, newMove->startPosition.COL, newMove->horizontal) + (char)(bingoMove)*50; // extra 10 points for now
            // ! newMove->moveScore = this->EvalCalculator->equity(Rack, bagSize, isEmptyBoard, bagSizeGreaterThanZero, newMove);
            moves.push_back(*newMove);
        }

        // Can I Go Left Furthur ??? : ANS:
        if (!boardEdge && (emptyBoard || (roomLeft && pos != -countRoomLeft)))
        {
            gen(pos - 1, word, gaddagNode);
        }
        // Setup Going Right Direction (Switch)

        bool rightBoardEdge = false;
        if (anchorRow + rowOffset >= maxBorder || anchorCol + colOffset >= maxBorder)
        {
            rightBoardEdge = true;
        } // board edge reached whehter from above or left.

        if (!rightBoardEdge && (emptyBoard || !directlyLeft))
        {
            // RIGHT:
            Node *delimeterNode = gaddagNode->findChildChar(GADDAG_DELIMITER); // search for the delimeter as on "newArc" to switch direction and  go right (SUFFIX).
            if (delimeterNode != NULL)
            {
                gen(1, word, delimeterNode);
            }
        }
    }
    else if (pos > 0)
    { // Go

        // RIGHT:

        bool roomRight = true;
        bool rightboardEdge = false;
        //al ahly

        if (board->hasaTile(anchorRow + pos * (cancelIndex), anchorCol + pos * (1 - cancelIndex)))
        {
            boardLetter -= ON_BOARD_CHAR;
        }

        word = word + boardLetter;

        if ((anchorCol + pos) * (1 - cancelIndex) + (anchorRow + pos) * (cancelIndex) == maxBorder - 1)
        {
            rightboardEdge = true;
        } // board edge reached whehter from above or left.
        else
        {

            //
            if (board->hasaTile(anchorRow + (pos + 1) * (cancelIndex), anchorCol + (pos + 1) * (1 - cancelIndex)))
            { // does it have a letter left (above) to this square
                roomRight = false;
            }
        }

        // Move Score Calculations and adding to move list:
        if (gaddagNode->isEndOfWord() && usedTiles != 0 && (emptyBoard || roomRight)) // a move is FOUND if : end of a word is found (in GADDAG) and atleast a tile was used and.
        {
            // create,calculate and add a new move in MOVE LIST.
            // using the class or struct(for now).
            bool bingoMove = false;

            Move *newMove = new Move();
            newMove->word = word;
            newMove->horizontal = (cancelIndex == 0 ? true : false);
            newMove->startPosition.ROW = anchorRow + pos * (cancelIndex) + (1 - word.length()) * (cancelIndex);
            newMove->startPosition.COL = anchorCol + pos * (1 - cancelIndex) + (1 - word.length()) * (1 - cancelIndex);

            if (usedTiles == 7)
            { // BINGO
                bingoMove = true;
            }

            //CALCULATE SCORE: PUT SCORE FUNCTION HERE.
            //--HERE
            //int score = 22;
            newMove->moveUsedTiles = usedTiles;
            //
            newMove->moveScore = board->calculateScore(newMove->word, newMove->startPosition.ROW, newMove->startPosition.COL, newMove->horizontal) + (char)(bingoMove)*50; // extra 10 points for now only.
            //newMove->moveScore = this->EvalCalculator->equity(Rack, bagSize, isEmptyBoard, bagSizeGreaterThanZero, newMove);
            moves.push_back(*newMove);
        }
        // Can I Go Left Furthur ??? : ANS:
        if (!rightboardEdge)
        {
            gen(pos + 1, word, gaddagNode);
        }
    }
} // Gordon GO ON funtion first function in Move Generation Algo.

/* This Function calculates the no. of tiles for each character in Rack.
    PLEASE READ CAREFULLY:
        -> Pass what ever RACK you need to generate possible moves using it.
        -> Dont Worry this Function Acts Like a SET Methode for RACK.
*/
void WordGenerate::countTilesRack(vector<char> *rackTiles)
{
    // TODO: USE rackTiles instead later.
    vector<char> *rack = rackTiles;
    Rack = rackTiles;
    if (rack == NULL)
    {
        *rack = board->getTiles();
    }

    for (int index = 0; index <= 29; ++index)
    {
        tilesCount[index] = 0;
    }

    for (int index = 0; index < rack->size(); ++index)
    {
        tilesCount[(*rack)[index] - CHAR_OFFSET]++;
    }
}

//This Function calculate the crosssets of each square.
void WordGenerate::crosssets()
{
    char letter = '.';
    //Horiz_crossset = 0;

    for (int row = 0; row < MAX_BOARD_ROWS; row++)
    {
        for (int col = 0; col < MAX_BOARD_COLS; col++)
        {
            Horiz_crossset[row][col].reset();
            Vertical_crossset[row][col].reset();
            cout << row << ":" << col << endl;
            if (!board->hasaTile(row, col) && (col != 14) && (board->hasaTile(row, col + 1)) && (col == 0 || !board->hasaTile(row, col - 1)))
            {

                int move_col = col + 1;
                while (move_col < MAX_BOARD_COLS && board->hasaTile(row, move_col++))
                {
                    ;
                }
                if (MAX_BOARD_COLS == move_col && board->hasaTile(row, move_col - 1))
                {
                    move_col++;
                }
                move_col -= 2;
                Node *nod = NULL;
                nod = this->root;
                for (int i = 0; i < move_col - col; i++)
                {
                    letter = board->getTileAtPosition(row, move_col - i);
                    nod = nod->findChildChar(letter);
                }
                nod = nod->getFirstChild();
                while (nod != 0)
                {
                    if (nod->getNodeLetter() != GADDAG_DELIMITER && nod->isEndOfWord())
                    {
                        Horiz_crossset[row][col].set(nod->getNodeLetter() - CHAR_OFFSET);
                    }
                    nod = nod->getNextChild();
                }
            }

            else if (!board->hasaTile(row, col) && (col == 14 || !board->hasaTile(row, col + 1)) && (col != 0) && (board->hasaTile(row, col - 1)))
            {

                int move_col = col - 1;
                int ptr = 0;

                while (move_col >= 0 && board->hasaTile(row, move_col--))
                {
                    ;
                }
                if (move_col == -1 && board->hasaTile(row, move_col + 1))
                {
                    move_col--;
                }
                move_col += 2;
                Node *nod = NULL;
                nod = this->root;
                if (col == 3 && row == 2)
                {
                    cout << "BELAL" << endl;
                }
                for (int itr = 0; itr <= col - move_col; itr++)
                {
                    if (itr == 1)
                    {
                        if (col == 3 && row == 2)
                        {
                            cout << "lloop BELAL 1" << endl;
                        }
                        nod = nod->findChildChar(GADDAG_DELIMITER);
                        if (col == 3 && row == 2)
                        {
                            cout << "lloop BELAL 2" << endl;
                        }
                    }
                    else
                    {
                        if (col == 3 && row == 2)
                        {
                            cout << "lloop BELAL 3" << endl;
                        }
                        letter = board->getTileAtPosition(row, move_col + ptr);
                        ptr++;
                        nod = nod->findChildChar(letter);
                        if (col == 3 && row == 2)
                        {
                            cout << "lloop BELAL 4" << endl;
                        }
                    }
                }
                if (col == 3 && row == 2)
                {
                    cout << "BELAL" << endl;
                }
                nod = nod->getFirstChild();
                if (col == 3 && row == 2)
                {
                    cout << "BELAL" << endl;
                }
                while (nod != 0)
                {
                    if (nod->getNodeLetter() != GADDAG_DELIMITER && nod->isEndOfWord())
                    {
                        Horiz_crossset[row][col].set(nod->getNodeLetter() - CHAR_OFFSET);
                    }
                    nod = nod->getNextChild();
                }
                if (col == 3 && row == 2)
                {
                    cout << "BELAL" << endl;
                }

                /**kh//kh*/
            }

            else if (!board->hasaTile(row, col) && (col == 0 || board->hasaTile(row, col - 1)) && (col == 14 || board->hasaTile(row, col + 1)))
            {

                int R_move_col = col + 1;
                while (R_move_col < MAX_BOARD_COLS && board->hasaTile(row, R_move_col++))
                {
                    ;
                }
                if (MAX_BOARD_COLS == R_move_col && board->hasaTile(row, R_move_col - 1))
                {
                    R_move_col++;
                }
                R_move_col -= 2;
                Node *nod = NULL, *child = NULL;
                nod = this->root;
                for (int i = 0; i < R_move_col - col; i++)
                {
                    letter = board->getTileAtPosition(row, R_move_col - i);
                    nod = nod->findChildChar(letter);
                }
                child = nod->getFirstChild();
                nod = child;
                char joinLetter = '.';

                while (child != 0)
                {
                    joinLetter = nod->getNodeLetter();
                    if (joinLetter != GADDAG_DELIMITER)
                    {

                        int itr = 1;
                        bool succeed = true;
                        while ((col - itr) >= 0 && board->hasaTile(row, col - itr))
                        {
                            letter = board->getTileAtPosition(row, col - itr);
                            nod = nod->findChildChar(letter);
                            if (nod == 0)
                            {
                                succeed = false;
                                break;
                            }
                            itr++;
                        }

                        if (succeed && nod->isEndOfWord())
                        {
                            Horiz_crossset[row][col].set(joinLetter - CHAR_OFFSET);
                        }
                    }

                    child = child->getNextChild();
                    nod = child;
                }
            }
            else
            {
                Horiz_crossset[row][col].set();
            }

            // //////// Vertical
            if (!board->hasaTile(row, col) && (row != 14) && (board->hasaTile(row + 1, col)) && (row == 0 || !board->hasaTile(row - 1, col)))
            {

                int move_row = row + 1;
                while (move_row < MAX_BOARD_ROWS && board->hasaTile(move_row++, col))
                {
                };
                if (move_row == MAX_BOARD_ROWS && board->hasaTile(move_row - 1, col))
                {
                    move_row++;
                }
                move_row -= 2;
                Node *nod = NULL;
                nod = this->root;
                for (int i = 0; i < move_row - row; i++)
                {
                    letter = board->getTileAtPosition(move_row - i, col);
                    nod = nod->findChildChar(letter);
                }
                nod = nod->getFirstChild();
                while (nod != 0)
                {

                    if (nod->getNodeLetter() != GADDAG_DELIMITER && nod->isEndOfWord())
                    {
                        Vertical_crossset[row][col].set(nod->getNodeLetter() - CHAR_OFFSET);
                    }
                    nod = nod->getNextChild();
                }
            }

            else if (!board->hasaTile(row, col) && (row == 14 || !board->hasaTile(row + 1, col)) && (row != 0) && (board->hasaTile(row - 1, col)))
            {

                int move_row = row - 1;
                move_row = row - 1;
                int ptr = 0;
                while (move_row >= 0 && board->hasaTile(move_row--, col))
                {
                    ;
                }
                if (move_row == -1 && board->hasaTile(move_row + 1, col))
                {
                    move_row--;
                }
                if (col == 3 && row == 2)
                {
                    cout << "BELALVert" << endl;
                }
                move_row += 2;
                Node *nod = this->root;
                if (col == 3 && row == 2)
                {
                    cout << "BELALVert 2" << endl;
                }
                for (int itr = 0; itr <= row - move_row; itr++)
                {
                    if (itr == 1)
                    {
                        nod = nod->findChildChar(GADDAG_DELIMITER);
                        if (col == 3 && row == 2)
                        {
                            cout << "BELALVert *" << endl;
                        }
                    }
                    else
                    {
                        letter = board->getTileAtPosition(move_row + ptr, col);
                        ptr++;
                        nod = nod->findChildChar(letter);
                    }
                }

                nod = nod->getFirstChild();
                if (col == 3 && row == 2)
                {
                    cout << "BELALVert 3" << endl;
                }
                while (nod != 0)
                {
                    if (nod->getNodeLetter() != GADDAG_DELIMITER && nod->isEndOfWord())
                    {
                        Vertical_crossset[row][col].set(nod->getNodeLetter() - CHAR_OFFSET);
                    }
                    nod = nod->getNextChild();
                }
                if (col == 3 && row == 2)
                {
                    cout << "BELALVert 1" << endl;
                }
            }

            else if (!board->hasaTile(row, col) && (row == 14 || board->hasaTile(row + 1, col)) && (row == 0 || board->hasaTile(row - 1, col)))
            {
                int move_row = row + 1;
                while (move_row < MAX_BOARD_ROWS && board->hasaTile(move_row++, col))
                {
                };
                if (MAX_BOARD_ROWS == move_row && board->hasaTile(move_row - 1, col))
                {
                    move_row++;
                }

                move_row -= 2;
                Node *nod = NULL, *child = NULL;
                nod = root;
                for (int i = 0; i < move_row - row; i++)
                {
                    letter = board->getTileAtPosition(move_row - i, col);
                    nod = nod->findChildChar(letter);
                }
                child = nod->getFirstChild();
                nod = child;
                char joinLetter = '.';

                while (child != 0)
                {
                    joinLetter = nod->getNodeLetter();
                    if (joinLetter != GADDAG_DELIMITER)
                    {
                        int itr = 1;
                        bool succeed = true;
                        while ((row - itr >= 0) && board->hasaTile(row - itr, col))
                        {
                            letter = board->getTileAtPosition(row - itr, col);
                            nod = nod->findChildChar(letter);
                            if (nod == 0)
                            {
                                succeed = false;
                                break;
                            }
                            itr++;
                        }

                        if (succeed && nod->isEndOfWord())
                        {
                            Vertical_crossset[row][col].set(joinLetter - CHAR_OFFSET);
                        }
                    }
                    child = child->getNextChild();
                    nod = child;
                }
            }
            else
            {
                Vertical_crossset[row][col].set();
            }
        }
    }
}

void WordGenerate::setBoardState(BoardToGrammer *board)
{
    if (this->board != board)
    {
        boardChanged = true;
    }
    else
    {
        boardChanged = false;
    }
    this->board = board;
}
// TODO: Assigns Different Board States For Monte Carlo.

list<Move> WordGenerate::allMoves()
{
    return moves;
} // TODO:Returns all moves.

void WordGenerate::emptyBoardMoves()
{
    if (!emptyBoard && false)
    { // for now.

        string word = "";
        // Middle Square in Board To Start generation of words at:
        setDirectionOptions(7, 7, true); // true -> horizontal.
        //currCrossSet.reset();
        anchorRow = 7;
        anchorCol = 7;
        emptyBoard = true;

        gen(0, word, this->root);

        setDirectionOptions(7, 7, false); // false -> vertical.
        //currCrossSet.reset();

        word = "";
        gen(0, word, this->root);

        emptyBoard = false;
    }
    else
    {
        string word = "";
        nonRepeatedMoves.clear();
        generateEmpty(this->root, word);

        // Now Repeat Words According to thier lengths ...

        std::list<string>::iterator end = nonRepeatedMoves.end();
        for (std::list<string>::iterator it = nonRepeatedMoves.begin(); it != end; ++it)
        {
            for (unsigned int k = 0; k < (*it).length(); ++k)
            {
                Move move;
                move.word = (*it);
                move.moveUsedTiles = (*it).length();
                move.horizontal = true;
                move.startPosition.ROW = 7;
                move.startPosition.COL = 7 - ((*it).length()) + 1 + k;

                if (move.startPosition.COL < 0)
                {
                    continue;
                }
                bool bingoMove = false;
                if (usedTiles == 7)
                { // BINGO
                    bingoMove = true;
                }

                move.moveScore = board->calculateScore(move.word, move.startPosition.ROW, move.startPosition.COL, move.horizontal) + (char)(bingoMove)*50;
                //newMove->moveScore = this->EvalCalculator->equity(Rack, bagSize, isEmptyBoard, bagSizeGreaterThanZero, newMove);
                moves.push_back(move);
            }
        }

        cout << "MOVES : " << moves.size() << endl;
    }
} //TODO: Generate all possible moves availabe given certain Rack when the status of the board is empty only.

void WordGenerate::generateEmpty(Node *node, string word)
{
    for (Node *child = node->getFirstChild(); child != NULL; child = child->getNextChild())
    {
        char childLetter = child->getNodeLetter();

        if (childLetter == GADDAG_DELIMITER || tilesCount[childLetter - CHAR_OFFSET] <= 0)
        {
            continue;
        }

        tilesCount[childLetter - CHAR_OFFSET]--;

        string newPrefix;
        newPrefix += childLetter;
        newPrefix += word;

        if (child->isEndOfWord())
        {
            nonRepeatedMoves.push_back(newPrefix);
        }

        // if (childLetter == 'c' && word == "")
        // {

        // }
        if (child->getFirstChild())
        {
            generateEmpty(child, newPrefix);
        }

        tilesCount[childLetter - CHAR_OFFSET]++;
    }
    if (tilesCount[BLANK - CHAR_OFFSET] >= 1)
    {
        for (Node *child = node->getFirstChild(); child != NULL; child = child->getNextChild())
        {
            char childLetter = child->getNodeLetter();

            if (childLetter == GADDAG_DELIMITER)
            {
                continue;
            }

            tilesCount[BLANK - CHAR_OFFSET]--;

            string newPrefix;
            newPrefix += (childLetter - BLANK_CHAR);
            newPrefix += word;

            if (child->isEndOfWord())
            {

                nonRepeatedMoves.push_back(newPrefix);
            }

            if (child->getFirstChild())
            {
                generateEmpty(child, newPrefix);
            }

            tilesCount[BLANK - CHAR_OFFSET]++;
        }
    }
}

void WordGenerate::duplicateMovesRemoval()
{
    // ! FOR THE EVALUATION TO WORK AT ITS BEST.

} // TODO: removes duplicate moves occuring from a one tile play. (vertically + Horizonatally).

bool WordGenerate::checkWordDict(string word)
{
    // HERE:
    Node *nodePtr = root;
    for (int index = word.size() - 1; index >= 0; --index)
    {

        nodePtr = nodePtr->findChildChar(word[index]);
        if (nodePtr == NULL)
        {
            return false;
        }
    }
    return nodePtr->isEndOfWord();
} // TODO: Given a Word it checks Whether This word in Dict or NOT.
Move *WordGenerate::bestScoreMove()
{
    return new Move(); // DUMMMYYYY.
} // TODO: Returns Best (Highest Score) Move From The Last Generated Moves RUN.

// TEST FUNCTION ONLY.
void WordGenerate::printCrossSet()
{
    for (int row = 0; row < MAX_BOARD_ROWS; row++)
    {
        for (int col = 0; col < MAX_BOARD_COLS; col++)
        {
            if (!Horiz_crossset[row][col].all())
            {
                cout << endl
                     << "Horizontal Cross Set [" + to_string(row) + "]" + "[" + to_string(col) + "] : " << Horiz_crossset[row][col] << endl;
            }

            if (!Vertical_crossset[row][col].all())
            {
                cout << endl
                     << "Vertical Cross Set [" + to_string(row) + "]" + "[" + to_string(col) + "] : " << Vertical_crossset[row][col] << endl;
            }
        }
    }
}

// Updates CrossSets of The Board When a Move is Played. Given This 'Move' The Function Uses Move Specific Information And Updates .
void WordGenerate::updateCrossSet(Move *move)
{
    vector<Position> boardIndex;

    Position boardPos;
    char moveType = move->horizontal ? 1 : 0;
    // Row and Col Changes according to the play type : row,endcol or endrow,col:
    int moveRow = move->startPosition.ROW + (move->word.length() - 1) * (1 - moveType);
    int moveCol = move->startPosition.COL + (move->word.length() - 1) * (moveType);

    if (moveRow > 0)
    { // Right and Left of a MOVE (Above or Below incase of Vertical Move)
        boardPos.ROW = move->startPosition.ROW - (1) * (1 - moveType);
        boardPos.COL = move->startPosition.COL - (1) * (moveType);
        boardIndex.push_back(boardPos);
    }

    // TODO: Complete ..

    // if (moveCol < MAX_BOARD_COLS) {

    //     boardPos.ROW = move->startPosition.ROW - (1) * (1 - moveType);
    //     boardPos.COL = move->startPosition.COL - (1) * (moveType);
    // 	boardIndex.push_back(boardPos);
    // 	hrows.push_back(row);
    // 	hcols.push_back(endcol + 1);
    // }
}

// please provide NULL inCase of a First Move ("PLAY") otherwise Provide the PLAYED or Suggested Move inorder To Update.
void WordGenerate::crosssetsManager(Move *move)
{
    if (boardChanged)
    {
        this->crosssets();
        boardChanged = false;
    }
    else
    {
        this->updateCrossSet(move); // ! IN PROGRESS ...
    }
} // Whether To Update or Generate New Crosssets.

void WordGenerate::setEvaluator(/*Evaluator *EvalCalculator*/)
{
    //this->EvalCalculator = EvalCalculator;
}