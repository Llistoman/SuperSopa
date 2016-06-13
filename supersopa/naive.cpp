#include "naive.h"

void naive(Dictionary & dictionary, Board & board) {
    int found = 0;
    int score = 0;
    int comparisons = 0;
    vector<vector<bool> > visited(board.getN(), vector<bool>(board.getN(), false));

    const clock_t begin = clock();

    for (int w = 0; w < dictionary.getK(); ++w) {

        bool word_found = false;
        string word = dictionary.nextWord();
        stack<pair<int,int> > pos;

        for (int i = 0; i < board.getN() and not word_found; ++i) {
            for (int j = 0; j < board.getN() and not word_found; ++j) {
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
                        while (not next and k < adj.size()) {
                            if (not visited[adj[k].i][adj[k].j] and word[index] == adj[k].val) {
                                next = true;
                                int aux_i = adj[k].i;
                                int aux_j = adj[k].j;
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
                        word_found = true;
                        //set positions to true on visited
                        while(not pos.empty()) {
                            cout << board.position(pos.top().first, pos.top().second);
                            visited[pos.top().first][pos.top().second] = true;
                            pos.pop();
                        }
                        cout << endl;
                    }
                    else {
                        stack<pair<int,int> > aux;
                        pos = aux;
                    }
                }
            }
        }
    }


      for(int i = 0; i < board.getN(); i++) {
        for(int j = 0; j < board.getN(); j++) {
          cout << " " << visited[i][j];
        }
        cout << endl;
      }

    const clock_t end = clock();
    int time = int(end - begin) / CLOCKS_PER_SEC;
    cout << "Time spent: " << time/60 << " minutes " << time%60 << " seconds" << endl;
    cout << "Found: " << found  << " out of " << dictionary.getK() << " total words" << endl;
    cout << "Score: " << score << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << endl;
}
