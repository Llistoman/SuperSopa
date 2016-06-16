# include "trie_alg.h"


void trie_alg(Dictionary & dictionary, Board & board, Board::Stats & stats, int tiempo) {
    vector<vector<bool> > used(board.getN(), vector<bool>(board.getN(), false));
    Trie trie;

    int max_length = dictionary.getWord(0).size();
    list<string>::iterator it = dictionary.begin();
    while(it != dictionary.end()) {
        string s = *it;
        trie.addWord(s);
        if(s.size() > max_length) max_length = s.size();
        it++;
    }

    string word = "";
    stats.clock_begin = clock();
    clock_t aux = clock();
    bool timeup = (tiempo != 0 and tiempo <= (int(aux - stats.clock_begin) / CLOCKS_PER_SEC));

    for(int i=0; i<board.getN() and not timeup and not trie.empty(); i++) {
        for(int j=0; j<board.getN() and not timeup and not trie.empty(); j++) {
            ++stats.comparisons;
            if(not used[i][j]) {
                word = board.position(i,j);
                if(trie.isPrefix(word)) {
                    used[i][j] = true;
                    bool found = check_for_word(trie, word, board, board.around(i,j), used, max_length, stats, tiempo, aux);
                    if(not found) used[i][j] = false;
                }
            }
            aux = clock();
            timeup = (tiempo != 0 and tiempo <= (int(aux - stats.clock_begin) / CLOCKS_PER_SEC));
        }
    }

    stats.clock_end = clock();

    // SOLUTION:
    ofstream output;
    string f = board.getOutputFile() + "_trie_sol.txt";
    output.open(f);
    for(int i=0; i<board.getN(); i++) {
        for(int j=0; j<board.getN(); j++) {
            output << " ";
            if(used[i][j]) {
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

bool check_for_word(Trie &trie, string word, Board &board, vector<Board::Cell> adj, vector<vector<bool> > &used, const int &l, Board::Stats &stats, const int &tiempo, clock_t &aux) {
    bool found = false;
    aux = clock();
    bool timeup = (tiempo != 0 and tiempo <= (int(aux - stats.clock_begin) / CLOCKS_PER_SEC));

    if(word.size() < l) {
        for(int i=0; i<adj.size() and not timeup; i++) {
            ++stats.comparisons;
            if(not used[adj[i].i][adj[i].j]) {
                string s = word + adj[i].val;
                if(trie.isPrefix(s)) {
                    used[adj[i].i][adj[i].j] = true;
                    found = check_for_word(trie, s, board, board.around(adj[i].i,adj[i].j), used, l, stats, tiempo, aux);
                    if(not found) used[adj[i].i][adj[i].j] = false;
                    else return true;
                }
            }
            aux = clock();
            timeup = (tiempo != 0 and tiempo <= (int(aux - stats.clock_begin) / CLOCKS_PER_SEC));
        }
    }

    if(timeup) return false;

    if(trie.searchWord(word)) {
        trie.deleteWord(word);
        ++stats.found;
        stats.score += word.size();
        found = true;
    }

    return found;
}
