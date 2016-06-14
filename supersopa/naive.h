#ifndef NAIVE_H
#define NAIVE_H

#include <iostream>
#include "dictionary.h"
#include "board.h"
#include <stack>

using namespace std;

void naive(Dictionary & dictionary, Board & board, Board::Stats & stats);
bool check_for_word(string &word, int index, Board &board, vector<Board::Cell> adj, vector<vector<bool> > &visited, stack<pair<int,int> > &pos, Board::Stats &stats);

#endif // NAIVE_H
