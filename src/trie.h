//
// Created by chaos on 4/14/2016.
//

#ifndef CS599_PROJECT_TRIE_H
#define CS599_PROJECT_TRIE_H

#include <string>
#include "node.h"


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
        struct map {
            int index;
            std::vector<int> mismatches;
        };

        struct nodeMismatch {
            Node* node;
            std::vector<int>* mismatches;
        };
        void addQuery(std::string query);
        int searchTrie(std::string subject);
        std::vector<map> searchTrieRecursively(std::string subject, int limit);
        bool strictSearch(std::string subject);
        int getMismatch() { return this->bestMismatch; };
        int getIndex() { return this->bestIndex; };
        Node* getRoot() { return this->root; };
        int getSize() {return this->numberOfNodes;}
        
    private:
        Node* root;
        int bestIndex;
        int bestMismatch;
        int numberOfQuerys;
        int numberOfNodes;      //keep track
};



#endif //CS599_PROJECT_TRIE_H
