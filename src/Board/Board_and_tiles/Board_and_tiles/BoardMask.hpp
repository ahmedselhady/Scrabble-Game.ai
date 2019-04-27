#pragma once

#define ULL unsigned long long

class BoardMask
{
private:
	//ULL First_64, Second_64, Third_64, Fourth_64, MASK;

	ULL* Values_x64, MASK;

public:
	bool isEmpty();// its name should be non empty 
	void setBit(int bitOffset);//sets bit whose bitOffset is given
	void unsetBit(int bitOffset);//unsets bit whose bitOffset is given
	bool getBit(int bitOffset);//gets bit whose bitOffset is given

	BoardMask operator &(const BoardMask& otherboard) const;
	BoardMask operator |(const BoardMask& otherboard) const;
	BoardMask operator ^(const BoardMask& otherboard) const;
	BoardMask& operator |=(const BoardMask& otherboard);
	BoardMask& operator &=(const BoardMask& otherboard);
	BoardMask& operator ^=(const BoardMask& otherboard);
	BoardMask& operator =(const BoardMask& otherboard);
	bool operator !=(const BoardMask& otherboard);
	bool operator ==(const BoardMask& otherboard);
	BoardMask& operator <<(int);
	BoardMask& operator >>(int);

	void print(); // for debug mode only
	
	
	BoardMask(ULL = 0, ULL = 0, ULL = 0, ULL = 0);
	BoardMask(const BoardMask&);
	~BoardMask();
};

	
