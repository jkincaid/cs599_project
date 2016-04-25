//
// Created by chaos on 4/14/2016.
//

#ifndef CS599_PROJECT_TRIE_H
#define CS599_PROJECT_TRIE_H

#include <string>
#include <c++/map>
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
        void addQuery(std::string query);
        int searchTrie(std::string subject);
        void searchTrieRecursively(Node* current, std::string subject, int limit, int currentMismatch = 0, int subjectIndex = 0);
        int getMismatch() { return this->bestMismatch; };
        int getIndex() { return this->bestIndex; };
        Node* getRoot() { return this->root; };
        int getSize() {return this->numberOfNodes;}
        std::map<int,std::vector<int>> getResults();
        void searchWithMismatch(std::string subject);
        
    private:
        Node* root;
        int bestIndex;
        int bestMismatch;
        int numberOfQuerys;
        int numberOfNodes;      //keep track
        std::vector<int> mismatchIndices;
        std::map<int,std::vector<int>> solution_dictionary;
};



#endif //CS599_PROJECT_TRIE_H
