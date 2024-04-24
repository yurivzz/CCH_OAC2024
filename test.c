#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define N 1410065408

double f(double x) {
    return sin(x);
} 

double trapezoidal_rule_parallel(double a, double b, int n) {
    double h = fabs(b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}

int main() {
    double a = 0.0; // Lower limit
    double b = M_PI; // Upper limit
    clock_t start = clock();
    double result = trapezoidal_rule_parallel(a, b, N);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Result: %.8f\n", result);
    printf("Parallel Execution Time: %f seconds\n", cpu_time_used);
    return 0;
}