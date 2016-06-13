#include <iostream>
#include "dictionary.h"
#include "board.h"
#include "naive.h"

using namespace std;

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

    naive(dictionary,board);

    for(int i = 0; i < 3; i++) by_bloom(dictionary, board, i);
}
