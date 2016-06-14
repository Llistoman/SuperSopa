#include <iostream>
#include "dictionary.h"
#include "board.h"
#include "trie.h"
#include "hashing.h"
#include "trie_alg.h"
#include "naive.h"

using namespace std;

void stats_reset(Board::Stats & stats) {
  stats.found = 0;
  stats.score = 0;
  stats.comparisons = 0;
  stats.clock_begin = stats.clock_end = clock();
}

void stats_print(Board::Stats & stats, int k) {
  int time = int(stats.clock_end - stats.clock_begin) / CLOCKS_PER_SEC;
  cout << "Time spent: " << time/60 << " minutes " << time%60 << " seconds" << endl;
  cout << "Found: " << stats.found << " out of " << k << " total words" << endl;
  cout << "Score: " << stats.score << endl;
  cout << "Comparisons: " << stats.comparisons << endl;
  cout << "---------------" << endl;
}

int main()
{
    int n, k, r1, r2, seed;
    string file1, file2;
    Board::Stats stats;

    cout << "N?" << endl;
    cin >> n;
    cout << "What output file (board)?" << endl;
    cin >> file1;

    cout << "K?" << endl;
    cin >> k;
    cout << "What output file (words)?" << endl;
    cin >> file2;
    cout << "Range?" << endl;
    cin >> r1 >> r2;
    cout << "What seed?" << endl;
    cin >> seed;

    Board board(n,file1);
    Dictionary dictionary(k,r1,r2,file2);

    board.generateBoard(seed);
    dictionary.generateWords(seed);

    stats_reset(stats);
    cout << endl << "Naive/greedy:" << endl;
    naive(dictionary,board,stats);
    stats_print(stats, k);
    cout << endl;

    stats_reset(stats);
    cout << "Trie implementation:" << endl;
    trie_alg(dictionary,board,stats);
    stats_print(stats, k);
    cout << endl;

    cout << "Hashes:" << endl;
    for(int i = 1; i < 3; i++) {
      stats_reset(stats);
      by_bloom(dictionary, board, i, stats);
      stats_print(stats, k);
    }
    cout << endl;
}
