
//INCLUDES:

#include <unordered_map>
#include "LoadNode.h"
using namespace std;

LoadNode::LoadNode(char letter){
    this->letter = letter;
    //this->isTerminal = false;
    this->lastChar = false;
    this->lastChild = false;
    this->numberChilds = 0;
}

inline void LoadNode::addChild(char letter ,LoadNode& node){
        this->childeren.push_back(node);
} // Adding successor.

int LoadNode::numberOfChilds(){
	return numberChilds;
}// return number of childern.

// inline bool LoadNode::isTerminal(){
//     return this->isTerminal;
// } // i.e. Node is last Node in the trie.

bool LoadNode::isEndOfWord(){
    return lastChar;
} // i.e. Node is last character in a valid word.

bool LoadNode::isLastChild(){
    return lastChild;
}// i.e. Node is last child of his parent.

inline int LoadNode::getChild(char letter){

     for (int index = 0; index < this->childeren.size(); ++index)
	 {
		if (childeren[index].letter == letter)
		{
			return index;
	    }
     }
     return -1; // not node letter not found.

} // get child corresponding to the node letter.

char LoadNode::getLetter(){
    return letter;
} // Retuns the node character.

void LoadNode::insertGaddagWord(string gaddagWord){

  if(gaddagWord.size() == 0) { this->lastChar = true;
      return ;} // no chars to insert.

  char firstChar = gaddagWord[0];
  string remainingChars = gaddagWord.substr(1,gaddagWord.size());

  int childIndex = getChild(firstChar);
  if(childIndex == -1)
  {
      LoadNode child(firstChar);
      this->addChild(firstChar,child);
      childIndex = childeren.size() - 1; // as it was the last one pushed.
  }

  childeren[childIndex].insertGaddagWord(remainingChars);

} // inserts a word in gaddag trie.

void LoadNode::storeNodes(vector< LoadNode* >& gaddagNodes)
{
	if (childeren.size() == 0){return;}

	this->numberChilds = gaddagNodes.size();  // usefull for byte offset indexing.
	childeren[childeren.size() - 1].lastChild = true;

	for (int index = 0; index < childeren.size(); ++index)
    {
        gaddagNodes.push_back(&childeren[index]);
    }

	for (int index = 0; index < childeren.size(); ++index)
    {
		childeren[index].storeNodes(gaddagNodes); // recursively for all nodes.
    }
}

// inline void  LoadNode::setTerminal(){
//     this->isTerminal = true;
// } // returns terminal state.
inline void  LoadNode::setLastChild(){
    this->lastChild = true;
}// returns last child state.
inline void LoadNode::setLastChar(){
    this->lastChar = true;
}// returns last char state.
