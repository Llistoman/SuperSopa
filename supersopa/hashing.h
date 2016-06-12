#ifndef HASHING_H
#define HASHING_H

#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

int next_prime(int n);
int hash_basic_sum(string s, int n);
int hash_sum(string s, int n);
int hash_read(string s, int n);
void by_bloom(Dictionary & dictionary, Board & board);
