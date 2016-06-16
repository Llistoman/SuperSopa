#include "dictionary.h"

Dictionary::Dictionary(int K, int range1, int range2, string output) {
    k = K;
    r1 = range1;
    r2 = range2;
    file = output;
    dictionary = list<string>();
}

Dictionary::Dictionary(string f) {
    ifstream input;
    string s = f + ".txt";
    input.open(s);
    if (input.is_open()) {
        input >> k;
        dictionary = list<string>();
        string aux;
        int min = 2 << 29;
        int max = 0;
        for (int j = 0; j < k; ++j) {
            input >> aux;
            if(stoi(aux,nullptr,10) > max) max = stoi(aux,nullptr,10);
            if(stoi(aux,nullptr,10) < min) min = stoi(aux,nullptr,10);
            dictionary.push_back(aux);
        }
        input.close();
        file = f;
        it = dictionary.begin();
        r1 = min;
        r2 = max;
    }
    else cout << "No se ha podido abrir el archivo del tablero" << endl;
}

int Dictionary::getK() {
    return k;
}

list<string> Dictionary::getWords() {
    return dictionary;
}

string Dictionary::getWord(int i) {
    list<string>::iterator j = dictionary.begin();
    int k = 0;
    while (k != i and j != dictionary.end()) {
        ++k;
        ++j;
    }
    return *j;
}

string Dictionary::nextWord() {
    string res = *it;
    ++it;
    return res;
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

bool Dictionary::contains(string w) {
    list<string>::iterator it = dictionary.begin();
    while(it != dictionary.end()) {
      if (*it == w) return true;
      it++;
    }
    return false;
}

void Dictionary::generateWords(int seed) {

    //if given seed is negative use time to generate random seed
    if (seed >= 0) srand(seed);
    else srand(time(0));

    ofstream output;
    string f = file + ".txt";
    output.open(f);
    output << k; output << "\n";
    for(int i = 0; i < k; ++i) {
        int x = (rand() % (r2 - r1)) + r1;
        string y = to_string(x);
        while(Dictionary::contains(y)) {
            x = (rand() % (r2 - r1)) + r1;
            y = to_string(x);
        }
        dictionary.push_front(y);
        output << y; output << "\n";
    }
    output.close();
    it = dictionary.begin();
}

void Dictionary::eraseWord(string w) {
    dictionary.remove(w);
}

list<string>::iterator Dictionary::begin() {
    list<string>::iterator it = dictionary.begin();
    return it;
}

list<string>::iterator Dictionary::end() {
    list<string>::iterator it = dictionary.end();
    return it;
}

bool Dictionary::empty() {
    return dictionary.empty();
}
