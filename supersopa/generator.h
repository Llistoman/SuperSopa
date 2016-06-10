#ifndef GENERATOR_H
#define GENERATOR_H

#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class Generator
{
private:
    int k;
    int r1;
    int r2;
    vector<int> dictionary;
    string file;

public:
    Generator(int K, int range1, int range2, string output);
    int getK();
    pair<int,int> getRange();
    vector<int> getWords();
    string getOutputFile();
    void changeK(int K);
    void changeRange(int range1, int range2);
    void changeOutputFile(string output);
    void generateWords(int seed);

};

#endif // GENERATOR_H
