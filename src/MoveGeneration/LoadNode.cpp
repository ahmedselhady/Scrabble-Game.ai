
//INCLUDES:

#include <unordered_map>
#include<iostream>
#include "LoadNode.h"
//#include "LoadGaddag.h"
using namespace std;

int count = 0;
// char wordLength; // for now.
// vector<LoadNode*> linkNodes;
//Funtion LoadNode is constructor is for initialization
LoadNode::LoadNode(char letter){
    this->letter = letter;
    //this->isTerminal = false;
    this->lastChar = false;
    this->lastChild = false;
    this->numberChilds = 0;
}

// void LoadNode::setWordLength(int value){
//     wordLength = value;
// }


//Function addChild it adds a successor.
inline void LoadNode::addChild(char letter ,LoadNode &node){
        this->childeren.push_back(node);
}

//Function numberOfChilds return number of childern.
int LoadNode::numberOfChilds(){
	return numberChilds;
}

// inline bool LoadNode::isTerminal(){
//     return this->isTerminal;
// } // i.e. Node is last Node in the trie.

/*
Function isEndofWord the Node contains EOW character (last character).
i.e. Node is last character in a valid word.
*/
bool LoadNode::isEndOfWord(){
    return lastChar;
}

//Function isLastChild the Node is last child of his parent.
bool LoadNode::isLastChild(){
    return lastChild;
}


//Function getChild get child corresponding to the node letter.
inline int LoadNode::getChild(char letter){

     for (int index = 0; index < this->childeren.size(); ++index)
	 {
		if (childeren[index].letter == letter)
		{
			return index;
	    }
     }
     return -1; // not node letter not found.

}

//Function getLetter it retuns the node character.
char LoadNode::getLetter(){
    return letter;
}

//Function insertGaddagWord it inserts a word in gaddag trie.
void LoadNode::insertGaddagWord(string gaddagWord){

  if(gaddagWord.length() == 0) { this->lastChar = true;
      return ;} // no chars to insert.

  char firstChar = gaddagWord[0];
  string remainingChars = gaddagWord.substr(1,gaddagWord.size()-1);
//   if(wordLength >= 4){
//       linkNodes.push_back(this);
//   }
//   if(wordLength<5 && wordLength != -1){
//       wordLength++;
//   }
//       int linkIndex = this->getChild(firstChar);
  int childIndex = getChild(firstChar);
  if(childIndex == -1)
  {
      LoadNode child(firstChar);
      this->addChild(firstChar,child);
      childIndex = childeren.size() - 1; // as it was the last one pushed.
  }

  childeren[childIndex].insertGaddagWord(remainingChars);
//       if(this->letter == GADDAG_DELIMITER&&linkNodes.size() != 0){

//             bool check = (linkNodes[0]->letter == firstChar);     
//             this->addChild(firstChar,linkNodes[0]); //Dummy FirstChar.
//             linkNodes.erase(linkNodes.begin());
//       }
//       else{
//              if(linkIndex == -1)
//              {
//                   LoadNode* child = new LoadNode(firstChar);
//                   this->addChild(firstChar,child); //Dummy FirstChar.
//                   linkIndex = childeren.size() - 1; // as it was the last one pushed.
//              }
//              childeren[linkIndex]->insertGaddagWord(remainingChars);
//       }
}

bool LoadNode::findWord(string word){

	int size = word.length();
	if(size == 0){return true;}

	int index;
	index = this->getChild(word[0]) ;
	char letter = word[0];

	cout<< letter <<" ";

	if(index == -1){
		return false;
	}
	return childeren[index].findWord(word.substr(1,word.size()-1));
}

//Function storeNodes it store nodes in gaddagNodes.
void LoadNode::storeNodes(vector< LoadNode* >& gaddagNodes)
{
	int size = childeren.size() ;
	if (childeren.size() == 0){return;}


	this->numberChilds = gaddagNodes.size();  // usefull for byte offset indexing.
	childeren[childeren.size() - 1].lastChild = true;

	for (int index = 0; index < childeren.size(); ++index)
    {
        gaddagNodes.push_back(&childeren[index]);



//        if(count == 6 && this->letter == 'v'){
//        	std::cout<<childeren[index].letter<<" "<<endl;
//        }
    }
//	if(count == 6 && this->letter == 'v'){
//		cout<<"Level : "<<count<<endl;
//	}

	for (int index = 0; index < childeren.size(); ++index)
    {
		childeren[index].storeNodes(gaddagNodes); // recursively for all nodes.
    }
	//count--;
}

// inline void  LoadNode::setTerminal(){
//     this->isTerminal = true;
// } // returns terminal state.

//Function setLastChild it returns last child state.
inline void  LoadNode::setLastChild(){
    this->lastChild = true;
}

//Function setLastChar it returns last char state.
inline void LoadNode::setLastChar(){
    this->lastChar = true;
}
