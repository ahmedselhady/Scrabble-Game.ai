#pragma once

#include <string>
#include <vector>
#include "MCTreeNode.h"
using namespace std;

unordered_map<char, int> globalBag;


MCTreeNode:: MCTreeNode(list<Move> Moves) {
	this->Depth = 0;
	this->AverageReward = 0;
	this->Parent = NULL;
	this->NumberOfVisits = 0;
	this->PossibleMoves = Moves;
	this->Expandable = true;
	for (int i = 0; i < Moves.size(); i++) {
		std::list<Move>::iterator it = Moves.begin();
		std::advance(it, i);
		Children.push_back(new MCTreeNode(this, it->moveScore));
	}
	
}

//This constructor is used with all other tree nodes than the root
MCTreeNode::MCTreeNode(MCTreeNode* parent,int moveScore) {
	this->Depth = parent->Depth + 1;
	this->AverageReward = 0;
	this->moveScore = moveScore;
	this->Parent = parent;
	this->NumberOfVisits = 0;
	this->Expandable = true;

	//expand the node only if it is non terminal node
	if(this->Depth<3){
		//TODO: with the given rack generate all the possible moves to fill the vector of children

		//TODO: Using the Rack Generated we need to generate all the possible moves "Just Call the Function" and Assign it to 
		//List Moves

	}
	
}

 MCTreeNode* MCTreeNode::getPartent() {
	return Parent;
}

void MCTreeNode::incrementVisits() {
	NumberOfVisits++;
}


bool MCTreeNode::isExpandable() {
	return Expandable;
}
void MCTreeNode::setAverageReward(float NewReward) {
	AverageReward = NewReward;
}

float MCTreeNode::getAverageReward() {
	return AverageReward;
}


vector<char> MCTreeNode::generateRack() {
	globalBag['A'] = 1;
	globalBag['B'] = 2;
	globalBag['L'] = 3;
	globalBag['D'] = 2;
	globalBag['K'] = 2;
	globalBag['G'] = 2;
	globalBag['H'] = 2;
	globalBag['O'] = 2;
	globalBag['Q'] = 3;
	globalBag['Z'] = 2;
	OpponentRack OP;
	OP.RackGenerator(globalBag);
	return OP.GetRack();

}

vector<MCTreeNode*> MCTreeNode::getChildren() {
	return this->Children;
}

int MCTreeNode::getNumberOfVisits() {
	return this->NumberOfVisits;
}

void MCTreeNode::setNonExpandable() {
	this->Expandable = false;
}

int MCTreeNode::getDepth() {
	return this->Depth;
}

int MCTreeNode::getMoveScore() {
	return this->moveScore;
}



void MCTreeNode::expandMidGame() {
	if (this->PossibleMoves.size() == 0) { 
		this->setNonExpandable(); 
		return;
	}
	else {
		Move newChild = this->PossibleMoves.back();
		this->PossibleMoves.pop_back();
		this->Children.push_back(new MCTreeNode(this, newChild.moveScore));
		if (this->PossibleMoves.size() == 0) this->setNonExpandable();
	}
}
void MCTreeNode::expandEndGame() {
	if (this->PossibleMoves.size() == 0) {
		this->setNonExpandable();
		return;
	}
	else {
		Move newChild = this->PossibleMoves.back();
		this->PossibleMoves.pop_back();
		this->Children.push_back(new MCTreeNode(this, newChild.moveScore));
		if (this->PossibleMoves.size() == 0&& this->Depth==2) this->setNonExpandable();
	

	}
}