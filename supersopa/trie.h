#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>

using namespace std;


class Trie {

    struct Node
    {
        vector<Node*> children;
        bool isLeaf;
    };

private:
    Node *root;

public:

    Trie();
    ~Trie();
    Node *createNode();
    bool isPrefix(string str);
    void addWord(string str);
    bool searchWord(string str);
    bool deleteWord(string str);
    void insert(Node *n, string str);
    bool search(Node *n, string str);
    bool isFree(Node *n);
    bool deleteStr(Node *n, string str,int level);
    bool empty();
};

#endif // TRIE_H
