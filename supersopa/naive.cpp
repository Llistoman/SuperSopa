#include "naive.h"

void naive(Dictionary & dictionary, Board & board, Board::Stats & stats, int tiempo) {
    vector<vector<bool> > visited(board.getN(), vector<bool>(board.getN(), false));
    vector<bool> check(dictionary.getK(),false);

    stats.clock_begin = clock();

    bool timeup = false;
    clock_t aux = clock();

    for (int w = 0; w < dictionary.getK() and not timeup; ++w) {

        string word = dictionary.nextWord();
        stack<pair<int,int> > pos;

        for (int i = 0; i < board.getN() and not check[w] and not timeup; ++i) {
            for (int j = 0; j < board.getN() and not check[w] and not timeup; ++j) {

                ++stats.comparisons;
                pos.push(make_pair(i,j));
                visited[i][j] = true;
                bool found = check_for_word(word, 1, board, board.around(i,j), visited, pos, stats, tiempo, aux);
                if(not found) {
                    visited[i][j] = false;
                    pos.pop();
                }
                else {
                    while(not pos.empty()) {
                        pos.pop();
                    }
                    ++stats.found;
                    stats.score += word.size();
                    check[w] = true;
                }

                aux = clock();
                timeup = (tiempo != 0 and tiempo <= (int(aux - stats.clock_begin) / CLOCKS_PER_SEC));
            }
        }
    }

    stats.clock_end = clock();

    // SOLUTION:
    ofstream output;
    string f = board.getOutputFile() + "_naive_sol.txt";
    output.open(f);
    for(int i=0; i<board.getN(); i++) {
        for(int j=0; j<board.getN(); j++) {
            output << " ";
            if(visited[i][j]) {
                output << board.position(i,j);
            }
            else {
                output << "-";
            }
        }
        output << "\n";
    }
    output.close();
}

bool check_for_word(string &word, int index, Board &board, vector<Board::Cell> adj, vector<vector<bool> > &visited, stack<pair<int,int> > &pos, Board::Stats &stats, const int &tiempo, clock_t &aux) {
    bool found = false;

    if(index == word.size()) return true;

    aux = clock();
    bool timeup = (tiempo != 0 and tiempo <= (int(aux - stats.clock_begin) / CLOCKS_PER_SEC));

    if(index < word.size()) {
        bool next = true;
        for(int i = 0; i < adj.size() and not found and not timeup; i++) {
            ++stats.comparisons;
            next = (word[index] == adj[i].val);

            if(not visited[adj[i].i][adj[i].j] and next) {
                pos.push(make_pair(adj[i].i,adj[i].j));
                visited[adj[i].i][adj[i].j] = true;

                found = check_for_word(word, index+1, board, board.around(adj[i].i,adj[i].j), visited, pos, stats, tiempo, aux);
                if(not found) {
                    visited[adj[i].i][adj[i].j] = false;
                    pos.pop();
                }
            }
            aux = clock();
            timeup = (tiempo != 0 and tiempo <= (int(aux - stats.clock_begin) / CLOCKS_PER_SEC));
        }
    }

    return found;
}
