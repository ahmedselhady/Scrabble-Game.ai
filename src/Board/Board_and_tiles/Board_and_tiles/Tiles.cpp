#include "./Tiles.h"

#include <algorithm>

Tiles::Tiles()
{
}

std::vector<char> Tiles::getRackTiles()
{

	return (RackTiles);//return current rack of tiles
}

Tiles* Tiles::TilesInst_=nullptr;

Tiles* Tiles::getTiles()
{

	if(TilesInst_==nullptr)
	{
		TilesInst_=new Tiles;
	}
	
	return (TilesInst_);
}

bool Tiles::addTiles(char tile)
{

        if(RackTiles.size()<7)//if rack of tiles less than 7 then you can add other wise operation fail with false return
        {
          RackTiles.push_back(tile); 
          return true;
        }
return false;
}

bool Tiles::exchngTiles(char Current,char New)
{
  
std::vector<char>::iterator itr= find(RackTiles.begin(), RackTiles.end(), Current);
//if the current tile is found in the rack of tiles exchange is successful other wise fail with false return

if (  itr!= RackTiles.end() )
   {
       //here we may take the current tile to give it to server befor deleting it from the rack of tiles
       RackTiles.erase(itr);//remove the current tile
       RackTiles.push_back(New);//add the new one

       return true;
   }
return false;
}