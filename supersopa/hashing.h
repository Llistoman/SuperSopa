#ifndef HASHING_H
#define HASHING_H

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "dictionary.h"
#include "board.h"

using namespace std;

int next_prime(int n);
int hash_basic_sum(string s, int n);
int hash_sum(string s, int n);
int hash_read(string s, int n);
void by_bloom(Dictionary & dictionary, Board & board, int hash_method, Board::Stats & stats, int tiempo);
bool check_for_word(string s, Board &board, Dictionary &dict, vector<int> &hdict, vector<Board::Cell> v, vector<vector<bool> > &used, const int &prime, const int &hash_method, const int &l, Board::Stats & stats);
bool search_word_h(string s, Dictionary &dict);

#endif // HASHING_H
