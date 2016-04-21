#include <iostream>
#include <fstream>
#include "trie.h"

using namespace std;

// Test program
int main()
{
	// Create trie
    Trie* trie = new Trie;
    
    // Add queries
    trie->addQuery("ATTGGTACACATTGGTACACATTGGTACACATTGGTACACATTGGTACAC");
    trie->addQuery("ACGGTGCGGCTTATTGGTACACATTGGTACACATTGGTACACATTGGTAC");
    trie->addQuery("ATAACCCATATTATTGGTACACATTGGTACACATTGGTACACATTGGTAC");
    trie->addQuery("CAAACCCCTTTTATTGGTACACATTGGTACACATTGGTACACATTGGTAC");

	// Search for subject
    string subject = "ACGGTGCGGCTTATTGGTACACATTGGTACACACTGGTACACATTGGTAC";
    trie->searchTrieRecursively(trie->getRoot(), subject, 1);
    
    cout << "Found " << subject << " at: " << trie->getIndex() << " with: " << trie->getMismatch() << " mismatches."  << endl;
    // TODO Create local variable that keeps track of best mismatches and index.

    // Free memory because we are good people
    delete trie;

    //input from file testing and tree building
    int* listSize = new int[5] {100,1000,10000,50000,100000};
    std::string fileName = "dengV2_";
    int listIndex = 0;

    Trie* listTest = new Trie;
    std::string tmpFileName = fileName;
    tmpFileName += to_string(listSize[listIndex]);
    ifstream file(tmpFileName);
    //ofstream wfile("dengV2_index11");
    std::string* strTemp = new std::string[5];

    if (file.is_open()) {

        printf("\nfile was opened\n");

        int count = 0;

        for (string line; getline(file, line);) {

            //if(count %10 == 0)
            //   printf("Str count %d : %s\n",(int) line.length(), line.c_str());
            listTest->addQuery(line);

            if(count<5){

                strTemp[count++] = line;
            }

        }
    }
    printf("\n%s %6d %s %6d %s\n","Trie was created with list of size ", listSize[listIndex],
           " the size of the trie is ", listTest->getSize(),"# of nodes");

    for(int j = 0; j < 5; j++) {

        listTest->searchTrieRecursively(listTest->getRoot(),strTemp[j],1);

        if(listTest->getMismatch() != 99999999) {
            printf("%s %s %s %d %s %d\n", "found the word", strTemp[j].c_str(),
                   "with #", listTest->getMismatch(), " mismatches at index ",
                   listTest->getIndex());
        }else{

            printf("\nDidn't find it recursively lets check our search function!\nBecause it should be in the list\n");

            if(listTest->strictSearch(strTemp[j])){

                printf("\nfound the word %s\n", strTemp[j].c_str());
            }else{

                printf("\nsearch didn't find the word, our trie might be broken\nor most likely both");
            }



        }
    }

    delete listTest;
    file.close();



    // Success
    return 0;
}

