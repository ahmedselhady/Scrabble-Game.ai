#include "MoveGenerate.h"


void MoveGenerate::crosssets()
{
	char letter;
	for(int row=0;row<15;row++)
	{
		for(int col=0;col<15;col++)
		{
			if(!board->hasaTile(row,col) && board->hasaTile(row,col+1) && !board->hasaTile(row,col-1))
			{
				
				int move_col=col+1;
				while(board->hasaTile(row,move_col++);
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
						Horiz_crossset[row][col]|=nod->getNodeLetter()-CHAR_OFFSET;
					}
					nod=nod->getNextChild();
				}
				
					
			}
			
			if(!board->hasaTile(row,col) && !board->hasaTile(row,col+1) && board->hasaTile(row,col-1))
			{
				
				int move_col=col-1;
				int ptr=0;
				while(board->hasaTile(row,move_col--);
				move_col+=2;
				Node* nod;
				nod=root;
				for(int itr=0;itr<=move_col-col;itr++)
				{
					if(itr==1)
					{
						nod=nod->findChildChar('^');
						i--;
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
						Horiz_crossset[row][col]|=nod->getNodeLetter()-CHAR_OFFSET;
					}
					nod=nod->getNextChild();
				}
				
					
			}
			
			if(!board->hasaTile(row,col) && board->hasaTile(row,col+1) && board->hasaTile(row,col-1))
			{
				int R_move_col=col+1;
				while(board->hasaTile(row,R_move_col++);
				R_move_col-=2;
				Node* nod,child;
				nod=root;
				for(int i=0;i<R_move_col-col;i++)
				{
					letter=board->getTileAtPosition(row,R_move_col-i);
					nod=nod->findChildChar(letter);
				}
				child=nod->getFirstChild();
				nod=child;
	
				while(child!=0)
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
						Horiz_crossset[row][col]|=child->getNodeLetter()-CHAR_OFFSET;
					child=child->getNextChild();
					
				}
				
					
			}
			
			
			
			//////// Vertical
			if(!board->hasaTile(row,col) && board->hasaTile(row+1,col) && !board->hasaTile(row-1,col))
			{
				
				int move_row=row+1;
				while(board->hasaTile(move_row++,col);
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
							Vertical_crossset[row][col]|=nod->getNodeLetter()-CHAR_OFFSET;
						}
						nod=nod->getNextChild();
					}while(nod!=0);
				}
					
			}
			
			if(!board->hasaTile(row,col) && !board->hasaTile(row+1,col) && board->hasaTile(row-1,col))
			{
				
				int move_row=row-1;
				int ptr=0;
				while(board->hasaTile(move_row--,col);
				move_row+=2;
				Node* nod;
				nod=root;
				for(int itr=0;itr<=move_row-row;itr++)
				{
					if(itr==1)
					{
						nod=nod->findChildChar('^');
						i--;
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
							Vertical_crossset[row][col]|=nod->getNodeLetter()-CHAR_OFFSET;
						}
						nod=nod->getNextChild();
					}while(nod!=0);
				}
					
			}
			
			if(!board->hasaTile(row,col) && board->hasaTile(row+1,col) && board->hasaTile(row-1,col))
			{
				int move_row=row+1;
				while(board->hasaTile(move_row++,col);
				move_row-=2;
				Node* nod,child;
				nod=root;
				for(int i=0;i<move_row-row;i++)
				{
					letter=board->getTileAtPosition(move_row-i,col);
					nod=nod->findChildChar(letter);
				}
				child=nod->getFirstChild();
				nod=child;
	
				while(child!=0)
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
						Vertical_crossset[row][col]|=child->getNodeLetter()-CHAR_OFFSET;
					child=child->getNextChild();
					
				}
				
					
			}
			
			
		}
	}
	
}
