/*

  Вариант 3.
  В массиве А(6,6) элементы каждого
  столбца расположить в порядке возрастания.

*/

#include <iostream>
#include <random>
#include <omp.h>

using namespace std;

void filling(int *p[], const int N, const int M){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            p[i][j] = rand()%100+1;
        }
    }
}

void print(int *p[], const int N, const int M){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cout << p[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {

    int const N = 6; // matrix size
    int matrix[N][N]; // your matrix 6x6

    // pointers massive for matrix
    int *p[N];
    for (int i = 0; i < N; i++) p[i] = matrix[i];

    cout << "Your matrix:\n" << endl;
    filling(p, N, N); // random filling matrix
    print(p, N, N); // printing matrix
    cout << "\n";

    omp_set_dynamic(0); // static threads
    omp_set_num_threads(6); // default num threads

    int temp = 0;
    bool changed_matrix = true; // Has the matrix been sorted? Values is True or False.
    double start_time = omp_get_wtime( ); // The start time of multithreaded algorithm

#pragma omp parallel for // Multithreaded algorithm
    for (int j = 0; j < N; ++j) {
        changed_matrix = true;
        temp = matrix[0][j];
        while (changed_matrix == true) {
            changed_matrix = false;
            for (int i = 0; i < N-1; ++i) {
                if (matrix[i+1][j] < matrix[i][j]) {
                    temp = matrix[i][j];
                    matrix[i][j] = matrix[i+1][j];
                    matrix[i+1][j] = temp;
                    changed_matrix = true;
                }
            }
        } // while
    } // for. end_time_time Multithreaded algorithm
    double end_time = omp_get_wtime( ); // The end_time time of multithreaded algorithm

    cout << "Accuracy of system timer: " << omp_get_wtick() << endl;
    cout << "Multithreaded algorithm running time: " << end_time - start_time << endl;

    start_time = omp_get_wtime( ); // The start time of single-threaded algorithm
    // Single-threaded algorithm
    for (int j = 0; j < N; ++j) {
        changed_matrix = true;
        temp = matrix[0][j];
        while (changed_matrix == true) {
            changed_matrix = false;
            for (int i = 0; i < N-1; ++i) {
                if (matrix[i+1][j] < matrix[i][j]) {
                    temp = matrix[i][j];
                    matrix[i][j] = matrix[i+1][j];
                    matrix[i+1][j] = temp;
                    changed_matrix = true;
                }
            }
        } // while
    } // for. end_time single-threaded algorithm
    end_time = omp_get_wtime( ); // The end_time time of single-threaded algorithm

    cout << "Single-threaded algorithm running time: " << end_time-start_time << endl;

    cout << "\nSort result:\n" << endl;
    for (int i = 0; i < N; i++) p[i] = matrix[i];
    print(p, N, N); // printing matrix

return 0;

}

/*
    Для данной простой задачи использование параллельных алгоритмов неэффективно,
    работа программы намного быстрее при однопоточном режиме.
    Погрешность системного таймера незначительна для этой задачи.

*/
