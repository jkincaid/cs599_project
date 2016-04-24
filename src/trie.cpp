//
// Created by chaos on 4/14/2016.
//

#include "trie.h"
#include <iostream>
#include <stack>

// Constructor --> create an empty root
Trie::Trie()
{
    root = new Node();
    root->setIndexMarker(-1);
    numberOfQuerys = 0;
    bestMismatch = 99999999;
    bestIndex = -1;
    numberOfNodes =0;
}

// Deconstructor --> free memory
Trie::~Trie() {}

/* Input: std::string

 * Function: adds a query to the trie
 * Output: void
 */
void Trie::addQuery(std::string query)
{

    // Start at root
    Node* current = root;

    // Word is empty, immediate marker
    if ( query.length() == 0 )
    {
        return;
    }
    // Go until end of query
    for ( unsigned int i = 0; i < query.length(); i++ )
    {

        // Check if there's already a child (base) to go to
        Node* child = current->findChild(query[i]);

        // Child was found, go to it
        if ( child->getIndexMarker() != -1 )
        {
            current = child;
        }

        // No child was found, create one
        else
        {
            Node* tmp = new Node();
            tmp->setIndexMarker(0);
            tmp->setContent(query[i]);
            current->appendChild(tmp);
            current = tmp;
            this->numberOfNodes++;          // keep track of size of the tree i.e how many nodes

        }

        if ( i == query.length() - 1 ) {
            this->numberOfQuerys++;
            current->setIndexMarker(this->numberOfQuerys);
        }
    }
    
}


/* Input: std::string subject
 * Function: attempts to strict search for subject to all queries
 * Output: int index of read
 */
int Trie::searchTrie(std::string subject)
{
    // Start at root
    Node* current = root;

    // Go until end of trie
    while ( current != NULL )
    {

        // Go until end of subject length
        for ( unsigned int i = 0; i < subject.length(); i++ )
        {

            // Try to find child with current base of subject
            Node* tmp = current->findChild(subject[i]);

            // Child is dead end for matching
            if ( tmp->getIndexMarker() == -1 ) { return false; };

            // Move to child
            current = tmp;
        }

        // Found everything up until end of word --> success
        if ( current->getIndexMarker() != 0 ) { return current->getIndexMarker(); }

        // Dead end
        else { return -1; }
    }

    // Failure
    return false;
}
/* 
 * This function will recursively search the prefix tree for the given subject,
 * Inputs: 
 *      std::string subject      : The subject we are searching for
 *      int limit                : The maximum allowable number of mismatches (inclusive)
 * Outputs:
 *      vector<map>              : A vector of maps
 *                                      
 */

std::vector<Trie::map> Trie::searchTrieRecursively(std::string subject, int limit)
{
    std::vector<Trie::map> returned;
    std::stack<Trie::nodeMismatch> s;
    Trie::nodeMismatch nm;
    for (Node* child : this->root->children()) {
        nm.node = child;
        nm.mismatches = new std::vector<int>;
        s.push(nm);
    }
    
    while (!s.empty()) {
        nm = s.top();
        std::vector<int> currentMismatch = *nm.mismatches;
        
        // Mismatch increment
        if (subject[nm.mismatches->size()] != nm.node->getContent()) {
            currentMismatch.push_back(1);
            int totalMismatch = 0;
            for(int i : currentMismatch) {
                if (i != 0) totalMismatch++;
            }
            if (totalMismatch > limit) continue;
        }
        
        // Reached end
        if(nm.node->getIndexMarker() != 0) {
            Trie::map map;
            map.index = nm.node->getIndexMarker();
            map.mismatches = currentMismatch;
            returned.push_back(map);
            continue;
        }
        
        // Adds children to stack
        for (Node* child : nm.node->children()) {
            nm.node = child;
            nm.mismatches = &currentMismatch;
            s.push(nm);
        }
        
    }
    
    return returned;
}
