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
  int ntime = (stats.clock_end - stats.clock_begin - time * CLOCKS_PER_SEC) * 1000000000 / CLOCKS_PER_SEC;
  cout << "Tiempo transcurrido: " << time/60 << " minutos " << time%60 << " segundos " << ntime << " nanosegundos" << endl;
  cout << "Encontradas: " << stats.found << " de " << k << " palabras totales" << endl;
  cout << "Puntuacion: " << stats.score << endl;
  cout << "Comparaciones: " << stats.comparisons << endl;
  cout << "---------------" << endl;
}

int main()
{
    int archivo;
    int n, k, r1, r2, seed, tiempo;
    string file1, file2;
    Board::Stats stats;

    cout << "--------------------------------------------------------------------------" << endl;
    cout << "--------------------------------SUPERSOPA---------------------------------" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "Bienvenido a nuestra practica de Algorítmia." << endl;
    cout << "Quieres leer un tablero y un diccionario de archivos?" << endl;
    cout << "0 - No" << endl;
    cout << "1 - Si" << endl;
    cin >> archivo;
    if (archivo == 0) {
        cout << "Selecciona un tamaño para el tablero (N)" << endl;
        cin >> n;
        cout << "Selecciona un numero de palabras para el diccionario (K)" << endl;
        cin >> k;
        cout << "Rango de numeros para formar palabras (primero minimo, despues maximo)" << endl;
        cin >> r1 >> r2;
        cout << "Introduce una semilla (si es negativa se usara el tiempo local)" << endl;
        cin >> seed;
        cout << "Introduce el tiempo en segundos para resolver (0 para tiempo infinito)" << endl;
        cin >> tiempo;
        cout << "Escribe el nombre del archivo donde se guardara el tablero (las soluciones" << endl;
        cout << "de los algoritmos también utilizaran archivos con ese nombre añadiendo '_sol')" << endl;
        cout << "No pongas extension, el archivo tendra formato txt" << endl;
        cin >> file1;
        cout << "Escribe el nombre del archivo donde se guardaran las palabras del diccionario" << endl;
        cout << "No pongas extension, el archivo tendra formato txt" << endl;
        cin >> file2;
        cout << endl << "Generando... " << endl;
    }

    Board board(n,file1);
    Dictionary dictionary(k,r1,r2,file2);

    if (archivo == 1) {
        cout << "Introduce el nombre del archivo del tablero" << endl;
        cout << "No pongas extension, el archivo tiene que tener formato txt" << endl;
        cin >> file1;
        cout << "Introduce el nombre del archivo del diccionario" << endl;
        cout << "No pongas extension, el archivo tiene que tener formato txt" << endl;
        cin >> file2;
        cout << "Introduce el tiempo en segundos para resolver (0 para tiempo infinito)" << endl;
        cin >> tiempo;
        cout << endl << "Generando... " << endl;

        board = Board(file1);
        dictionary = Dictionary(file2);
    }
    else {
        board.generateBoard(seed);
        dictionary.generateWords(seed);
    }

    cout << "Listo." << endl << endl;

    cout << "Que algoritmo deseas probar?" << endl;
    cout << "0 - Naive (voraz que mira palabras iterativamente)" << endl;
    cout << "1 - Naive2 (voraz que recorre el tablero iterativamente buscando en DFS)" << endl;
    cout << "2 - Trie (busca palabras en DFS, usa un Trie para consultar en el diccionario)" << endl;
    cout << "3 - Hash (busca palabras en DFS, hay varios Hashes para consultar)" << endl;

    int option;
    cin >> option;
    while (option > 3 or option < 0) {
        cout << "No existe esa opcion" << endl;
        cin >> option;
    }
    if (option == 0) {
        stats_reset(stats);
        cout << endl << "Naive:" << endl;
        naive(dictionary,board,stats,tiempo);
        stats_print(stats, dictionary.getK());
        cout << endl;
    }
    else if (option == 1) {
        stats_reset(stats);
        cout << endl << "Naive2:" << endl;
        greedy(dictionary,board,stats,tiempo);
        stats_print(stats, dictionary.getK());
        cout << endl;
    }
    else if (option == 2) {
        stats_reset(stats);
        cout << "Trie:" << endl;
        trie_alg(dictionary,board,stats,tiempo);
        stats_print(stats, dictionary.getK());
        cout << endl;
    }
    else {
        cout << "Selecciona tipo de Hash:" << endl;
        cout << "0 - Suma de digitos modulo primo" << endl;
        cout << "1 - Suma de digitos por primo elevado a N" << endl;
        cout << "2 - Numero modulo primo" << endl;

        int option2;
        cin >> option2;
        while (option2 > 2 or option2 < 0) {
            cout << "No existe esa opcion" << endl;
            cin >> option2;
        }
        if (option2 == 0) {
            stats_reset(stats);
            cout << "Hash 0:" << endl;
            by_bloom(dictionary,board,0,stats,tiempo);
            stats_print(stats, dictionary.getK());
        }
        else if (option2 == 1) {
            stats_reset(stats);
            cout << "Hash 1:" << endl;
            by_bloom(dictionary,board,1,stats,tiempo);
            stats_print(stats, dictionary.getK());
        }
        else {
            stats_reset(stats);
            cout << "Hash 2:" << endl;
            by_bloom(dictionary,board,2,stats,tiempo);
            stats_print(stats, dictionary.getK());
        }
    }
    cout << endl;
}
