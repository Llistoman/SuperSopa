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

int hash_basic_sum(string s, int n, int k) {
  long key = 0;
  for(int i = 0; i < s.size(); i++) {
    key += s[i] - '0';
  }
  key = key*k;
  int r = key % n;
  return r;
}

int hash_sum(string s, int n, int k) {
  long key = 0;
  for(int i = 0; i < s.size(); i++) {
    key *= k;
    key += s[i] - '0';
    key = key % n;
  }
  return key;
}

int hash_read(string s, int n, int k) {
  long key = stoi(s,nullptr,10)*k;
  int r = key % n;
  return r;
}

int custom_hash(string s, int n, int k, int m) {
  switch(m) {
    //caso base es busqueda naive del siguiente primo (ver default)
    //SUM MOD NAIVE NEXT PRIME

    //caso 1 es suponiendo que haciendo de s un num en base [primo]
    //es suficiente primalidad
    //SUM OF BASE 31 DIGITS
    case 1:
      return hash_sum(s, n, k);

    //caso 2 es usando el propio numero representado para el calc del modulo
    //NUM MOD NEXT PRIME
    case 2:
      return hash_read(s, n, k);

    default:
      return hash_basic_sum(s, n, k);
  }
}

void by_bloom(Dictionary & dictionary, Board & board, int hash_method, Board::Stats & stats) {
  int max_length = 0;
  int hashN = 0;
  int prime = 0;
  int repetitions = 0;
  Dictionary dict = dictionary;
  vector<int> hdict;

  stats.clock_begin = clock();

  cout << "Hashing method used: ";
  if((dictionary.getRange().second - dictionary.getRange().first) > dictionary.getK())
    prime = (dictionary.getRange().second - dictionary.getRange().first)*30 % dictionary.getK();
  else prime = dictionary.getK()*30 % (dictionary.getRange().second - dictionary.getRange().first);
  prime = next_prime(prime);

  switch(hash_method) {
    //caso base es busqueda naive del siguiente primo (ver default)
    //SUM MOD PRIME

    //caso 1 es suponiendo que haciendo de s un num en base [primo]
    //es suficiente primalidad
    //SUM OF BASE 'PRIME' DIGITS
    case 1:
      hashN = dictionary.getK();
      cout << "SUM OF BASE " << prime << " DIGITS" << endl;
      break;

    //caso 2 es usando el propio numero representado para el calc del modulo
    //NUM MOD NEXT PRIME
    case 2:
      hashN = next_prime(dictionary.getK());
      cout << "NUM MOD " << prime << endl;
      break;

    default:
      hashN = next_prime(dictionary.getK());
      cout << "SUM MOD " << prime << endl;
      break;
  }

  hdict = vector<int>(hashN, 0);
  cout << "Hash dict. size: " << hashN << endl;
  for(int i=0; i<dict.getK(); i++) {
    hdict[custom_hash(dict.getWord(i), hdict.size(), prime, hash_method)]++;
    if(dict.getWord(i).size() > max_length) max_length = dict.getWord(i).size();
  }

  for(int i=0; i<hdict.size(); i++) {
    if(hdict[i] > repetitions) repetitions = hdict[i];
  }
  cout << "Max. hash repetitions: " << repetitions << endl;

  vector<vector<bool> > used = vector<vector<bool> >(board.getN(), vector<bool>(board.getN(), false));

  bool found = false;
  string word = "";

  for(int i = 0; i < board.getN(); i++) {
    for(int j = 0; j < board.getN(); j++) {
      if(!used[i][j]) {
        stats.comparisons++;
        used[i][j] = true;
        word = board.position(i,j);
        found = check_for_word(word, board, dict, hdict, board.around(i,j), used, prime, hash_method, max_length, stats);
        if(!found) used[i][j] = false;
        else {
          found = false;
          stats.found++;
        }
      }
    }
  }

  // SOLUTION:
  ofstream output;
  string f = board.getOutputFile() + "_hash_" + to_string(hash_method) + "_sol.txt";
  output.open(f);
  for(int i=0; i<board.getN(); i++) {
    for(int j=0; j<board.getN(); j++) {
      output << " ";
      if(used[i][j]) {
          output << board.position(i,j);
      }
      else {
          output << "-";
      }
    }
    output << "\n";
  }
  output.close();

  stats.clock_end = clock();
}

bool check_for_word(string word, Board &board, Dictionary &dict, vector<int> &hdict, vector<Board::Cell> v, vector<vector<bool> > &used, const int &prime, const int &hash_method, const int &l, Board::Stats & stats) {
  bool found = false;
  string s = "";

  if(word.size() < l) {
    for(int i = 0; i < v.size(); i++) {
      if(not used[v[i].i][v[i].j]) {
        stats.comparisons++;

        used[v[i].i][v[i].j] = true;
        s = word + v[i].val;
        found = check_for_word(s, board, dict, hdict, board.around(v[i].i,v[i].j), used, prime, hash_method, l, stats);
        if(not found) used[v[i].i][v[i].j] = false;
        else return true;
      }
    }
  }

  if(hdict[custom_hash(word, hdict.size(), prime, hash_method)] > 0) {
    found = search_word_h(word, dict);
    if(found) {
      hdict[custom_hash(word, hdict.size(), prime, hash_method)]--;
      stats.score += word.size();
    }
    return found;
  }

  return found;
}

bool search_word_h(string s, Dictionary &dict) {
  list<string>::iterator it = dict.begin();
  while(it != dict.end()) {
    if(s == *it) {
      dict.eraseWord(s);
      return true;
    }
    it++;
  }

  return false;
}
