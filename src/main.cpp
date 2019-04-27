#include <iostream>
#include "AI_MODE.h"


void main()
{
	unordered_map<char,int> Tiles;
	Tiles['b'] = 1;
	Tiles['e'] = 1;
	Tiles['l'] = 1;
	Tiles['z'] = 1;
	Tiles['n'] = 1;
	Tiles['g'] = 1;
	Tiles['h'] = 1;
	Tiles['o'] = 1;
	Tiles['q'] = 1;
	Tiles['y'] = 1;
	vector<char> Rack;
    Rack.push_back('f');
    Rack.push_back('x');
    Rack.push_back('a');
    Rack.push_back('g');

    Rack.push_back('o');
    Rack.push_back('v');
    Rack.push_back('b');
    bool isEmpty=true;
    Move recommendedMove = AI_Mode_Function(Tiles,Rack,isEmpty);
    std::cout <<"Move word: "<< recommendedMove.word<< "recommended move score:" << recommendedMove.moveScore<<endl;
	system("pause");
}