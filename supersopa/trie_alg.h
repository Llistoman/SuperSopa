#ifndef TRIE_ALG_H
#define TRIE_ALG_H

#include <iostream>
#include "dictionary.h"
#include "board.h"
#include "trie.h"
#include <stack>

using namespace std;

bool check_for_word(Trie* trie, string word, Board &board, Dictionary &dict, vector<Board::Cell> adj, vector<vector<bool> > &used, const int &l);

void trie_alg(Dictionary & dictionary, Board & board);

#endif // TRIE_ALG_H
