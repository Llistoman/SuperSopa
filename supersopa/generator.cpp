#include "generator.h"

Generator::Generator(int K, int range1, int range2, string output) {
    k = K;
    r1 = range1;
    r2 = range2;
    file = output;
    dictionary = vector<int>(K);
}

int Generator::getK() {
    return k;
}

pair<int, int> Generator::getRange() {
    return make_pair(r1,r2);
}

string Generator::getOutputFile() {
    return file;
}

void Generator::changeK(int K) {
    k = K;
}

void Generator::changeRange(int range1, int range2) {
    r1 = range1;
    r2 = range2;
}

void Generator::changeOutputFile(string output) {
    file = output;
}

void Generator::generateWords(int seed) {

    //if given seed is negative use time to generate random seed
    if (seed >= 0) srand(seed);
    else srand(time(0));

    ofstream output;
    output.open(file);

    for(int i = 0; i < k; ++i) {
        int x = rand() % r2 + r1;
        dictionary[i] = x;
        output << x; output << "\n";
    }
    output.close();
}
