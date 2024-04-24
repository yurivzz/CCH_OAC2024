#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 1410065408 // Number of intervals

double f(double x) {
    return sin(x);
}

double trapezoidal_rule_sequential(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}

int main(int argc, char *argv[]) {
    double a = 0.0; // Lower limit
    double b = M_PI; // Upper limit
    int slices = atoi(argv[1]);
    clock_t start = clock();
    double result = trapezoidal_rule_sequential(a, b, slices);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Result: %.8f\n", result);
    printf("Execution Time(s): %f \n", cpu_time_used);
    printf("Clocks: %li\n", (end-start));
    return 0;
}