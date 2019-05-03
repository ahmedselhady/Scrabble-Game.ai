

#include <string>
#include <vector>
#include "MCTSearch.h"

MCTSearch::MCTSearch(list<Move> Moves)
{
	this->Root = new MCTreeNode(Moves);
}

MCTreeNode *MCTSearch::SelectBestMove(MCTreeNode *Parent)
{
	MCTreeNode *BestChild = NULL;
	float BestScore = FLT_MIN;
	float CurrentScore = 0;
	;
	int cp = 30;
	for (int i = 0; i < Parent->Children.size(); i++)
	{
		if (Parent->Children[i]->getNumberOfVisits() == 0)
		{
			cout << "Parent never visited" << endl;
			CurrentScore =(float) (Parent->Children[i]->getMoveScore());
		}
		else
		{
			cout << "Normal Visit" << endl;
			CurrentScore = Parent->Children[i]->getMoveScore() +
						   2 * cp * log((2 * Parent->getNumberOfVisits()) / Parent->Children[i]->getNumberOfVisits());
		}

		if (CurrentScore > BestScore && Parent->Children[i]->isExpandable())
		{
			BestChild = Parent->Children[i];
			BestChild->incrementVisits();
			BestScore = CurrentScore;
		}
	}
	return BestChild;
}

int MCTSearch::endGameMCTS()
{
	//10000 is the available computation power
	for (int i = 0; i < 10000; i++)
	{
		Root->incrementVisits();

		//Primary Selection on depth=1
		MCTreeNode *FirstMove = SelectBestMove(Root);
		if (FirstMove == NULL)
			break;
		//expand on selected depth=1 if possible(more moves are unexplored)
		FirstMove->expandEndGame();
		//select from depth=2
		MCTreeNode *SecondMove = SelectBestMove(FirstMove);
		if (SecondMove == NULL)
			FirstMove->setNonExpandable();

		//expand from depth=2 if possible and if not we should mark node selected from depth=2 expandable=false
		//then select the second best option  to expand it, until all are not expandable then the whole tree from node
		//selected at depth=1 is not expanable and therefore mark it as non expanable
		SecondMove->expandEndGame();

		//We will not select again but instead perform simulation on the last expanded node as it is the newest node to the path
		//to the tree
		int MySecondMove = SecondMove->Children.back()->getMoveScore();
		//Finally the value will be back propagated to the d=1 node
		float MoveDifference = FirstMove->getMoveScore() + MySecondMove - SecondMove->getMoveScore();
		if (MoveDifference > FirstMove->getAverageReward())
		{
			FirstMove->setAverageReward(MoveDifference);
		}
	}

	float BestMoveScore = FLT_MIN;
	int BestMoveIndex = -1;
	for (int j = 0; j < Root->Children.size(); j++)
	{
		if (Root->Children[j]->getAverageReward() > BestMoveScore)
		{
			BestMoveIndex = j;
			BestMoveScore = Root->Children[j]->getAverageReward();
		}
	}
	this->destroyMCTree(this->Root);
	return BestMoveIndex;
}

int MCTSearch::midGameMCTS()
{
	//10000 is the available computation power
	for (int i = 0; i < 10000; i++)
	{
		Root->incrementVisits();

		//Primary Selection on depth=1
		MCTreeNode *FirstMove = SelectBestMove(Root);
		if (FirstMove == NULL)
			break;

		//expand on selected depth=1 if possible(more moves are unexplored)

		//call function that is called expandmidgame on FirstMove Node that will create new node and add it to
		//children give it the new depth and value. If list of available moves is empty then mark this
		//node as un expandable
		FirstMove->expandMidGame();

		//We will not select again but instead perform simulation on the last expanded node as it is the newest node to the path
		//to the tree

		int OpponentMoveScore = 0;
		if (FirstMove->Children.size() == 0)
		{

			OpponentMoveScore = 10;
		}
		else
		{
			OpponentMoveScore = FirstMove->Children.back()->getMoveScore();
		}

		//Finally the value will be back propagated to the d=1 node to calculate the move score
		//For now we will be saving the maximum score in the branch
		float MoveDifferenece = FirstMove->getMoveScore() - OpponentMoveScore;
		if (MoveDifferenece > FirstMove->getAverageReward())
		{
			FirstMove->setAverageReward(MoveDifferenece);
		}
	}
	float BestMoveScore = FLT_MIN;
	int BestMoveIndex = -1;
	for (int j = 0; j < Root->Children.size(); j++)
	{
		if (Root->Children[j]->getAverageReward() > BestMoveScore)
		{
			BestMoveIndex = j;
			BestMoveScore = Root->Children[j]->getAverageReward();
		}
	}

	this->destroyMCTree(this->Root);
	return BestMoveIndex;
}

void MCTSearch::destroyMCTree(MCTreeNode *CurrentNode)
{
	/*if (CurrentNode->getDepth() == 3) {
		delete CurrentNode;
		return;
	}*/
	while (!empty(CurrentNode->Children))
	{
		destroyMCTree(CurrentNode->Children.back());
		CurrentNode->Children.pop_back();
	}
	delete CurrentNode;
	return;
}