#include <iostream>
#include "AI_MODE.cpp"


void main()
{
	unordered_map<char,int> Tiles;
	Tiles['A'] = 1;
	Tiles['B'] = 2;
	Tiles['C'] = 3;
	Tiles['D'] = 2;
	Tiles['K'] = 2;
	Tiles['G'] = 2;
	Tiles['H'] = 2;
	Tiles['L'] = 2;
	Tiles['Q'] = 3;
	Tiles['Z'] = 2;
	vector<char> Rack;
    Rack.push_back('A');
    Rack.push_back('L');
    Rack.push_back('K');
    Rack.push_back('D');

    Rack.push_back('Z');
    Rack.push_back('V');
    Rack.push_back('B');
    bool isEmpty=true;
    Move recommendedMove = AI_Mode_Function(Tiles,Rack,isEmpty);
    std::cout <<"Move word: "<< recommendedMove.word<< "recommended move score:" << recommendedMove.moveScore<<endl;

}