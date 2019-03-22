
//TODO: Completion of Move Generation Algorithm.
#include "MoveGenerate.h"
#include "LoadGaddag.h"
#include "Gaddag.h"


using namespace std;

// dummylist:
// a particular sqaure. 
#define HorizCrossSet 1; // each will be replaced by the coreponding sqaure crossset 
#define VerticalCrossSet 0;
#define BLANK ' '

//This Function it takes a Reference to the Board.
WordGenerate::WordGenerate(BoardToGrammer&board){
    this->board=&board; // catching a boardcomm. verison object.
}


/*
This Function iterates on each sqaure in the board and performing the algo. Taking the board 2-Dimensions into Consideration.
and it iterates on each sqaure in the board and performing the algo.
*/
void WordGenerate::generateWords(){

    bool isAnchorSquare = false;
    int countRoomLeft = 0;
    string word;

    countTilesRack();
    for(int indexRow = 0; indexRow < MAX_BOARD_ROWS ; ++indexRow){
        for(int indexCol = 0; indexCol < MAX_BOARD_COLS ; ++indexCol){
            word = "";

            //Horizonatal Move Generation:
            setDirectionOptions(indexRow,indexCol,true); // true -> horizontal.
            isAnchorSquare = isAnchor(indexRow,indexCol); 
            if(isAnchorSquare){
                countRoomLeft = roomLeftCount(indexRow,indexCol);
                anchorRow = indexRow ;
                anchorCol = indexCol ;
                gen(0,word,this->root);
            }

            word = "";
            //Vertical Move Generation:
            setDirectionOptions(indexRow,indexCol,false); // false -> vertical.
            isAnchorSquare = isAnchor(indexRow,indexCol);
            if(isAnchorSquare){
                countRoomLeft = roomLeftCount(indexRow,indexCol);
                anchorRow = indexRow ;
                anchorCol = indexCol ;
                gen(0,word,this->root);
            }
        }
    }
} 


//This Function is this square given row and col an anchor sqaure.
bool WordGenerate::isAnchor(int row,int col){
     // NOTE: GADDAG algo. works from the left to right. it can be reversed but also need reverse of the structure itself DAGGAD.

  // what is an anchor square:
    /*
       1- if it has a letter on the square and its right sqaure doesn't.
        this means that "log" anchor's is 'g'. beacuse no need of 'o' or 'l' as anchors giving same repeated results.
       2- if it doesnot have a letter but it should at least have an opposite cross set to its current direction.
        this means that if a vertical word directly above a square i can attach a word to this square but hoirz.
     
    */

  if(board->hasaTile(row,col) && (currDirection == maxBorder - 1 || !board->hasaTile(row+rowOffset,col+colOffset))){
    
      return true;
  } // when there is a char.

  if(!board->hasaTile(row,col) && currCrossSet.any()){
    
    if( (currDirection != 0 && !board->hasaTile(row-rowOffset,col-colOffset)) || ((currDirection !=  maxBorder - 1) && !board->hasaTile(row+rowOffset,col+colOffset)))
    {
        return true;
    }
  } // when no char. on this square.

    return false;
 }// is this square given row and col an anchor sqaure? Offsets used to make the function works in 2D (vert./horiz.)



