#include "hashing.h"

int next_prime(int n) {
  if(n < 3) return 3;
  else if(n % 2 == 0) n++;
  n += 2;

  bool is_prime = false;
  int sqrt_n = sqrt(n);
  while(not is_prime) {
    //asumimos que n es primo y comprobamos que no lo sea
    is_prime = true;

    for(int i = 5; i < sqrt_n and is_prime; i += 6) {
      if(n % i == 0) is_prime = false;
      else if(n % (i + 2) == 0) is_prime = false;
    }

    n += 2;
  }

  return n;
}

int hash_basic_sum(string s, int n) {
  int key = 0;
  for(int i = 0; i < s.length(); i++) {
    key += s[i] - '0';
  }
  return key % n;
}

int hash_sum(string s, int n) {
  int key = 0;
  for(int i = 0; i < s.length(); i++) {
    key *= 31;
    key += s[i] - '0';
  }
  return key % n;
}

int hash_read(string s, int n) {
  int key = stoi(s,nullptr);
  return key % n;
}

void by_bloom(Dictionary & dict, Board & board, int hash_method) {
  int found_words = 0;
  int score = 0;
  int comparisons = 0;
  int max_length = 0;
  int hashN = 0;
  vector<bool> hdict;
  int(*hash)(string,int);

  switch(hash_method) {
    //caso base es busqueda naive del siguiente primo (ver default)
    //SUM MOD NAIVE NEXT PRIME

    //caso 1 es suponiendo que haciendo de s un num en base [primo]
    //es suficiente primalidad
    //SUM OF BASE 31 DIGITS
    case 1:
      hdict = vector<bool>(board.getN(), false);
      for(int i=0; i<dict.getK(); i++) {
        hdict[hash_sum(dict.getWord(i), board.getN())] = true;
        if(dict.getWord(i).length() > max_length) max_length = dict.getWord(i).length();
      }

      hash = &hash_sum;
      break;

    //caso 2 es usando el propio numero representado para el calc del modulo
    //NUM MOD NEXT PRIME
    case 2:
      hashN = next_prime(board.getN());
      hdict = vector<bool>(hashN, false);

      for(int i=0; i<dict.getK(); i++) {
        hdict[hash_read(dict.getWord(i), hashN)] = true;
        if(dict.getWord(i).length() > max_length) max_length = dict.getWord(i).length();
      }

      hash = &hash_read;
      break;

    default:
      hashN = next_prime(board.getN());
      hdict = vector<bool>(hashN, false);

      for(int i=0; i<dict.getK(); i++) {
        hdict[hash_basic_sum(dict.getWord(i), hashN)] = true;
        if(dict.getWord(i).length() > max_length) max_length = dict.getWord(i).length();
      }

      hash = &hash_basic_sum;
      break;
  }

  vector<vector<bool> > used = vector<vector<bool> >(board.getN(), vector<bool>(board.getN(), false));

  bool found = false;

  for(int i = 0; i < board.getN(); i++) {
    for(int j = 0; i < board.getN(); j++) {
      used[i][j] = true;
      found = check_for_word(""+board.position(i,j), board, dict, hdict, board.around(i,j), used, hash, max_length);
      if(!found) used[i][j] = false;
      else {
        found = false;
        found_words++;
      }
    }
  }
}

bool check_for_word(string s, Board &board, const Dictionary &dict, const vector<bool> &hdict, vector<Board::Cell> v, vector<vector<bool> > &used, int(*hash)(string,int), const int &l) {
  bool found = false;

  if(s.length() < l) {
    for(int i = 0; i < v.size(); i++) {
      used[v[i].i][v[i].j] = true;
      found = check_for_word(s+v[i].val, board, dict, hdict, board.around(v[i].i,v[i].j), used, hash, l);
      if(!found) used[v[i].i][v[i].j] = false;
      else return found;
    }
  }

  if(hdict[hash(s,hdict.size())]) {
    return true;
  }

  return false;
}
