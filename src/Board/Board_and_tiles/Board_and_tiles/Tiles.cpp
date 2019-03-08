#include "Tiles.h"

Tiles::Tiles()
{
}

vector<char> Tiles::getTiles()
{

	return (RackTiles);//return current rack of tiles
}
bool Tiles::addTiles(char tile)
{

        if(RackTiles.size()<6)//if rack of tiles less than 7 then you can add other wise operation fail with false return
        {
          RackTiles.push_back(tile); 
          return true;
        }
return false;
}
bool Tiles::exchngTiles(char Current,char New)
{
  
vector<char>::iterator itr= find(RackTiles.begin(), RackTiles.end(), Current);
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