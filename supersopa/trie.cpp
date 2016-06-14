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

bool Trie::searchPrefix(Node *root, string str)
{
    for(auto it=str.begin();it!=str.end();it++)
    {
        if(!root->children[*it-'0'])
            return false;
        root=root->children[*it-'0'];
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

void Trie::insert(Node *root, string str)
{
    Node *ptr=root;
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
bool Trie::search(Node *root, string str)
{
    for(auto it=str.begin();it!=str.end();it++)
    {
        if(!root->children[*it-'0'])
            return false;
        root=root->children[*it-'0'];
    }
    return root && root->isLeaf;
}
bool Trie::isFree(Node *n)
{
    for(int i=0;i<10;i++)
        if(n->children[i])
            return false;
    return true;
}
bool Trie::deleteStr(Node *root, string str,int level)
{
    if(root)
    {
        if(level==str.length())
        {
            root->isLeaf=false;
            if(isFree(root))
            {
                delete root;
                return true;
            }
            return false;
        }

        int key=str[level];
        if(deleteStr(root->children[key-'0'],str,level+1))
        {
            if(!root->isLeaf)
            {
                delete root;
                return true;
            }
            else
                return false;
        }

    }
    return false;
}
