//
// Created by chaos on 4/14/2016.
//

#ifndef CS599_PROJECT_NODE_H
#define CS599_PROJECT_NODE_H

#include <vector>

using namespace std;

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
        // TODO Change endQuery to an integer that keeps track of line of query in file.
        bool endQuery;

        // Dynamic-size array that holds all children
        vector<Node*> nodeChildren;
};


#endif //CS599_PROJECT_NODE_H
