#include "board.h"

Board::Board(int N, string output) {
    n = N;
    file = output;
    board = vector<vector<char> > (n, vector<char>(n));
}

int Board::getN() {
    return n;
}

string Board::getOutputFile() {
    return file;
}

char itoc(int x) {
    if (x == 0) return '0';
    if (x == 1) return '1';
    if (x == 2) return '2';
    if (x == 3) return '3';
    if (x == 4) return '4';
    if (x == 5) return '5';
    if (x == 6) return '6';
    if (x == 7) return '7';
    if (x == 8) return '8';
    if (x == 9) return '9';
}

void Board::generateBoard(int seed) {

    //if given seed is negative use time to generate random seed
    if (seed >= 0) srand(seed);
    else srand(time(0));

    ofstream output;
    string f = file + ".txt";
    output.open(f);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = rand() % 10;
            char y = itoc(x);
            board[i][j] = y;
            output << y; output << " ";
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

char Board::position(int i, int j) {
    return board[i][j];
}

vector<Board::Cell> Board::around(int i, int j) {
    Cell aux;
    vector<Cell> res;
    for (int x = i-1; x <= i+1; ++x) {
        for (int y = j-1; y <= j+1; ++y) {
            if (not (x == i and y == j) and x >= 0 and x < n and y >= 0 and y < n) {
                aux.val = board[x][y];
                aux.i = x;
                aux.j = y;
                res.push_back(aux);
            }
        }
    }
    return res;
}

