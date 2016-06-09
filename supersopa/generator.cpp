#include "generator.h"

Generator::Generator(int K, int range, string output) {
    k = K;
    r = range;
    file = output;
    dictionary = vector<int>(K);
}

int Generator::getK() {
    return k;
}

int Generator::getRange() {
    return r;
}

string Generator::getOutputFile() {
    return file;
}

void Generator::changeOutputFile(string output) {
    file = output;
}

void Generator::generateWords(int seed) {

    //if given seed is negative use time to generate random seed
    if (seed >= 0) srand(seed);
    else srand(time(0));

    ofstream output;
    output.open(file + ".txt");

    for(int i = 0; i < k; ++i) {
        int x = rand() % r;
        dictionary[i] = x;
        output << x; output << "\n";
    }
    output.close();
}
