#include "trie.h"

Node::Node() {
     mContent = ' '; mMarker = false;
}

Node::~Node() {
  //free space
}

char Node::content() {
   return mContent;
}

void Node::setContent(char c) {
    mContent = c;
}

bool Node::wordMarker() {
    return mMarker;
}

void Node::setWordMarker() {
    mMarker = true;
}

void Node::unsetWordMarker() {
    mMarker = false;
}

void Node::appendChild(Node *child) {
    mChildren.push_back(child);
}

vector<Node*> Node::children() {
    return mChildren;
}

Node* Node::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

void Node::deleteChild(Node* child) {
    int i = 0;
    while(i<mChildren.size() and mChildren[i] != child) i++;
    while(i<mChildren.size()-1) mChildren[i] = mChildren[i+1];
    Node* tmp = mChildren.back();
    delete tmp;
    tmp = NULL;
    mChildren.pop_back();
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addWord(string s)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}

bool Trie::isPrefix(string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }
        return true;
    }
}


bool Trie::searchWord(string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() )
            return true;
        else
            return false;
    }

    return false;
}

bool deleteHelper(Node *current, string s, int level, int l)
{
    if (current != NULL) {
        if (level == l) {
            if (current->wordMarker()) {
                current->unsetWordMarker();
                if (current->children().size() == 0) return true;
                else return false;
            }
        }
        else {
            Node *child = current->findChild(s[level]);
            if(deleteHelper(child,s,level+1,l)) {
                return (current->children().size() <= 0);
            }
        }
    }
}

void Trie::deleteWord(string s)
{
    int l = s.size();
    if(l > 0) deleteHelper(root,s,0,l);
}
