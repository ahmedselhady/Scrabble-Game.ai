#include "./BoardMask.hpp"

#include <iostream>

//This Function setBit whose bitOffset Is Calculated using Equation provided by andrew
void BoardMask::setBit(int bitOffset) {
	Values_x64[bitOffset >> 6] |= (MASK << (bitOffset - (64 * (bitOffset >> 6))));
 }

// This unset bit whose bitOffset Is Calculated using Equation provided by andrew
void BoardMask::unsetBit(int bitOffset) { 
	Values_x64[bitOffset >> 6] ^= (MASK << (bitOffset - (64 * (bitOffset >> 6))));
}

//This Function getsbit whose bitOffset is given
bool BoardMask::getBit(int bitOffset) {
	int offset = bitOffset / 64;
	return (Values_x64[offset] & (MASK << (bitOffset - (64 * (offset)))));
 }

BoardMask BoardMask::operator &(const BoardMask& otherboard) const {
	return BoardMask(this->Values_x64[0]&otherboard.Values_x64[0], this->Values_x64[1] & otherboard.Values_x64[1],
		this->Values_x64[2] & otherboard.Values_x64[2], this->Values_x64[3] & otherboard.Values_x64[3]);
}

BoardMask BoardMask::operator |(const BoardMask& otherboard) const {
	return BoardMask(this->Values_x64[0] | otherboard.Values_x64[0], this->Values_x64[1] | otherboard.Values_x64[1],
		this->Values_x64[2] | otherboard.Values_x64[2], this->Values_x64[3] | otherboard.Values_x64[3]);
}

BoardMask BoardMask::operator ^(const BoardMask& otherboard) const {
	return BoardMask(this->Values_x64[0] ^ otherboard.Values_x64[0], this->Values_x64[1] ^ otherboard.Values_x64[1],
		this->Values_x64[2] ^ otherboard.Values_x64[2], this->Values_x64[3] ^ otherboard.Values_x64[3]);
}

BoardMask& BoardMask::operator &=(const BoardMask& otherboard)  {
	this->Values_x64[0] &= otherboard.Values_x64[0];
	this->Values_x64[1] &= otherboard.Values_x64[1];
	this->Values_x64[2] &= otherboard.Values_x64[2];
	this->Values_x64[3] &= otherboard.Values_x64[3];
	return (*this);
}

BoardMask& BoardMask::operator |=(const BoardMask& otherboard) {
	this->Values_x64[0] |= otherboard.Values_x64[0];
	this->Values_x64[1] |= otherboard.Values_x64[1];
	this->Values_x64[2] |= otherboard.Values_x64[2];
	this->Values_x64[3] |= otherboard.Values_x64[3];
	return (*this);
}

BoardMask& BoardMask::operator ^=(const BoardMask& otherboard) {
	this->Values_x64[0] ^= otherboard.Values_x64[0];
	this->Values_x64[1] ^= otherboard.Values_x64[1];
	this->Values_x64[2] ^= otherboard.Values_x64[2];
	this->Values_x64[3] ^= otherboard.Values_x64[3];
	return (*this);
}

BoardMask& BoardMask::operator =(const BoardMask& otherboard) {
	if (this->Values_x64 != nullptr) {
		delete[] this->Values_x64;
	}

	Values_x64 = new ULL[4];
	this->Values_x64[0] = otherboard.Values_x64[0];
	this->Values_x64[1] = otherboard.Values_x64[1];
	this->Values_x64[2] = otherboard.Values_x64[2];
	this->Values_x64[3] = otherboard.Values_x64[3];
	return (*this);
}

bool BoardMask::operator !=(const BoardMask& otherboard) {
	return (Values_x64[0] != otherboard.Values_x64[0] || Values_x64[1] != otherboard.Values_x64[1]
		|| Values_x64[2] != otherboard.Values_x64[2] || Values_x64[3] != otherboard.Values_x64[3]);
}

bool BoardMask::operator ==(const BoardMask& otherboard) {
	return (Values_x64[0] == otherboard.Values_x64[0] && Values_x64[1] == otherboard.Values_x64[1]
		&& Values_x64[2] == otherboard.Values_x64[2] && Values_x64[3] == otherboard.Values_x64[3]);
}

