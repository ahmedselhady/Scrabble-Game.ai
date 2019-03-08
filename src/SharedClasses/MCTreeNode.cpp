#pragma once

#include <string>
#include <vector>
#include "MCTreeNode.h"
using namespace std;


MCTreeNode:: MCTreeNode(vector<char> Rack) {
	this->depth = 0;
	this->AverageReward = 0;
	this->Parent = NULL;
	this->NumberOfVisits = 0;
	this->Rack = Rack;
	//TODO: with the given rack generate all the possible moves to fill the vector of children
}

//This constructor is used with all other tree nodes than the root
MCTreeNode::MCTreeNode(MCTreeNode* parent) {
	this->depth = parent->Depth + 1;
	this->AverageReward = 0;
	this->Parent = parent;
	this->NumberOfVisits = 0;
	//TODO: complete the function that generates rack based on the current state and call it here
}



MCTreeNode::MCTreeNode* getPartent() {
	return Parent;
}

MCTreeNode::MCTreeNode* getMaxChild() {
	//TODO: return the best child from children based on thier average score
}

MCTreeNode::void incrementVisits() {
	NumberOfVisits++;
}

MCTreeNode::void setAverageReward(float NewReward) {
	AverageReward = NewReward;
}

MCTreeNode::float getAverageReward() {
	return AverageReward;
}

MCTreeNode::vector<char> getRack() {
	return Rack;
}

MCTreeNode::vector<char> generateRack() {
	//TODO:implement this function
}


