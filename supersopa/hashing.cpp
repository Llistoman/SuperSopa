#include "hashing.h"

int next_prime(int n) {
  cout << "Start prime search" << endl;
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

  cout << "End prime search" << endl;
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

int custom_hash(string s, int n, int m) {
  switch(m) {
    //caso base es busqueda naive del siguiente primo (ver default)
    //SUM MOD NAIVE NEXT PRIME

    //caso 1 es suponiendo que haciendo de s un num en base [primo]
    //es suficiente primalidad
    //SUM OF BASE 31 DIGITS
    case 1:
      return hash_sum(s, n);

    //caso 2 es usando el propio numero representado para el calc del modulo
    //NUM MOD NEXT PRIME
    case 2:
      return hash_read(s, n);

    default:
      return hash_basic_sum(s, n);
  }
}

void by_bloom(Dictionary & dict, Board & board, int hash_method) {
  int found_words = 0;
  int score = 0;
  int comparisons = 0;
  int max_length = 0;
  int hashN = 0;
  vector<int> hdict;

  const clock_t begin = clock();
  cout << "Hashing method used: ";

  switch(hash_method) {
    //caso base es busqueda naive del siguiente primo (ver default)
    //SUM MOD NAIVE NEXT PRIME

    //caso 1 es suponiendo que haciendo de s un num en base [primo]
    //es suficiente primalidad
    //SUM OF BASE 31 DIGITS
    case 1:
      hdict = vector<int>(board.getN(), 0);
      cout << "SUM OF BASE 31 DIGITS" << endl;
      break;

    //caso 2 es usando el propio numero representado para el calc del modulo
    //NUM MOD NEXT PRIME
    case 2:
      hashN = next_prime(board.getN());
      hdict = vector<int>(hashN, 0);
      cout << "NUM MOD [NAIVE NEXT PRIME]" << endl;
      break;

    default:
      hashN = next_prime(board.getN());
      hdict = vector<int>(hashN, 0);
      cout << "SUM MOD [NAIVE NEXT PRIME]" << endl;
      break;
  }
  cout << "Start hdict initialization" << endl;

  for(int i=0; i<dict.getK(); i++) {
    hdict[custom_hash(dict.getWord(i), hdict.size(), hash_method)]++;
    if(dict.getWord(i).length() > max_length) max_length = dict.getWord(i).length();
  }
  cout << "End hdict initialization" << endl;

  vector<vector<bool> > used = vector<vector<bool> >(board.getN(), vector<bool>(board.getN(), false));

  bool found = false;
  cout << "Start word checking" << endl;
  string word = "";

  for(int i = 0; i < board.getN(); i++) {
    for(int j = 0; i < board.getN(); j++) {
      used[i][j] = true;
      cout << "Checking position: (" << i << ", " << j << ")" << endl;
      word = board.position(i,j);
      found = check_for_word(word, board, dict, hdict, board.around(i,j), used, hash_method, max_length);
      if(!found) used[i][j] = false;
      else {
        found = false;
        found_words++;
      }
    }
  }

  const clock_t end = clock();
  int time = int(end - begin) / CLOCKS_PER_SEC;
  cout << endl;
  cout << "Time spent: " << time/60 << " minutes " << time%60 << " seconds" << endl;
  cout << "Found: " << found_words  << " out of " << dict.getK() << " total words" << endl;
  cout << "Score: " << score << endl;
  cout << "Comparisons: " << comparisons << endl;
  cout << "---------------" << endl;
}

bool check_for_word(string word, Board &board, Dictionary &dict, vector<int> &hdict, vector<Board::Cell> v, vector<vector<bool> > &used, const int &hash_method, const int &l) {
  bool found = false;
  string s = "";
  cout << "Checking word: " << word << endl;

  if(s.length() < l) {
    for(int i = 0; i < v.size(); i++) {
      if(not used[v[i].i][v[i].j]) {
        used[v[i].i][v[i].j] = true;
        s = word + v[i].val;
        found = check_for_word(s, board, dict, hdict, board.around(v[i].i,v[i].j), used, hash_method, l);
        if(!found) used[v[i].i][v[i].j] = false;
        else return found;
      }
    }
  }

  if(hdict[custom_hash(s, hdict.size(), hash_method)] > 0) {
    found = search_word(s, dict);
    if(found) {
      hdict[custom_hash(s, hdict.size(), hash_method)]--;
    }
    return found;
  }

  return false;
}

bool search_word(string s, Dictionary &dict) {
  cout << "Possible word found: " << s << endl;
  for(int i=0; i<dict.getK(); i++) {
    if(s == dict.getWord(i)) {
      dict.getWord(i) = "";
      return true;
    }
  }

  return false;
}
