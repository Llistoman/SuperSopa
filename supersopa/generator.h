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
    int r;
    vector<int> dictionary;
    string file;

public:
    Generator(int K, int range, string output);
    int getK();
    int getRange();
    vector<int> getWords();
    string getOutputFile();
    void changeOutputFile(string output);
    void generateWords(int seed);

};

#endif // GENERATOR_H
