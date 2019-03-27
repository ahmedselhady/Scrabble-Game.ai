#include "./Tiles.h"

#include <algorithm>

Tiles::Tiles()
{
}

//This Function returns current rack of tiles
std::vector<char> Tiles::getRackTiles()
{

	return (RackTiles)
}

Tiles* Tiles::TilesInst_=nullptr;


//This Function return tiles
Tiles* Tiles::getTiles()
{

	if(TilesInst_==nullptr)
	{
		TilesInst_=new Tiles;
	}
	
	return (TilesInst_);
}

//This Function add tiles to the rack
bool Tiles::addTiles(char tile)
{

        if(RackTiles.size()<7)//if rack of tiles less than 7 then you can add other wise operation fail with false return
        {
          RackTiles.push_back(tile); 
          return true;
        }
return false;
}

//This Function exchange tiles
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
