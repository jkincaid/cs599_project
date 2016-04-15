//
// Created by chaos on 4/14/2016.
//

#include "trie.h"

// Constructor --> create an empty root
Trie::Trie()
{
    root = new Node();
}

// Deconstructor --> free memory
Trie::~Trie() {}


/* Input: string
 * Function: adds a query to the trie
 * Output: void
 */
void Trie::addQuery(string query)
{

    // Start at root
    Node* current = root;

    // Word is empty, immediate marker
    if ( query.length() == 0 )
    {
        current->setWordMarker();
        return;
    }

    // Go until end of query
    for ( int i = 0; i < query.length(); i++ )
    {

        // Check if there's already a child (base) to go to
        Node* child = current->findChild(query[i]);

        // Child was found, go to it
        if ( child != NULL )
        {
            current = child;
        }

            // No child was found, create one
        else
        {
            Node* tmp = new Node();
            tmp->setContent(query[i]);
            current->appendChild(tmp);
            current = tmp;
        }

        if ( i == query.length() - 1 )
            current->setWordMarker();
    }
}


/* Input: string (subject)
 * Function: attempts to fuzzy match subject to all queries up to X mismatches
 * Output: best query and score
 */
bool Trie::searchTrie(string subject)
{

    // Start at root
    Node* current = root;

    // Go until end of trie
    while ( current != NULL )
    {

        // Go until end of subject length
        for ( int i = 0; i < subject.length(); i++ )
        {

            // Try to find child with current base of subject
            Node* tmp = current->findChild(subject[i]);

            // Child is dead end for matching
            if ( tmp == NULL )
                return false;

            // Move to child
            current = tmp;
        }

        // Found everything up until end of word --> success
        if ( current->wordMarker() )
            return true;

            // Dead end
        else
            return false;
    }

    // Failure
    return false;
}
/* 
 * This function will recursively search the prefix tree for the given subject,
 * Inputs: 
 *      Node* current       : A pointer to the root node
 *      string subject      : The subject we are searching for
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
void Trie::searchTrieRecursively(Node* current, string subject, int limit, int* bestMismatch, int* bestIndex, int currentMismatch = 0, int subjectIndex = 0)
{
    // Base case 1: End of the Query
    // If we have gotten to this point we know that this is better then our current best
    // - So update values in the memory addresses given by pointers
    if(current->wordMarker() != 0)
    {
        *bestMismatch = currentMismatch;
        *bestIndex = current->wordMarker();
        return;
    }
    
    // Check if the content of this node matches our subject as long as current node
    // is not the root node
    // - if not then increment the mismatch counter
    if(current->getContent() != subject[subjectIndex] && *current != this->*root)
    {
        best_path = best_path.substr(0, end-1)
        return
        currentMismatch++;
    }
    
    // Base case 2: Number of current mismatches is greater then limit or
    // current mismatches is not better then our best
    // - So we just end this path by returning
    if(currentMismatch > limit || currentMismatch >= *bestMismatch) 
    {
        return;
    }

    // If this node is not the root, then increment the subjectIndex by one, as
    // we are going to check the next base in the subject. 
    if(*currentNode != this->*root) 
    {
        subjectIndex++;
    }
    
    // Then, for each child of the current node, call this method
    // on the child. After, decrement the subject index
    for(int i=0; i<(current->children.size()); i++)
    {
        searchTrieRecursively(current->children[i], subject, limit, bestMismatch, bestIndex, currentMismatch, subjectIndex);
    }
}