//This Function it's important to stop right before a letter found while travesring the board leftward generating possible moves.
int WordGenerate::roomLeftCount(int row,int col){
    
    // count include the first char (itself).
    for(int offsetLeft = currDirection; offsetLeft >=0; --offsetLeft){
        if(board->hasaTile(row+cancelIndex*offsetLeft,col+(1-cancelIndex)*offsetLeft)){
            countRoomLeft++;
        }
    }

    for(int offsetLeft = currDirection - countRoomLeft - 1; offsetLeft >=0; --offsetLeft){
          if(!currCrossSet.any() && !board->hasaTile(row+cancelIndex*(offsetLeft),col+(1-cancelIndex)*(offsetLeft))){
                if(offsetLeft == 0){ countRoomLeft++;}
                else{
                    if(!board->hasaTile(row+cancelIndex*(offsetLeft-1),col+(1-cancelIndex)*(offsetLeft - 1))){
                        countRoomLeft++;
                    }
                }
          }
          else{

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
}


//This Gen funtion first function in Move Generation Algo.
void WordGenerate::gen(int pos,string &word,Node*gaddagNode){

    char childLetter; // init.
    char boardLetter;
    Node*childNode;

    if(board->hasaTile(anchorRow,anchorCol)){
        boardLetter = board->getTileAtPosition(anchorRow,anchorCol);
        childNode = gaddagNode->findChildChar(boardLetter);
        goOn(pos,boardLetter,word,childNode);
    }
    else{
        childNode = gaddagNode->getFirstChild();
        while(childNode != NULL){

            childLetter = childNode->getNodeLetter();
			if ((tilesCount[childLetter - CHAR_OFFSET] > 0) && currCrossSet.test(childLetter-CHAR_OFFSET)) {
                
                tilesCount[childLetter - CHAR_OFFSET]--; // meaning that a letter has been taken into consideration dont repeat it.
                goOn(pos, childLetter, word, childNode);
                tilesCount[childLetter - CHAR_OFFSET]++; // Make it re-usable again.

			}

            childNode = childNode->getNextChild();
        }

        if(tilesCount[BLANK - CHAR_OFFSET] > 0){ // consider all chars if BLANK tile.

            childNode = gaddagNode->getFirstChild();
            while(childNode != NULL){

                childLetter = childNode->getNodeLetter();
			    if (((childLetter-CHAR_OFFSET) != COMPRESSED_GADDAG_DELIMITER) && currCrossSet.test(childLetter-CHAR_OFFSET)) {
                
                    tilesCount[BLANK - CHAR_OFFSET]--; // meaning that a letter has been taken into consideration dont repeat it.
                    goOn(pos, childLetter, word, childNode);
                    tilesCount[BLANK - CHAR_OFFSET]++; // Make it re-usable again.

			    }

                childNode = childNode->getNextChild();
            }
        }
    }

} 


//This Function it sets the Options needed for transforming from Horiz. to vertical and vice versa.
void WordGenerate::setDirectionOptions(int row,int col ,bool isHorizontal){

    if(isHorizontal){
      maxBorder =  MAX_BOARD_COLS;
      currDirection = col;
      cancelIndex = 0;
      colOffset = 1;
      rowOffset = 0;
      currCrossSet = VerticalCrossSet;// dummy pass to it Vericrossset[row][col] .
  }else {
      maxBorder = MAX_BOARD_ROWS;
      currDirection = row;
      cancelIndex = 1;
      colOffset = 0;
      rowOffset = 1;
      currCrossSet = HorizCrossSet;// dummy pass to it Horizcrossset[row][col] .
  }
}

//This Function GO ON funtion first function in Move Generation Algo.
void WordGenerate::goOn(int pos,char boardLetter,string&word,Node*gaddagNode){
    //TODO: Complete The Algo. + Add any Helping Functions that may be Needed During Implementation.
    cout<<"HI GADDAD<<endl";
} 


// This Function calculates the no. of tiles for each character in Rack.
void WordGenerate::countTilesRack(){
	
    vector<char> rack = board->getTiles();

     for(int index = 0 ; index<=29; ++index){
        tilesCount[index] = 0;
    }

    for(int index = 0 ; index<rack.size(); ++index){
        tilesCount[rack[index] - CHAR_OFFSET]++;
    }

} 


//This Function calculate the crosssets of each square.
void WordGenerate::crosssets()
{
	char letter;
	for(int row=0;row<MAX_BOARD_ROWS;row++)
	{
		for(int col=0;col<MAX_BOARD_COLS;col++)
		{
			if(!board->hasaTile(row,col) && (col==14 || board->hasaTile(row,col+1)) && (col==0 || !board->hasaTile(row,col-1)))
			{
				
				int move_col=col+1;
				while(board->hasaTile(row,move_col++)){};
				move_col-=2;
				Node* nod;
				nod=root;
				for(int i=0;i<move_col-col;i++)
				{
					letter=board->getTileAtPosition(row,move_col-i);
					nod=nod->findChildChar(letter);
				}
				nod=nod->getFirstChild();
				while(nod!=0)
				{	
					if(nod->isEndOfWord)
					{
						Horiz_crossset[row][col].set(nod->getNodeLetter()-CHAR_OFFSET);
					}
					nod=nod->getNextChild();
				}
				
					
			}
			
			else if(!board->hasaTile(row,col) && (col==14 || !board->hasaTile(row,col+1)) && (col==0 || board->hasaTile(row,col-1)))
			{
				
				int move_col=col-1;
				int ptr=0;
				while(board->hasaTile(row,move_col--));
				move_col+=2;
				Node* nod;
				nod=root;
				for(int itr=0;itr<=move_col-col;itr++)
				{
					if(itr==1)
					{
						nod=nod->findChildChar('^');
						itr--;
					}
					else
					{
						letter=board->getTileAtPosition(row,move_col+ptr);
						ptr++;
						nod=nod->findChildChar(letter);
					}
				}
				nod=nod->getFirstChild();
				while(nod!=0)
				{	
					if(nod->isEndOfWord)
					{
						Horiz_crossset[row][col].set(nod->getNodeLetter()-CHAR_OFFSET);
					}
					nod=nod->getNextChild();
				}
				
					
			}
			
			else if(!board->hasaTile(row,col))
					if(board->hasaTile(row,col+1) && board->hasaTile(row,col-1))
					{
					int R_move_col=col+1;
					while(board->hasaTile(row,R_move_col++));
					R_move_col-=2;
					Node* nod,*child;
					nod=root;
					for(int i=0;i<R_move_col-col;i++)
					{
						letter=board->getTileAtPosition(row,R_move_col-i);
						nod=nod->findChildChar(letter);
					}
					child=nod->getFirstChild();
					nod=child;
	
					while(*child!=0)
					{	
						int itr=1;
						bool succeed=true;
						while(board->hasaTile(row,col-itr))
						{
							letter=board->getTileAtPosition(row,col-itr);
							nod=nod->findChildChar(letter);
							if(nod==0)
							{
								succeed=false;
								break;
							}
							itr++;
						}	
					
						if(succeed)
							Horiz_crossset[row][col].set(nod->getNodeLetter()-CHAR_OFFSET);
						child=child->getNextChild();
					
					}
				
					
					}
			
			
			
			//////// Vertical
			if(!board->hasaTile(row,col) && (row==14 || board->hasaTile(row+1,col)) && (row==0 || !board->hasaTile(row-1,col)))
			{
				
				int move_row=row+1;
				while(board->hasaTile(move_row++,col));
				move_row-=2;
				Node* nod;
				nod=root;
				for(int i=0;i<move_row-row;i++)
				{
					letter=board->getTileAtPosition(move_row-i,col);
					nod=nod->findChildChar(letter);
				}
				nod=nod->getFirstChild();
				if(nod!=0){
					do
					{	
						if(nod->isEndOfWord)
						{
							Vertical_crossset[row][col].set(nod->getNodeLetter()-CHAR_OFFSET);
						}
						nod=nod->getNextChild();
					}while(nod!=0);
				}
					
			}
			
			else if(!board->hasaTile(row,col) && (row==14 || !board->hasaTile(row+1,col)) && (row==0 || board->hasaTile(row-1,col)))
			{
				
				int move_row=row-1;
				int ptr=0;
				while(board->hasaTile(move_row--,col));
				move_row+=2;
				Node* nod;
				nod=root;
				for(int itr=0;itr<=move_row-row;itr++)
				{
					if(itr==1)
					{
						nod=nod->findChildChar('^');
						itr--;
					}
					else
					{
						letter=board->getTileAtPosition(move_row+ptr,col);
						ptr++;
						nod=nod->findChildChar(letter);
					}
				}
				nod=nod->getFirstChild();
				if(nod!=0){
					do
					{	
						if(nod->isEndOfWord)
						{
							Vertical_crossset[row][col].set(nod->getNodeLetter()-CHAR_OFFSET);
						}
						nod=nod->getNextChild();
					}while(nod!=0);
				}
					
			}
			
			else if(!board->hasaTile(row,col) && board->hasaTile(row+1,col) && board->hasaTile(row-1,col))
			{
				int move_row=row+1;
				while(board->hasaTile(move_row++,col));
				move_row-=2;
				Node* nod,*child;
				nod=root;
				for(int i=0;i<move_row-row;i++)
				{
					letter=board->getTileAtPosition(move_row-i,col);
					nod=nod->findChildChar(letter);
				}
				child=nod->getFirstChild();
				nod=child;
	
				while(*child!=0)
				{	
					int itr=1;
					bool succeed=true;
					while(board->hasaTile(row-itr,col))
					{
						letter=board->getTileAtPosition(row-itr,col);
						nod=nod->findChildChar(letter);
						if(nod==0)
						{
							succeed=false;
							break;
						}
						itr++;
					}
					
					if(succeed)
							Vertical_crossset[row][col].set(nod->getNodeLetter()-CHAR_OFFSET);
					child=child->getNextChild();
					
				}
				
					
			}
			
			
		}
	}
	
}
