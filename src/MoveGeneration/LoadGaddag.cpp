
#include "LoadGaddag.h"
#include "LoadNode.h"
#include <sys/stat.h>
#include <algorithm>

#define DICT_FILE_NAME "./src/MoveGeneration/Dict.txt"
#define GADDAG_FILE_NAME "./src/MoveGeneration/GADDAG.txt"
#define ARA "./"
#define TOTAL_GADDAG_NODES 6419512

using namespace std;

//Function LoadGaddag is the constructor
LoadGaddag::LoadGaddag() : Root((char)GADDAG_ROOT)
{

    // nothing.
}

//Function readDictFile it reads dict. files which contains valid words given filename.
void LoadGaddag::readDictFile(vector<string> &dictGaddagWords, const char *fileName)
{

    string word;
    ifstream myFile(fileName);
    if (myFile.is_open())
    {
        string gaddagWord; // gaddag word structure.
        while (myFile >> word)
        {
            // Each word will be multipied by number of its characters. ex: "cat" will have three entries in GADDAG.
            for (int index = 0; index < word.size(); ++index)
            {
                gaddagWord = ""; //reset word.
                for (int prefix = index; prefix >= 0; --prefix)
                {
                    gaddagWord.insert(index - prefix, 1, word[prefix]);
                }                            // prefix part
                if (index < word.size() - 1) // no delimiter for last word inverted.
                {
                    gaddagWord.push_back(GADDAG_DELIMITER);
                    for (int suffix = index + 2; suffix <= word.size(); ++suffix)
                    {
                        gaddagWord.push_back((word[suffix - 1]));
                    } // suffix part
                }

                //            if(word == "aardvark"){
                //            	 cout<<gaddagWord<<endl;
                //            	 count++;
                //            }

                dictGaddagWords.push_back(gaddagWord);
            }
        }
        myFile.close();
    }
    else
    {
        cout << "Unable to open file";
        return;
    }
}

// for String Comparison.
bool compare(string &s1, string &s2)
{
    return s1.size() > s2.size();
}

//Function constructGaddag it builds Gaddag trie and returns compressed trie node.
Node *LoadGaddag::constructGaddag()
{

    struct stat buffer;

    if ((stat(GADDAG_FILE_NAME, &buffer) == 0))
    {

        ifstream inputGaddagFile(GADDAG_FILE_NAME);
        if (!inputGaddagFile.is_open())
        {
            cout << "Unable to open file HERE";
            return NULL;
        }
        cout << "HI GADDAG is RUNNING ... ";
        unsigned int *gaddagRootNode = new unsigned int[TOTAL_GADDAG_NODES];

        int nodeInfo;
        int index = 0;

        while (inputGaddagFile >> nodeInfo)
        {
            gaddagRootNode[index] = nodeInfo;
            index++;
        }
        //cout << " NODES: "<<index<<endl;
        inputGaddagFile.close();
        return (Node *)&gaddagRootNode[0]; // ROOT .. return address of the first value in compressed byte offset array casted in a Node type.
    }

    // Gaddag Root Construction.
    vector<string> dictGaddagWords; // GADDAG words from given dict. file.
    vector<LoadNode *> gaddagNodes; // store all nodes to then output a compressed structure then.
    readDictFile(dictGaddagWords, DICT_FILE_NAME);
    for (int index = 0; index < dictGaddagWords.size(); ++index)
    {
        Root.insertGaddagWord(dictGaddagWords[index]); //inserting word into GADDAG.
    }

    //bool check = Root.findWord("legovsaa");
    gaddagNodes.push_back(&Root);
    cout << "HERE 2" << endl;

    Root.storeNodes(gaddagNodes);
    unsigned int *gaddagRootNode = new unsigned int[gaddagNodes.size()];
    compressGaddag(gaddagRootNode, gaddagNodes);

    ofstream gaddagFile;
    gaddagFile.open(GADDAG_FILE_NAME);
    int index = 0;
    while (index < TOTAL_GADDAG_NODES) // Writing Data.
    {
        gaddagFile << gaddagRootNode[index];
        if (index != TOTAL_GADDAG_NODES - 1)
        {
            gaddagFile << "\n";
        }
        index++;
    }

    cout << "Total Nodes : " << gaddagNodes.size() << endl;
    return (Node *)&gaddagRootNode[0]; // ROOT .. return address of the first value in compressed byte offset array casted in a Node type.
}

//The function CompressGaddag it compresses the trie into an array of nodes using byte offset techinque.
void LoadGaddag::compressGaddag(unsigned int *&gaddagRootNode, vector<LoadNode *> &gaddagNodes)
{

    unsigned char compressedLetter; // i.e.: means that a = 1 .... z = 26
    /* info in compressedLetter : 1- letter after compression.
                                  2- is it the last character mapped as a bit.
                                  3- is it the parent's last child.
                                  */
    unsigned int address; // just the distance between the parent and child that will be used
    // as an offset in offset byte array.
    unsigned letter;

    for (int index = 0; index < gaddagNodes.size(); ++index)
    {
        letter = (gaddagNodes[index])->getLetter();
        if (letter != GADDAG_DELIMITER && letter != GADDAG_ROOT)
        {
            compressedLetter = (letter - CHAR_OFFSET);
        }
        else
        {
            compressedLetter = COMPRESSED_GADDAG_DELIMITER;
        }

        compressedLetter &= 0x0000001F;
        if (gaddagNodes[index]->isEndOfWord())
        {
            compressedLetter |= 0x20;
        }
        //73986
        if (gaddagNodes[index]->isLastChild())
        {
            compressedLetter |= 0x40;
        }
        address = gaddagNodes[index]->numberOfChilds();
        if (address != 0)
        {                     // Byte Index.
            address -= index; // as all counts(addresses) are increased by one to achieve a right indexed offset.
        }

        gaddagRootNode[index] = (address & 0x00FFFFFF) | (compressedLetter << 24);
        if (index == 73985)
        {
            cout << "Adress : " << gaddagNodes[index]->numberOfChilds() << endl;
            cout << "node info : " << gaddagRootNode[index] << endl;
        }
    }
}
