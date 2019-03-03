#include "BoardMask.h"


void BoardMask::setBit(int bitOffset) { // bitOffset Is Calculated using Equation provided by andrew
	// accessing certain bit efficiently!
	// TODO: find better implementation
	int offset = bitOffset / 64;
	Values_x64[offset] |= (MASK << (bitOffset - (64 * (offset))));
	/*if (bitOffset < 64) {
		this->First_64 |= (MASK <<bitOffset);
	}
	else  if (bitOffset < 128) {
		this->Second_64 |= (MASK << (bitOffset-64));
	}
	else if(bitOffset <192){
		this->Third_64 |= (MASK << (bitOffset - 128));
	}
	else {
		this->Fourth_64 |= (MASK << (bitOffset - 192));
	}*/
 }

void BoardMask::unsetBit(int bitOffset) { // bitOffset Is Calculated using Equation provided by andrew
	int offset = bitOffset / 64;
	Values_x64[offset] ^= (MASK << (bitOffset - (64 * (offset))));
	/*if (bitOffset < 64) {
		this->First_64 |= (MASK << bitOffset);
	}
	else  if (bitOffset < 128) {
		this->Second_64 ^= (MASK << (bitOffset - 64));
	}
	else if (bitOffset < 192) {
		this->Third_64 ^= (MASK << (bitOffset - 128));
	}
	else {
		this->Fourth_64 ^= (MASK << (bitOffset - 192));
	}*/
}

ULL BoardMask::getBit(int bitOffset) {
	int offset = bitOffset / 64;
	return Values_x64[offset] & (MASK << (bitOffset - (64 * (offset))));
 }

BoardMask BoardMask::operator &(const BoardMask& otherboard) const {
	return BoardMask(this->Values_x64[0]&otherboard.Values_x64[0], this->Values_x64[1] & otherboard.Values_x64[1],
		this->Values_x64[2] & otherboard.Values_x64[2], this->Values_x64[3] & otherboard.Values_x64[3]);
	/*return BoardMask(this->First_64&otherboard.First_64, this->Second_64&otherboard.Second_64,
		this->Third_64&otherboard.Third_64, this->Fourth_64&otherboard.Fourth_64);*/
}

BoardMask BoardMask::operator |(const BoardMask& otherboard) const {
	return BoardMask(this->Values_x64[0] | otherboard.Values_x64[0], this->Values_x64[1] | otherboard.Values_x64[1],
		this->Values_x64[2] | otherboard.Values_x64[2], this->Values_x64[3] | otherboard.Values_x64[3]);
	/*return BoardMask(this->First_64|otherboard.First_64, this->Second_64|otherboard.Second_64,
		this->Third_64|otherboard.Third_64, this->Fourth_64|otherboard.Fourth_64);*/
}

BoardMask BoardMask::operator ^(const BoardMask& otherboard) const {
	return BoardMask(this->Values_x64[0] ^ otherboard.Values_x64[0], this->Values_x64[1] ^ otherboard.Values_x64[1],
		this->Values_x64[2] ^ otherboard.Values_x64[2], this->Values_x64[3] ^ otherboard.Values_x64[3]);
	/*return BoardMask(this->First_64^otherboard.First_64, this->Second_64^otherboard.Second_64,
		this->Third_64^otherboard.Third_64, this->Fourth_64^otherboard.Fourth_64);*/
}

BoardMask::BoardMask(ULL first, ULL second, ULL third, ULL fourth)
{
	Values_x64 = new ULL[4];
	this->Values_x64[0] = first;
	this->Values_x64[1] = second;
	this->Values_x64[2] = third;
	this->Values_x64[3] = fourth;
	this->MASK = 1;
}

BoardMask::~BoardMask()
{
}
