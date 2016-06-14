#include "trie_alg.h"

bool check_for_word(Trie &trie, string word, Board &board, Dictionary &dict, vector<Board::Cell> &adj, vector<vector<bool> > &used, const int &l) {
  bool found = false;
  string s = "";

  if(word.size() < l) {
    for(int i = 0; i < adj.size(); i++) {
      if(not used[adj[i].i][adj[i].j]) {
        used[adj[i].i][adj[i].j] = true;
        s = word + adj[i].val;
        if(trie.isPrefix(s)) {
            vector<Board::Cell> aux = board.around(adj[i].i,adj[i].j);
            found = check_for_word(trie, s, board, dict, aux, used, l);
            if(!found) used[adj[i].i][adj[i].j] = false;
            else return true;
        }
      }
    }
  }
  if(trie.searchWord(s)) {
      trie.deleteWord(s);
      return true;
  }
  return false;
}

void trie_alg(Dictionary & dictionary, Board & board) {

    int found_words = 0;
    int score = 0;
    int comparisons = 0;
    vector<vector<bool> > used(board.getN(), vector<bool>(board.getN(), false));
    Dictionary dict = dictionary;

    //init trie
    Trie trie;
    int max_length = dictionary.getWord(0).size();
    for(int w = 0; w < dictionary.getK(); ++w) {
        string s = dictionary.getWord(w); //MEJORAR ESTO
        trie.addWord(s);
        if(s.size() > max_length) max_length = s.size();
    }
    string word;
    bool found = false;
    const clock_t begin = clock();

    for(int i = 0; i < board.getN(); i++) {
      for(int j = 0; j < board.getN(); j++) {
        word = board.position(i,j);
        if(!used[i][j] and trie.isPrefix(word)) {
          used[i][j] = true;
          vector<Board::Cell> aux = board.around(i,j);
          found = check_for_word(trie, word, board, dict, aux, used, max_length);
          if(!found) used[i][j] = false;
          else {
            found = false;
            found_words++;
          }
        }
      }
    }

    const clock_t end = clock();
    int time = int(end - begin) / CLOCKS_PER_SEC;
    cout << "Time spent: " << time/60 << " minutes " << time%60 << " seconds" << endl;
    cout << "Found: " << found_words  << " out of " << dict.getK() << " total words" << endl;
    cout << "Score: " << score << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << "---------------" << endl;
}

