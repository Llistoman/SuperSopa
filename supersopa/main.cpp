#include <iostream>
#include <generator.h>
#include <board.h>

using namespace std;

int main()
{
    int n;
    string file;
    cout << "N?" << endl;
    cin >> n;
    cout << "What output file?" << endl;
    cin >> file;
    Board board(n,file);
    board.generateBoard(-1);
    cout << "position?" << endl;
    int i,j;
    cin >> i >> j;
    cout << board.position(i,j) << endl;
    vector<int> res = board.arround(i,j);
    for (int x = 0; x < res.size(); ++x) {
        cout << res[x] << " ";
    }
    cout << endl;
}

