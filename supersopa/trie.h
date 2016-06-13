#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>

using namespace std;

class Node {

private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;

public:
    Node();
    ~Node();
    char content();
    void setContent(char c);
    bool wordMarker();
    void setWordMarker();
    void unsetWordMarker();
    Node* findChild(char c);
    void appendChild(Node* child);
    vector<Node*> children();
    void deleteChild(Node* child);
};

class Trie {

private:
    Node* root;

public:
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s);
    bool isPrefix(string s);
    void deleteWord(string s);
};

#endif // TRIE_H
