#include <iostream>
#include "AI_MODE.h"


void main()
{
	unordered_map<char,int> Tiles;
	Tiles['A'] = 1;
	Tiles['B'] = 1;
	Tiles['L'] = 1;
	Tiles['D'] = 1;
	Tiles['K'] = 1;
	Tiles['G'] = 1;
	Tiles['H'] = 1;
	//Tiles['O'] = 1;
	//Tiles['Q'] = 1;
	//Tiles['Z'] = 1;
	vector<char> Rack;
    Rack.push_back('A');
    Rack.push_back('L');
    Rack.push_back('L');
    Rack.push_back('D');

    Rack.push_back('O');
    Rack.push_back('V');
    Rack.push_back('B');
    bool isEmpty=true;
    Move recommendedMove = AI_Mode_Function(Tiles,Rack,isEmpty);
    std::cout <<"Move word: "<< recommendedMove.word<< "recommended move score:" << recommendedMove.moveScore<<endl;
	system("pause");
}