#include "hashing.h"

int hash_sum(string s, int n) {
  int key = 0;
  for(int i = 0; i < s.length; i++) {
    key += s[i] - '0';
  }
  return key % n;
}

int hash_read(string s, int n) {
  int key = stoi(s,nullptr);
  return key % n;
}

void by_bloom(Dictionary & dictionary, Board & board) {
  int found = 0;
  int score = 0;
  int comparisons = 0;
  int hashN = 3;

  vector<bool> hdictionary = vector<bool>(dictionary.getK, false);

  if(dictionary.getN() > hashN) hashN = dictionary.getN();

  for(int i=0; i<hdictionary.size; i++) {
    hdictionary[hash(dictionary[i])] = true;
  }
}
