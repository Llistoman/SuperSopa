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
        newNode->isLeaf = false;
        newNode->children = vector<Node*>(10, NULL);
    }
    return newNode;

}

bool Trie::isPrefix(string str)
{
    Node* n = root;
    for(int i=0; i<str.size();i++)
    {
        if(n->children[str[i]-'0'] == NULL) {
            return false;
          }
        n=n->children[str[i]-'0'];
    }

    return (n != NULL);
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
    for(int i=0; i<str.size(); i++)
    {
        if(ptr->children[str[i]-'0'] != NULL) {
            ptr=ptr->children[str[i]-'0'];
          }
        else
        {
            Node *newNode=createNode();
            ptr->children[str[i]-'0']=newNode;
            ptr=newNode;
        }
    }
    ptr->isLeaf=true;
}
bool Trie::search(Node *n, string str)
{
    for(int i=0; i<str.size(); i++)
    {
        if(n->children[str[i]-'0'] == NULL)
            return false;
        n=n->children[str[i]-'0'];
    }
    return (n!=NULL) && n->isLeaf;
}
bool Trie::isFree(Node *n)
{
    for(int i=0;i<10;i++)
        if(n->children[i] != NULL)
            return false;
    return true;
}
bool Trie::deleteStr(Node *n, string str, int level)
{
    if(n != NULL)
    {
        if(level==str.size())
        {
            if(n->isLeaf and isFree(n))
            {
                n->isLeaf=false;
                return true;
            }
            return false;
        }

        int key=str[level];
        if(deleteStr(n->children[key-'0'],str,level+1))
        {
            delete n->children[key-'0'];
            n->children[key-'0'] = NULL;
            if(isFree(n))
            {
                return true;
            }
        }
        return false;
    }
    return true;
}
