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
        bool searchTrie(string subject);

    private:
        Node* root;
};



#endif //CS599_PROJECT_TRIE_H
