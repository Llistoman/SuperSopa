#include <iostream>
#include "dictionary.h"
#include "board.h"
#include "trie.h"
#include "hashing.h"
#include "trie_alg.h"
#include "naive.h"  //Naive
#include "greedy.h" //Naive2

using namespace std;

void stats_reset(Board::Stats & stats) {
  stats.found = 0;
  stats.score = 0;
  stats.comparisons = 0;
  stats.clock_begin = stats.clock_end = clock();
}

void stats_print(Board::Stats & stats, int k) {
  int time = int(stats.clock_end - stats.clock_begin) / CLOCKS_PER_SEC;
  cout << "Tiempo transcurrido: " << time/60 << " minutes " << time%60 << " seconds" << endl;
  cout << "Encontradas: " << stats.found << " de " << k << " palabras totales" << endl;
  cout << "Puntuacion: " << stats.score << endl;
  cout << "Comparaciones: " << stats.comparisons << endl;
  cout << "---------------" << endl;
}

int main()
{
    int n, k, r1, r2, seed;
    string file1, file2;
    Board::Stats stats;

    cout << "--------------------------------------------------------------------------" << endl;
    cout << "--------------------------------SUPERSOPA---------------------------------" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "Bienvenido a nuestra practica de Algorítmia." << endl;
    cout << "Selecciona un tamaño para el tablero (N)" << endl;
    cin >> n;
    cout << "Selecciona un numero de palabras para el diccionario (K)" << endl;
    cin >> k;
    cout << "Rango de numeros para formar palabras (primero minimo, despues maximo)" << endl;
    cin >> r1 >> r2;
    cout << "Introduce una semilla (si es negativa se usara el tiempo local)" << endl;
    cin >> seed;
    cout << "Escrbe el nombre del archivo donde se guardara el tablero (las soluciones" << endl;
    cout << "de los algoritmos también utilizaran archivos con ese nombre añadiendo '_sol'" << endl;
    cin >> file1;
    cout << "Escrbe el nombre del archivo donde se guardaran las palabras del diccionario" << endl;
    cin >> file2;

    Board board(n,file1);
    Dictionary dictionary(k,r1,r2,file2);

    board.generateBoard(seed);
    dictionary.generateWords(seed);

    cout << "Que algoritmo deseas probar?" << endl;
    cout << "0 - Naive (voraz que mira palabras iterativamente)" << endl;
    cout << "1 - Naive2 (voraz que recorre el tablero iterativamente buscando palabras en DFS)" << endl;
    cout << "2 - Trie (busca palabras en DFS, usa un Trie para consultar en el diccionario)" << endl;
    cout << "3 - Hash (busca palabras en DFS, hay varios Hashes para consultar)" << endl;
    cout << "4 - Terminar ejecucion" << endl;

    int option;
    while (cin >> option) {
        if (option == 0) {
            stats_reset(stats);
            cout << endl << "Naive:" << endl;
            naive(dictionary,board,stats);
            stats_print(stats, k);
            cout << endl;
        }
        else if (option == 1) {
          stats_reset(stats);
          cout << endl << "Naive2:" << endl;
          naive(dictionary,board,stats);
          stats_print(stats, k);
          cout << endl;
        }
        else if (option == 2) {
            stats_reset(stats);
            cout << "Trie implementation:" << endl;
            trie_alg(dictionary,board,stats);
            stats_print(stats, k);
            cout << endl;
        }
        else if (option == 3) {
            int order2;
            cout << "Selecciona tipo de Hash:" << endl;
            cout << "0 - Suma de digitos modulo primo" << endl;
            cout << "1 - Suma de digitos por primo elevado a N" << endl;
            cout << "2 - Numero modulo primo" << endl;

            cin >> order2;
            if (order2 == 0) {
                stats_reset(stats);
                cout << "Hash 0:" << endl;
                by_bloom(dictionary, board, 0, stats);
                stats_print(stats, k);
            }
            else if (order2 == 1) {
                stats_reset(stats);
                cout << "Hash 1:" << endl;
                by_bloom(dictionary, board, 1, stats);
                stats_print(stats, k);
            }
            else if (order2 == 2) {
                stats_reset(stats);
                cout << "Hash 2:" << endl;
                by_bloom(dictionary, board, 2, stats);
                stats_print(stats, k);
            }
            else cout << "No existe esa opcion" << endl;
        }
        else cout << "No existe esa opcion" << endl;
        cout << endl;
        cout << "Que algoritmo deseas probar?" << endl;
        cout << "0 - Naive (voraz que mira palabras iterativamente)" << endl;
        cout << "1 - Naive2 (voraz que recorre el tablero iterativamente buscando palabras en DFS)" << endl;
        cout << "2 - Trie (busca palabras en DFS, usa un Trie para consultar en el diccionario)" << endl;
        cout << "3 - Hash (busca palabras en DFS, hay varios Hashes para consultar )" << endl;
        cout << "4 - Terminar ejecucion" << endl;
    }
}
