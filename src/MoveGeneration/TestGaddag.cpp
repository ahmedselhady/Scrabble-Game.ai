//Test Main:


//INCLUDES:

#include "LoadGaddag.h"
#include "../SharedClasses/Logger.hpp"

// NOTE: when printing cout use the Logger class utility function 'log'.

using namespace std;

inline Node* createGaddag(){ // just a test function.
	 LoadGaddag gaddagConstructor;
	 Node* gaddagRoot = gaddagConstructor.constructGaddag();
	 return gaddagRoot;
}

int main() {
	Node* gaddagRoot;

	gaddagRoot = createGaddag();

    cout <<std::hex<< gaddagRoot->getNodeInfo()<< endl;
    unsigned int x = 0x000000ff;
    cout << std::hex<< x<<endl;
    cout << gaddagRoot->findChildChar('z')<<endl;

    system("pause");
    return 0;
}
