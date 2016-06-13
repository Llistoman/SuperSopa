#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include <list>
#include <string>

using namespace std;

class Dictionary
{
private:
    int k;
    int r1;
    int r2;
    list<string> dictionary;
    list<string>::iterator it;
    string file;


public:
    Dictionary(int K, int range1, int range2, string output);
    int getK();
    pair<int,int> getRange();
    list<string> getWords();
    string getWord(int i);
    string getOutputFile();
    string nextWord();
    void changeK(int K);
    void changeRange(int range1, int range2);
    void changeOutputFile(string output);
    void generateWords(int seed);
    void eraseWord(string w);

};

#endif // DICTIONARY_H
