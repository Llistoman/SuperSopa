#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>

using namespace std;


class Trie {

    struct Node
    {
        Node *children[9];
        bool isLeaf;
    };

private:
    Node *root;

public:

    Trie();
    ~Trie();
    Node *createNode();
    bool searchPrefix(Node *n, string str);
    bool isPrefix(string str);
    void addWord(string str);
    bool searchWord(string str);
    bool deleteWord(string str);
    void insert(Node *n, string str);
    bool search(Node *n, string str);
    bool isFree(Node *n);
    bool deleteStr(Node *n, string str,int level);
};

#endif // TRIE_H
