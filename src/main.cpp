#include <iostream>
#include "trie.h"

using namespace std;

// Test program
int main()
{
	// Create trie
    Trie* trie = new Trie();
    
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
    
    // Success
    return 0;
}

