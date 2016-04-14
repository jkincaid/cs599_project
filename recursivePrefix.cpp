#include <iostream>
#include <vector>
using namespace std;


/* TODO: exhaustive search
 * Return the query and number of mismatches
 */
 
class Node 
{
public:
	// Constructor
    Node() 
	{ 
		content = ' '; 
		endQuery = false; 
	}
    
    // Deconstructor
    ~Node() {}
        
    // Return base
    char getContent() { return content; }
	
	// Set base
    void setContent(char base) { content = base; }
	
	// True if query ends at current node, false otherwise
    bool wordMarker() { return endQuery; }
	
	// Set true if end query, naturally false
    void setWordMarker() { endQuery = true; }
	
	// Add a child to the current node's vector
	void appendChild(Node* child) { nodeChildren.push_back(child); } // push_back == append
	
	// Prototype
    Node* findChild(char base);
    
    // Returns vector of children if found
    vector<Node*> children() { return nodeChildren; }

private:
	
	// Single base
    char content;
    
    // True if query ended
    bool endQuery;
    
    // Dynamic-size array that holds all children
    vector<Node*> nodeChildren;
};


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


/* Input: char (base)
 * Function: checks if a certain base exists for the current node
 * Output: pointer to the node found (child)
 */
Node* Node::findChild(char base)
{
	
	// Goes through every child
    for ( int i = 0; i < nodeChildren.size(); i++ )
    {
    	// Current node is the child
        Node* tempChild = nodeChildren.at(i);
        
        // Child matched the content
        if ( tempChild->getContent() == base )
        {
        	
        	// Return child
            return tempChild;
        }
    }

    return NULL;
}


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

