#include <iostream>
#include "dictionary.h"
#include "board.h"

using namespace std;

void greedy(Dictionary & dictionary, Board & board) {
    int found = 0;
    int score = 0;
    int comparisons = 0;
    vector<bool> check(dictionary.getK(),false);
    for (int w = 0; w < dictionary.getK(); ++w) {
        string word = dictionary.getWord(w);
        for (int i = 0; i < board.getN(); ++i) {
            for (int j = 0; j < board.getN(); ++j) {
                if (board.position(i,j) == word[0] and not check[w]) {
                    int ii = i;
                    int jj = j;
                    vector<Board::Cell> arround = board.arround(i,j);
                    int index = 1;
                    while (ii != -1 or jj != -1 and index < word.size()) {
                        bool next = false;
                        for (int k = 0; k < arround.size() and not next; ++k) {
                            ++comparisons;
                            if (arround[k].val == word[index]) {
                                ii = arround[k].i;
                                jj = arround[k].j;
                                next = true;
                            }
                            else {
                                ii = -1;
                                jj = -1;
                            }
                        }
                        ++index;
                    }
                    if (index == word.size()) {
                        ++found;
                        score += word.size();
                        check[w] = true;
                    }
                }
            }
        }
    }
    cout << "Found: " << found  << " out of " << dictionary.getK() << " total words" << endl;
    cout << "Score: " << score << endl;
    cout << "Comparisons: " << comparisons << endl;
}

int main()
{
    int n, k, r1, r2, seed;
    string file1, file2;

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

    greedy(dictionary,board);
}

