#include <iostream>
#include <generator.h>

using namespace std;

int main()
{
    int k, range;
    string file;
    cout << "How many numbers?" << endl;
    cin >> k;
    cout << "What range from 0 to?" << endl;
    cin >> range;
    cout << "What output file?" << endl;
    cin >> file;
    Generator gen(k,range,file);
    gen.generateWords(-1);
}

