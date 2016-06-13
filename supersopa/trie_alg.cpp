#include "trie_alg.h"

void trie_alg(Dictionary & dictionary, Board & board) {

    /* While the queue is not empty:
  Dequeue a triple (x, y, s)
  For each square (x', y') with letter c adjacent to (x, y):
    If s+c is a word, output s+c
    If s+c is a prefix of a word, insert (x', y', s+c) into the queue

        trie->addWord("Hello");
        trie->addWord("Balloon");
        trie->addWord("Ball");

        if ( trie->searchWord("Hell") )
            cout << "Found Hell" << endl; */

    int found = 0;
    int score = 0;
    int comparisons = 0;
    vector<vector<bool> > visited(board.getN(), vector<bool>(board.getN(), false));

    Trie* trie = new Trie();
    for(int w = 0; w < dictionary.getK(); ++w) {
        trie->addWord(dictionary.getWord(w));
    }

    const clock_t begin = clock();

    //DO SHIT

    const clock_t end = clock();
    int time = int(end - begin) / CLOCKS_PER_SEC;
    cout << "Time spent: " << time/60 << " minutes " << time%60 << " seconds" << endl;
    cout << "Found: " << found  << " out of " << dictionary.getK() << " total words" << endl;
    cout << "Score: " << score << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << endl;
}

