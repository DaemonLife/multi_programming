/*
10. Сгенерировать массив из N строк,
содержащих случайные 300 цифр. Посчитать
число вхождений цифры "9" в каждой строке,
используя N потоков. Измерить время работы
программы для N =
5: 1193ms
10: 1967ms
20: 3553ms
30: 5737ms
*/

#include <iostream>
#include <thread>
#include <stdlib.h> // rand
#include <time.h> // time
#include <ctime> // program work time
#include <vector>

using namespace std;

void filling(int *p[], const int N, const int M){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            p[i][j] = rand();
        }
    }
}

void print(int *p[], const int N, const int M){
    for (int i = 0; i < N; i++){
        cout << i << ": ";
        for (int j = 0; j < M; j++){
            cout << p[i][j] << ", ";
        }
        cout << "\n";
    }
}

// finding of num 9
int finder(int *p, const int M, int i)
{
    cout << " === Start thread " << i << " === " << endl;
    int temp = 0;
    int count = 0;

    for (int j = 0; j < M; j++)
    {
        temp = p[j];
        while (temp > 0)
        {
            if ((temp%10) == 9) count++; // 9 is your num
            temp = (temp/(10));
        }
    }
    cout << " == End thread " << i << " [" << count << "] == " << endl;

    return 0;
}

vector <thread> threads;

int main(){

    int start_time =  clock();

    // random seed
    srand(time(NULL));

    const int M = 10000; // number of digits
    const int N = 4; // number of strings

    int matrix[N][M];

    // pointers massive for matrix
    int *p[N];
    for (int i = 0; i < N; i++) p[i] = matrix[i];

    filling(p, N, M); // random filling matrix
//    print(p, N, M); // printing matrix

    // start threads
    threads.resize(N);
    for (int i = 0; i < N; i++)
    {
        threads[i] = thread(finder, p[i], M, i);
    }

    // out of threads
    for (int i = 0; i < N; i++)
    {
        threads[i].join();
    }

    int end_time = clock();
    cout << "\nComplited for " << end_time - start_time << "ms." << endl;

    return 0;
}
