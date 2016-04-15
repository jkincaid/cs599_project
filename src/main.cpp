#include <iostream>
#include "trie.h"

using namespace std;

// Test program
int main()
{
	// Create trie
    Trie* trie = new Trie();
    
    // Add queries
    trie->addQuery("ACTGTATCGATCGCTGTTACGTCGCTATATCGACTACGTACGATCGACGTACGACTAGCTAGCTCGAT6CGATCGACGATCGATCGATCGATGCAGCATGCATCGACTGACTGATCGATCGATCGATCGATCGACTTTTACGATCGCATCGATCGCACGTACTGATCGACTAGCTACGATG");
    trie->addQuery("ACTGACTGATCGATCGATCGATGCTACTACCTACTATCTACGACTGCTCGATCGATCGTACGATCG");
    trie->addQuery("CGATCGATCGATCGATCGTCGCTACGAT");

	// Search for subject
    if ( trie->searchTrie("CGATCGATCGATCGATCGTCGCTACGA") )
        cout << "Found CGATCGATCGATCGATCGTCGCTACGA" << endl;

	// Free memory because we are good people
    delete trie;
    
    // Success
    return 0;
}

