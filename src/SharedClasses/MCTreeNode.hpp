#pragma once

#include <string>
#include <vector>
#include<list>
#include "Move.hpp"
#include "Opponent-Rack-Generator/Opponent.h"

using namespace std;

//struct Move { // defines what a "Move" is.
//	int moveScore;
//	int startPosition;
//	bool horizontal; // true -> horiz false -> vertical.
//};

class MCTreeNode {
//This class Represents a state weather for the player or the opponent in the monte carlo search tree
public:

	std::vector<MCTreeNode*> Children;	//Children expanded for the node till now

	//This constructor is only used with the root Node as it has no parent
	MCTreeNode(list<Move> Moves);

	//This constructor is used with all other tree nodes than the root
	MCTreeNode(MCTreeNode* parent, int moveScore);

	MCTreeNode* getPartent();

	void incrementVisits();

	//This function will be used when back propagating a new value in monte carlo
	void setAverageReward(float NewReward);

	float getAverageReward();

	vector<char> generateRack();

	vector<MCTreeNode*> getChildren();

	bool isExpandable();

	void setNonExpandable();

	int getNumberOfVisits();

	int getDepth();

	int getMoveScore();
	void expandMidGame();
	void expandEndGame();
	~MCTreeNode();
private:

	MCTreeNode* Parent;		//Parent Node
	int moveScore;			//The score of the move itself
	int Depth;				//Depth of the current node
	int NumberOfVisits;		//Number of times this node was included in a path(certain play)
	float AverageReward;	//The reward I will win from this play (opponent score will be propagated as negative score)
	std::vector<char> Rack;		//The Rack in this state //amr
	list<Move> PossibleMoves; //The Stack of unplayed moves
	bool Expandable;		//Check if the node still has Moves that are not expanded
	
};