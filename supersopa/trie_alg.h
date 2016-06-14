#ifndef TRIE_ALG_H
#define TRIE_ALG_H

#include <iostream>
#include "dictionary.h"
#include "board.h"
#include "trie.h"
#include <stack>

using namespace std;

void trie_alg(Dictionary & dictionary, Board & board, Board::Stats & stats);
bool check_for_word(Trie &trie, string word, Board &board, vector<Board::Cell> adj, vector<vector<bool> > &used, const int &l, Board::Stats &stats);

#endif // TRIE_ALG_H
