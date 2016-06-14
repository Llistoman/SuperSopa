#include "trie.h"

Trie::Trie()
{
    root = createNode();
}

Trie::~Trie()
{

}

Trie::Node * Trie::createNode()
{
    Node *newNode=new Node;
    if(newNode)
    {
        newNode->isLeaf=false;
        for(int i=0;i<10;i++)
            newNode->children[i]=NULL;
    }
    return newNode;

}

bool Trie::searchPrefix(Node *n, string str)
{
    for(auto it=str.begin();it!=str.end();it++)
    {
        if(!n->children[*it-'0'])
            return false;
        n=n->children[*it-'0'];
    }
    return true;
}

bool Trie::isPrefix(string str)
{
    return searchPrefix(root,str);
}

void Trie::addWord(string str)
{
    insert(root,str);
}

bool Trie::searchWord(string str)
{
    return search(root,str);
}

bool Trie::deleteWord(string str)
{
    return deleteStr(root,str,0);
}

void Trie::insert(Node *n, string str)
{
    Node *ptr=n;
    for(auto it=str.begin();it!=str.end();it++)
    {
        if(ptr->children[*it-'0'])
            ptr=ptr->children[*it-'0'];
        else
        {
            Node *newNode=createNode();
            ptr->children[*it-'0']=newNode;
            ptr=newNode;
        }
    }
    ptr->isLeaf=true;
}
bool Trie::search(Node *n, string str)
{
    for(auto it=str.begin();it!=str.end();it++)
    {
        if(!n->children[*it-'0'])
            return false;
        n=n->children[*it-'0'];
    }
    return n && n->isLeaf;
}
bool Trie::isFree(Node *n)
{
    for(int i=0;i<10;i++)
        if(n->children[i])
            return false;
    return true;
}
bool Trie::deleteStr(Node *n, string str,int level)
{
    if(n)
    {
        if(level==str.length())
        {
            n->isLeaf=false;
            if(isFree(n))
            {
                delete n;
                return true;
            }
            return false;
        }

        int key=str[level];
        if(deleteStr(n->children[key-'0'],str,level+1))
        {
            if(!n->isLeaf)
            {
                delete n;
                return true;
            }
            else
                return false;
        }

    }
    return false;
}
