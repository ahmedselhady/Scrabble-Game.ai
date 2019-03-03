#pragma once

#define ULL unsigned long long

class BoardMask
{
private:
	//ULL First_64, Second_64, Third_64, Fourth_64, MASK;

	ULL* Values_x64, MASK;

public:

	void setBit(int bitOffset);
	void unsetBit(int bitOffset);
	ULL getBit(int bitOffset);

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


	
	
	BoardMask(ULL = 0, ULL = 0, ULL = 0, ULL = 0);
	BoardMask(const BoardMask&);
	~BoardMask();
};

