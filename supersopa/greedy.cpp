#include "greedy.h"

void greedy(Dictionary & dictionary, Board & board, Board::Stats & stats) {
  vector<vector<bool> > used(board.getN(), vector<bool>(board.getN(), false));
  vector<bool> check(dictionary.getK(),false);

  stats.clock_begin = clock();

  int max_length = dictionary.getWord(0).size();
  list<string>::iterator it = dictionary.begin();
  while(it != dictionary.end()) {
    string s = *it;
    if(s.size() > max_length) max_length = s.size();
    it++;
  }
  Dictionary dict = dictionary;
  string word = "";
  for(int i=0; i<board.getN(); i++) {
    for(int j=0; j<board.getN(); j++) {
      cout << "pos " << i << "," << j << "; ";
      ++stats.comparisons;
      if(not used[i][j]) {
        word = board.position(i,j);
        used[i][j] = true;
        bool found = check_for_word(dict, word, board, board.around(i,j), used, max_length, stats);
        if(not found) used[i][j] = false;
      }
    }
  }

  // SOLUTION:
  ofstream output;
  string f = board.getOutputFile() + "_greedy_sol.txt";
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
    cout << endl;
  }
  output.close();

  stats.clock_end = clock();
}


bool check_for_word(Dictionary &dict, string word, Board &board, vector<Board::Cell> adj, vector<vector<bool> > &used, const int &l, Board::Stats &stats) {
  bool found = false;

  cout << endl << "start check for \"" << word << "\"";
  if(word.size() < l) {
    for(int i=0; i<adj.size(); i++) {
      ++stats.comparisons;
      if(not used[adj[i].i][adj[i].j]) {
        string s = word + adj[i].val;
        if(search_prefix(s, dict)) {
          used[adj[i].i][adj[i].j] = true;
          found = check_for_word(dict, s, board, board.around(adj[i].i,adj[i].j), used, l, stats);
          if(not found) used[adj[i].i][adj[i].j] = false;
          else return true;
        }
      }
    }
  }

  cout << "; check done";
  found = search_word_g(word, dict);
  if(found) {
    ++stats.found;
    stats.score += word.size();
    cout << "; word found";
  }

  cout << endl;
  return found;
}

bool search_prefix(string s, Dictionary &dict) {
  list<string>::iterator it = dict.begin();
  string word = "";
  while(it != dict.end()) {
    word = *it;
    if(word.size() >= s.size()) {
      int i=0;
      while(i<s.size() and s[i]==word[i]) i++;
      if(i == s.size()) return true;
    }
  }

  return false;
}

bool search_word_g(string s, Dictionary &dict) {
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
