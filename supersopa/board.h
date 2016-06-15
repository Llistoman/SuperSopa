#ifndef BOARD_H
#define BOARD_H

#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class Board
{
private:
    int n;
    string file;
    vector<vector<char> > board;

public:
    struct Cell {
        char val;
        int i;
        int j;
    };

    struct Stats {
        int found;
        int comparisons;
        int score;
        clock_t clock_begin;
        clock_t clock_end;
    };

    Board(int N, string output);
    Board(string file);
    int getN();
    string getOutputFile();
    void generateBoard(int seed);
    void changeN(int N);
    void changeOutputFile(string output);
    char position(int i, int j);
    vector<Cell> around(int i, int j);

};

#endif // BOARD_H
