#ifndef HASHING_H
#define HASHING_H

#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include "dictionary.h"
#include "board.h"

using namespace std;

int next_prime(int n);
int hash_basic_sum(string s, int n);
int hash_sum(string s, int n);
int hash_read(string s, int n);
void by_bloom(Dictionary & dictionary, Board & board);
bool check_for_word(string s, Board &board, const Dictionary &dict, const vector<bool> &hdict, vector<Board::Cell> v, vector<vector<bool> > &used, int(*hash)(string,int), const int &l);

#endif // HASHING_H
