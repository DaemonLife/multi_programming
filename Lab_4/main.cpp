/*

  Лаб.4. Вариант 2.
  Написать программу, которая приближенно вычисляет определнный интеграл по формуле прямоугольников.
  Подъинтегральную функцию задавать в виде отдельной функции, чтобы программа могла считать разные
  интегралы.Для распараллеливания использовать OpenMP.

*/

#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

double InFunction(double x) { // integrand
  return x*x;
}

int main() {

    int n = pow(10, 7); // number of iterations
    double a = 0; // start segment [a, b]
    double b = 10; // end segment [a, b]
    double result = 0; // result
    double h = (b - a) / n; // step

    // Multithread
    double start = omp_get_wtime(); // The start time of multithreaded algorithm
#pragma omp parallel shared(result, n, b, a, h)
    {
    double result_private = 0; // private variable of a specific thread
#pragma omp for
    for (int i = 0; i < n; i++) {
        result_private += InFunction(a + h * (i + 0.5));
    }
#pragma omp critical
{
    result += result_private; // combine all the private results into one
}
}
    result *= h;
    double end = omp_get_wtime(); // The end of multithreaded algorithm

    cout << "Multithreaded algorithm running time:\t" << end - start << endl;

    // Single-thread
    result = 0;
    start = omp_get_wtime(); // The start time of single-threaded algorithm
    for (int i = 0; i < n; i++) {
        result += InFunction(a + h * (i + 0.5));
    }
    result *= h;
    end = omp_get_wtime(); // The end of single-threaded algorithm

    cout << "Single-threaded algorithm running time:\t" << end - start << "\n" << endl;
    cout << "Result is " << result << endl;

    return 0;
}
/*

    Multithreaded algorithm running time:
    0.0436036

    Single-threaded algorithm running time:
    0.0772671
    Result is 333.333

    Если уменьшить итерации хотя бы на один порядок (10E6),
    параллельный алгоритм потеряет свой смысл из-за
    неэффективности перед однопоточным режимом.

*/
