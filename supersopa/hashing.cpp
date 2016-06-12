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
  for(int i = 0; i < s.length; i++) {
    key += s[i] - '0';
  }
  return key % n;
}

int hash_sum(string s, int n) {
  int key = 0;
  for(int i = 0; i < s.length; i++) {
    key *= 31;
    key += s[i] - '0';
  }
  return key % n;
}

int hash_read(string s, int n) {
  int key = stoi(s,nullptr);
  return key % n;
}

void by_bloom(Dictionary & dictionary, Board & board, int hash_method) {
  int found = 0;
  int score = 0;
  int comparisons = 0;
  vector<bool> hdictionary;

  switch(hash_method) {
    //caso base es busqueda naive del siguiente primo (ver default)

    //caso 1 es suponiendo que haciendo de s un num en base [primo]
    //es suficiente primalidad
    case 1:
      hdictionary = vector<bool>(board.getN(), false);
      for(int i=0; i<hdictionary.size; i++)
        hdictionary[hash_sum(dictionary[i], board.getN())] = true;
      break;

    //caso 2 es usando el propio numero representado para el calc del modulo
    case 2:
      int hashN = 3;
      hashN = next_prime(board.getN());
      hdictionary = vector<bool>(hashN, false);

      for(int i=0; i<hdictionary.size; i++)
        hdictionary[hash_read(dictionary[i], hashN)] = true;
      break;

    default:
      int hashN = 3;
      hashN = next_prime(board.getN());
      hdictionary = vector<bool>(hashN, false);

      for(int i=0; i<hdictionary.size; i++)
        hdictionary[hash_basic_sum(dictionary[i], hashN)] = true;
      break;
  }

  vector<vector<bool> > used = vector<vector<bool> >(board.getN(), vector<bool>(board.getN(), false));

  for(int i = 0; i < board.getN(); i++) {
    for(int j = 0; i < board.getN(); j++) {
      //do shit
    }
  }
}
