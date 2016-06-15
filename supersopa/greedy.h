#ifndef GREEDY_H
#define GREEDY_H

#include <iostream>
#include "dictionary.h"
#include "board.h"
#include <stack>

using namespace std;

void greedy(Dictionary & dictionary, Board & board, Board::Stats & stats, int tiempo);
bool check_for_word(Dictionary &dict, string word, Board &board, vector<Board::Cell> adj, vector<vector<bool> > &used, const int &l, Board::Stats &stats, const int &tiempo, clock_t &aux);
bool search_prefix(string s, Dictionary &dict);
bool search_word_g(string s, Dictionary &dict);

#endif // GREEDY_H
