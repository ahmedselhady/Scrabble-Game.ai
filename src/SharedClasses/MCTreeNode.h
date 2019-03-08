#pragma once

#include <string>
#include <vector>
using namespace std;

class MCTreeNode {
//This class Represents a state weather for the player or the opponent in the monte carlo search tree
public:

	//This constructor is only used with the root Node as it has no parent
 MCTreeNode(vector<char> Rack);

	//This constructor is used with all other tree nodes than the root
 MCTreeNode(MCTreeNode* parent);

	MCTreeNode* getPartent();

	MCTreeNode* getMaxChild();

	void incrementVisits();

	//This function will be used when back propagating a new value in monte carlo
	void setAverageReward(float NewReward);

	float getAverageReward();

	vector<char> getRack();

	vector<char> generateRack();


private:

	MCTreeNode* Parent;		//Parent Node
	std::vector<MCTreeNode*> Children;	//Children expanded for the node till now
	int Depth;				//Depth of the current node
	int NumberOfVisits;		//Number of times this node was included in a path(certain play)
	float AverageReward;	//The reward I will win from this play (opponent score will be propagated as negative score)
	std::vector<char> Rack;		//The Rack in this state
	

};