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
  for(int i = 0; i < s.size(); i++) {
    key += s[i] - '0';
  }
  return key % n;
}

int hash_sum(string s, int n) {
  int key = 0;
  for(int i = 0; i < s.size(); i++) {
    key *= 31;
    key += s[i] - '0';
  }
  return key % n;
}

int hash_read(string s, int n) {
  int key = stoi(s,nullptr,10);
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

void by_bloom(Dictionary & dictionary, Board & board, int hash_method, Board::Stats & stats) {
  int max_length = 0;
  int hashN = 0;
  int repetitions = 0;
  Dictionary dict = dictionary;
  vector<int> hdict;

  stats.clock_begin = clock();
  cout << "Hashing method used: ";

  switch(hash_method) {
    //caso base es busqueda naive del siguiente primo (ver default)
    //SUM MOD NAIVE NEXT PRIME

    //caso 1 es suponiendo que haciendo de s un num en base [primo]
    //es suficiente primalidad
    //SUM OF BASE 31 DIGITS
    case 1:
      hdict = vector<int>(dictionary.getRange().second - dictionary.getRange().first, 0);
      cout << "SUM OF BASE 31 DIGITS" << endl;
      break;

    //caso 2 es usando el propio numero representado para el calc del modulo
    //NUM MOD NEXT PRIME
    case 2:
      hashN = next_prime(dictionary.getRange().second - dictionary.getRange().first);
      hdict = vector<int>(hashN, 0);
      cout << "NUM MOD [NAIVE NEXT PRIME]" << endl;
      cout << "Chosen prime: " << hashN << endl;
      break;

    default:
      hashN = next_prime(dictionary.getRange().second - dictionary.getRange().first);
      hdict = vector<int>(hashN, 0);
      cout << "SUM MOD [NAIVE NEXT PRIME]" << endl;
      cout << "Chosen prime: " << hashN << endl;
      break;
  }

  for(int i=0; i<dict.getK(); i++) {
    hdict[custom_hash(dict.getWord(i), hdict.size(), hash_method)]++;
    if(dict.getWord(i).size() > max_length) max_length = dict.getWord(i).size();
  }

  for(int i=0; i<hdict.size(); i++) {
    if(hdict[i] > repetitions) repetitions = hdict[i];
  }
  cout << "Bloom repetitions: " << repetitions << endl;

  vector<vector<bool> > used = vector<vector<bool> >(board.getN(), vector<bool>(board.getN(), false));

  bool found = false;
  string word = "";

  for(int i = 0; i < board.getN(); i++) {
    for(int j = 0; j < board.getN(); j++) {
      if(!used[i][j]) {
        stats.comparisons++;
        used[i][j] = true;
        word = board.position(i,j);
        found = check_for_word(word, board, dict, hdict, board.around(i,j), used, hash_method, max_length, stats);
        if(!found) used[i][j] = false;
        else {
          found = false;
          stats.found++;
        }
      }
    }
  }

  // SOLUTION:
  for(int i=0; i<board.getN(); i++) {
    for(int j=0; j<board.getN(); j++) {
      cout << " ";
      if(used[i][j]) cout << board.position(i,j);
      else cout << "-";
    }
    cout << endl;
  }

  stats.clock_end = clock();
}

bool check_for_word(string word, Board &board, Dictionary &dict, vector<int> &hdict, vector<Board::Cell> v, vector<vector<bool> > &used, const int &hash_method, const int &l, Board::Stats & stats) {
  bool found = false;
  string s = "";

  if(word.size() < l) {
    for(int i = 0; i < v.size(); i++) {
      if(not used[v[i].i][v[i].j]) {
        stats.comparisons++;

        used[v[i].i][v[i].j] = true;
        s = word + v[i].val;
        found = check_for_word(s, board, dict, hdict, board.around(v[i].i,v[i].j), used, hash_method, l, stats);
        if(!found) used[v[i].i][v[i].j] = false;
        else return true;
      }
    }
  }

  if(hdict[custom_hash(word, hdict.size(), hash_method)] > 0) {
    found = search_word(word, dict);
    if(found) {
      hdict[custom_hash(word, hdict.size(), hash_method)]--;

      stats.score += word.size();
    }
    return found;
  }

  return found;
}

bool search_word(string s, Dictionary &dict) {
  list<string> words = dict.getWords();
  for(int i=0; i<words.size(); i++) {
    if(s == dict.getWord(i)) {
      dict.eraseWord(s);
      return true;
    }
  }

  return false;
}
