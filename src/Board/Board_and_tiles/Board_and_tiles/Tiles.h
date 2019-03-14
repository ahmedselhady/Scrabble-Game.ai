#pragma once
#ifndef TILES_H
#define TILES_H
#include <vector>
#include <algorithm>
using namespace std;

class Tiles
{
private:


	 vector<char> RackTiles;//Vector Containing character which is tiles
public:

	Tiles();//Default Constructor
	vector<char> getTiles();//function to get current rack of tiles
	bool addTiles(char tile);//function to add a tile to the rack
	bool exchngTiles(char Current,char New);//function to exchange tiles with server

};

#endif