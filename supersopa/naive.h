#ifndef NAIVE_H
#define NAIVE_H

#include <iostream>
#include "dictionary.h"
#include "board.h"
#include <stack>

using namespace std;

void naive(Dictionary & dictionary, Board & board, Board::Stats & stats,int tiempo);
bool check_for_word(string &word, int index, Board &board, vector<Board::Cell> adj, vector<vector<bool> > &visited, stack<pair<int,int> > &pos, Board::Stats &stats, const int &tiempo, clock_t &aux);

#endif // NAIVE_H
