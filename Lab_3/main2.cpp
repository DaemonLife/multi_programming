/*
  Вариант 10. Массив А[5][5], максимальный элемент каждой строки
  массива поставить в конец соответствующей строке.
*/

#include <iostream>
#include <random>
#include <omp.h>

using namespace std;

void random_arr(int *p[], const int N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            p[i][j] = rand()%1000;
        }
    }
}

void print(int *p[], const int N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << p[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "\n";
}

int main() {

    int const N = 5; // arr size
    int arr[N][N]; // your arr 5x5
    int arr2[N][N]; // тот же массив, но для работы с однопоточным алгоритмом

    // указатели на массив, используемые для печати и случайного заполнения в функциях
    int *p[N];
    for (int i = 0; i < N; i++) {
        p[i] = arr[i];
    }
    random_arr(p, N); // случайное заполнение массива
    cout << "Your arr:\n" << endl;
    print(p, N); // printing arr

    // копирование массива arr в arr2
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            arr2[i][j] = arr[i][j];
        }
    }

    omp_set_dynamic(0); // статичный режим omp
    omp_set_num_threads(N); // задаем число потоков (при динамическом режиме это максимальное число, при статичном - текущее)

    int temp = 0; // временная переменная для перестановки элементов в массиве
    int max[2] = {0, 0}; // первое число - индекс максимального элемента в строке
    // второе - само максимальное число

    double start_time = omp_get_wtime( ); // The start time of multithreaded algorithm

    // начало параллельного алгоритма
#pragma omp parallel for // Multithreaded algorithm
    for (int i = 0; i < N; i++){
        max[1] = arr[i][0];
        for (int j = 0; j < N; j++){
            if (arr[i][j] > max[1]) {
                max[0] = j;
                max[1] = arr[i][j];
            }
        }
        // ставим в конец максимальное число,
        // то есть меняем последнее число в строке и максимальное местами
        temp = arr[i][N-1];
        arr[i][N-1] = max[1];
        arr[i][max[0]] = temp;
    }
    // конец параллельного алгоритма
    double end_time = omp_get_wtime( ); // The end_time time of multithreaded algorithm

    cout << "Accuracy of system timer: " << omp_get_wtick() << endl;
    cout << "Multithreaded algorithm running time: " << end_time - start_time << endl;

    // Single-threaded algorithm
    start_time = omp_get_wtime( ); // The start time of single-threaded algorithm
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (arr2[i][j] > max[1]) {
                max[0] = j;
                max[1] = arr2[i][j];
            }
        }
        // ставим в конец максимальное число,
        // то есть меняем последнее число в строке и максимальное местами
        temp = arr2[i][N-1];
        arr2[i][N-1] = max[1];
        arr2[i][max[0]] = temp;
    }
    //end_time single-threaded algorithm
    end_time = omp_get_wtime( ); // The end_time time of single-threaded algorithm

    cout << "Single-threaded algorithm running time: " << end_time-start_time << endl;

    cout << "\nSort result:\n" << endl;
    for (int i = 0; i < N; i++) {
        p[i] = arr[i];
    }
    print(p, N); // печать массива (arr и arr1 очевидно идентичны после сортировки, поэтому только arr)

return 0;
}

/*
    Для данной простой задачи использование параллельных алгоритмов неэффективно,
    работа программы намного быстрее при однопоточном режиме.
    Погрешность системного таймера незначительна для этой задачи.
*/
