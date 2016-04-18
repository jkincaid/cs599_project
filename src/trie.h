//
// Created by chaos on 4/14/2016.
//

#ifndef CS599_PROJECT_TRIE_H
#define CS599_PROJECT_TRIE_H

#include <string>
#include "node.h"

using namespace std;

/* TODO: exhaustive search
 * Return the query and number of mismatches
 */
class Trie
{
    public:
        // Constructor/Deconstructor
        Trie();
        ~Trie();

        // Prototypes
        void addQuery(string query);
        int searchTrie(string subject);
        void searchTrieRecursively(Node* current, string subject, int limit, int currentMismatch = 0, int subjectIndex = 0);
        int getMismatch() { return this->bestMismatch; };
        int getIndex() { return this->bestIndex; };
        Node* getRoot() { return this->root; };
        
    private:
        Node* root;
        int bestIndex;
        int bestMismatch;
        int numberOfQuerys;
};



#endif //CS599_PROJECT_TRIE_H
