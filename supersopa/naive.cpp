#include "naive.h"

void naive(Dictionary & dictionary, Board & board, Board::Stats & stats, int tiempo) {
    vector<vector<bool> > visited(board.getN(), vector<bool>(board.getN(), false));
    vector<bool> check(dictionary.getK(),false);

    stats.clock_begin = clock();

    bool timeup = false;
    for (int w = 0; w < dictionary.getK() and not timeup; ++w) {

        clock_t aux = clock();
        if (tiempo == 0 or tiempo > (int(aux - stats.clock_begin) / CLOCKS_PER_SEC)) {
            string word = dictionary.nextWord();
            stack<pair<int,int> > pos;

            for (int i = 0; i < board.getN() and not check[w] and not timeup; ++i) {

                clock_t aux2 = clock();
                if (tiempo == 0 or tiempo > (int(aux2 - stats.clock_begin) / CLOCKS_PER_SEC)) {

                    for (int j = 0; j < board.getN() and not check[w] and not timeup; ++j) {

                        clock_t aux3 = clock();
                        if (tiempo == 0 or tiempo > (int(aux3 - stats.clock_begin) / CLOCKS_PER_SEC)) {

                            ++stats.comparisons;

                            if (not visited[i][j] and board.position(i,j) == word[0]) {
                                pos.push(make_pair(i,j));
                                visited[i][j] = true;
                                bool found = check_for_word(word, 1, board, board.around(i,j), visited, pos, stats);
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
                            }
                        }
                        else timeup = true;
                    }
                }
                else timeup = true;
            }
        }
        else timeup = true;
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

bool check_for_word(string &word, int index, Board &board, vector<Board::Cell> adj, vector<vector<bool> > &visited, stack<pair<int,int> > &pos, Board::Stats &stats) {
    bool found = false;

    if(index == word.size()) return true;

    if(index < word.size()) {
        bool next = true;
        for(int i = 0; i < adj.size() and not found; i++) {
            ++stats.comparisons;
            next = (word[index] == adj[i].val);

            if(not visited[adj[i].i][adj[i].j] and next) {
                pos.push(make_pair(adj[i].i,adj[i].j));
                visited[adj[i].i][adj[i].j] = true;

                found = check_for_word(word, index+1, board, board.around(adj[i].i,adj[i].j), visited, pos, stats);
                if(not found) {
                    visited[adj[i].i][adj[i].j] = false;
                    pos.pop();
                }
            }
        }
    }

    return found;
}
