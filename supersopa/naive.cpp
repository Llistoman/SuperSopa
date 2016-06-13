#include "naive.h"

void naive(Dictionary & dictionary, Board & board) {
    int found = 0;
    int score = 0;
    int comparisons = 0;
    vector<vector<bool> > visited(board.getN(), vector<bool>(board.getN(), false));
    vector<bool> check(dictionary.getK(),false);

    const clock_t begin = clock();

    for (int w = 0; w < dictionary.getK(); ++w) {

        string word = dictionary.nextWord();
        stack<pair<int,int> > pos;

        for (int i = 0; i < board.getN() and not check[w]; ++i) {
            for (int j = 0; j < board.getN() and not check[w]; ++j) {
                ++comparisons;

                if (not visited[i][j] and board.position(i,j) == word[0]) {
                    pos.push(make_pair(i,j));
                    vector<Board::Cell> adj = board.around(i,j);
                    bool end = false;
                    int index = 1;
                    while (not end and index < word.size()) {
                        //continue while finding word
                        bool next = false;
                        int k = 0;
                        int aux_i = i;
                        int aux_j = j;
                        while (not next and k < adj.size()) {
                            if (not visited[adj[k].i][adj[k].j] and word[index] == adj[k].val and not (adj[k].i == i and adj[k].j == j)) {
                                next = true;
                                aux_i = adj[k].i;
                                aux_j = adj[k].j;
                                pos.push(make_pair(aux_i,aux_j));
                                adj = board.around(aux_i,aux_j);
                            }
                            ++k;
                            ++comparisons;
                        }
                        if (not next) end = true;
                        else ++index;
                    }
                    if (index == word.size()) {
                        ++found;
                        score += word.size();
                        check[w] = true;
                        //set positions to true on visited
                        while(not pos.empty()) {
                            visited[pos.top().first][pos.top().second] = true;
                            pos.pop();
                        }
                    }
                    else {
                        pos.pop();
                    }
                }
            }
        }
    }

    const clock_t end = clock();
    int time = int(end - begin) / CLOCKS_PER_SEC;
    cout << "Time spent: " << time/60 << " minutes " << time%60 << " seconds" << endl;
    cout << "Found: " << found  << " out of " << dictionary.getK() << " total words" << endl;
    cout << "Score: " << score << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << endl;
}
