//
// Created by chaos on 4/14/2016.
//

#include "trie.h"
#include <iostream>
#include <c++/queue>

// Constructor --> create an empty root
Trie::Trie()
{
    root = new Node();
    root->setIndexMarker(-1);
    numberOfQuerys = 0;

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


/* Input: std::string
  (subject)
 * Function: attempts to fuzzy match subject to all queries up to X mismatches
 * Output: best query and score
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
 *      Node* current       : A pointer to the root Node
 *      std::st *     subject      : The subject we are searching for
 *      int limit           : The maximum allowable number of mismatches (inclusive)
 *      int* bestMatch      : A pointer to our least amount of mismatches for our
 *                            best query. Initialized to our limit + 1
 *      int* bestIndex      : A pointer to the index of the best query so far.
 *                            Initialized to any value (preferably 0)
 *      int currentMismatch : Default value of the current number of mismatches.
 *      int subjectIndex    : Default value of what base in the subject we are
 *                            trying to match. 
 * Outputs:
 *      Updates values of:
 *          int* bestMismatch
 *          int* bestIndex               
 */
void Trie::searchTrieRecursively(Node* current, std::string subject, int limit, int currentMismatch, int subjectIndex)
{
    // Check if the content of this Node matches our subject as long as current Node
    // is not the root Node
    // - if not then increment the mismatch counter
    if(current->getContent() != subject[subjectIndex] && current->getIndexMarker() != -1)
    {
        currentMismatch++;
        this->mismatchIndices.push_back(subjectIndex);
    }
    
    // Base case 1: Number of current mismatches is greater then limit
    // - So we just end this path by returning

    if(currentMismatch > limit)
    {
        this->mismatchIndices.pop_back();
        return;
    }
    
    // Base case 2: End of the Query
    // If we have gotten to this point we know that this is better then our current best
    // - So update values in the memory addresses given by pointers
    if(current->getIndexMarker() != 0 && current->getIndexMarker() != -1)
    {
        this->bestMismatch = currentMismatch;
        this->bestIndex = current->getIndexMarker();
        this->solution_dictionary.emplace(this->bestIndex,this->mismatchIndices);
        this->mismatchIndices.pop_back();
        return;
    }    

    // If this Node is not the root, then increment the subjectIndex by one, as
    // we are going to check the next base in the subject. 
    if(current->getIndexMarker() != -1) 
    {
        subjectIndex++;
    }
    
    // Then, for each child of the current Node, call this method
    // on the child. After, decrement the subject index
    for(unsigned int i=0; i<(current->children().size()); i++)
    {
        searchTrieRecursively(current->children().at(i), subject, limit, currentMismatch, subjectIndex);
    }
    this->mismatchIndices.pop_back();
    return;
}

//return the results and clear old indices
std::map<int,std::vector<int>> Trie::getResults() {

    return solution_dictionary;

}

void Trie::searchWithMismatch(std::string subject) {


    std::queue<Node*> treeNodes;

    Node* current = root;

    treeNodes.push(current);



    while(!treeNodes.empty()){

        Node* tmp = treeNodes.front();
        treeNodes.pop();

        for(Node* n : tmp->getChildren()){

            treeNodes.push(n);

            numberOfNodes++;

        }


}

