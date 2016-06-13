#include "dictionary.h"

Dictionary::Dictionary(int K, int range1, int range2, string output) {
    k = K;
    r1 = range1;
    r2 = range2;
    file = output;
    dictionary = vector<string>(K);
}

int Dictionary::getK() {
    return k;
}

vector<string> Dictionary::getWords() {
    return dictionary;
}

string Dictionary::getWord(int i) {
    return dictionary[i];
}

pair<int, int> Dictionary::getRange() {
    return make_pair(r1,r2);
}

string Dictionary::getOutputFile() {
    return file;
}

void Dictionary::changeK(int K) {
    k = K;
}

void Dictionary::changeRange(int range1, int range2) {
    r1 = range1;
    r2 = range2;
}

void Dictionary::changeOutputFile(string output) {
    file = output;
}

void Dictionary::generateWords(int seed) {

    //if given seed is negative use time to generate random seed
    if (seed >= 0) srand(seed);
    else srand(time(0));

    ofstream output;
    output.open(file.c_str());

    for(int i = 0; i < k; ++i) {
        int x = rand() % (r2 - r1) + r1;
        string y = to_string(x);
        dictionary[i] = y;
        output << y; output << "\n";
    }
    output.close();
}