BoardMask& BoardMask::operator <<(int offset) {
	// now this is tricky!
	// to shift left, we need to see by how much values should we shift!
	switch (offset >> 6) {
	case 0:
		// less than 64 bits, shift them all by the same value:
		Values_x64[3] = ((Values_x64[3] << offset) | (Values_x64[2] >> (64 - offset)));
		Values_x64[2] = ((Values_x64[2] << offset) | (Values_x64[1] >> (64 - offset)));
		Values_x64[1] = ((Values_x64[1] << offset) | (Values_x64[0] >> (64 - offset)));
		Values_x64[0] = Values_x64[0] << offset;
		break;
	case 1:
		offset -= 64;
		Values_x64[3] = ((Values_x64[3] << offset) | (Values_x64[2] >> (64 - offset)));
		Values_x64[2] = ((Values_x64[2] << offset) | (Values_x64[1] >> (64 - offset)));
		Values_x64[1] = ((Values_x64[1] << offset) | (Values_x64[0] >> (64 - offset)));
		Values_x64[0] = 0;
		break;
	case 2:
		offset -= 128;
		Values_x64[3] = ((Values_x64[3] << offset) | (Values_x64[2] >> (64 - offset)));
		Values_x64[2] = ((Values_x64[2] << offset) | (Values_x64[1] >> (64 - offset)));
		Values_x64[1] = 0;
		Values_x64[0] = 0;
		break;
	case 3:
		offset -= 192;
		Values_x64[3] = ((Values_x64[3] << offset) | (Values_x64[2] >> (64 - offset)));
		Values_x64[2] = 0;
		Values_x64[1] = 0;
		Values_x64[0] = 0;
		break;
	default:
		throw "Offset Out of Bound";
	}
	return (*this);
}

BoardMask& BoardMask::operator >>(int offset) {
	// now this is tricky!
	// to shift left, we need to see by how much values should we shift!
	switch (offset >> 6) {
	case 0:
		// less than 64 bits, shift them all by the same value:
		Values_x64[0] = ((Values_x64[0]>>offset) | (Values_x64[1]<<(64-offset)) );
		Values_x64[1] = ((Values_x64[1] >> offset) | (Values_x64[2] << (64 - offset)));
		Values_x64[2] = ((Values_x64[2] >> offset) | (Values_x64[3] << (64 - offset)));
		Values_x64[3] = Values_x64[3] >> offset;
		break;
	case 1:
		offset -= 64;
		Values_x64[0] = ((Values_x64[0] >> offset) | (Values_x64[1] << (64 - offset)));
		Values_x64[1] = ((Values_x64[1] >> offset) | (Values_x64[2] << (64 - offset)));
		Values_x64[2] = ((Values_x64[2] >> offset) | (Values_x64[3] << (64 - offset)));
		Values_x64[3] = 0;
		break;
	case 2:
		offset -= 128;
		Values_x64[0] = ((Values_x64[0] >> offset) | (Values_x64[1] << (64 - offset)));
		Values_x64[1] = ((Values_x64[1] >> offset) | (Values_x64[2] << (64 - offset)));
		Values_x64[2] = 0;
		Values_x64[3] = 0;
		break;
	case 3:
		offset -= 192;
		Values_x64[0] = ((Values_x64[0] >> offset) | (Values_x64[1] << (64 - offset)));
		Values_x64[1] = 0;
		Values_x64[2] = 0;
		Values_x64[3] = 0;
		break;
	default:
		throw "Offset Out of Bound";
	}
	return (*this);
}

void BoardMask::print(){

	for(int i=0, j=0;i<225;++i,++j){
		if(j%15==0)
			std::cout<<"\n";
		std::cout<<getBit(i)<<" ";
	}
}

bool BoardMask::isEmpty()
{
	return ((this->Values_x64[0] | this->Values_x64[1]|this->Values_x64[2]|this->Values_x64[3]));

}

BoardMask::BoardMask(ULL first, ULL second, ULL third, ULL fourth)// first is the LSB
{
	Values_x64 = new ULL[4];
	this->Values_x64[0] = first;
	this->Values_x64[1] = second;
	this->Values_x64[2] = third;
	this->Values_x64[3] = fourth;
	this->MASK = 1;
}

BoardMask::BoardMask(const BoardMask& board) {
	Values_x64 = new ULL[4];
	this->Values_x64[0] = board.Values_x64[0];
	this->Values_x64[1] = board.Values_x64[1];
	this->Values_x64[2] = board.Values_x64[2];
	this->Values_x64[3] = board.Values_x64[3];
	this->MASK = 1;
}

BoardMask::~BoardMask()
{
	delete [] this->Values_x64;
}
