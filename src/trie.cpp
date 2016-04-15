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

// TODO Translate method from pseudocode to C++
// TODO Add parameter to function called currentMismatch (keeps track of current mismatches) w/ default value 0
// TODO Add parameter for bestMismatches *pointer* that fills out info
void Trie::searchTrieRecursively(Node* current, string subject)
{
    if(current->endQuery)
    {
        if(mismatches < best_mismatches)
        {
            best_mismatches = mismatches;
            best_path = current_path;
        }
    }

    /* TODO Fix block conditions:
     * If currentMismatches > bestMismatch OR
     * if currentMismatches > tolerance
     */
    if(mismatches > tolerance && mismatches > best_mismatches)
    {
        best_path = best_path.substr(0, end-1)
        return
    }

    if(current->getContent() != subject[index])
    {
        mismatches++;
    }

    index++;
    for(int i=0; i<(current->children.size()); i++)
    {
        searchTrieRecursively(current->children[i], subject)
    }

    current_path = current_path.substr(0, current_path.length() - 1);
    index--;
}