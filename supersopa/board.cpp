#include "board.h"

Board::Board(int N, string output) {
    n = N;
    file = output;
    board = vector<vector<int> > (n, vector<int>(n));
}

int Board::getN() {
    return n;
}

string Board::getOutputFile() {
    return file;
}

void Board::generateBoard(int seed) {

    //if given seed is negative use time to generate random seed
    if (seed >= 0) srand(seed);
    else srand(time(0));

    ofstream output;
    output.open(file);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = rand() % 10;
            board[i][j] = x;
            output << x; output << " ";
        }
        output << "\n";
    }
}

void Board::changeN(int N) {
    n = N;
}

void Board::changeOutputFile(string output) {
    file = output;
}

int Board::position(int i, int j) {
    return board[i][j];
}

vector<int> Board::arround(int i, int j) {
    vector<int> res = vector<int>(8,-1);
    int index = 0;
    for (int x = i-1; x <= i+1; ++x) {
        for (int y = j-1; y <= j+1; ++y) {
            if ((x != i or y != j) and x >= 0 and x < n and y >= 0 and y < n) {
                res[index] = board[x][y];
                ++index;
            }
        }
    }
    return res;
}

