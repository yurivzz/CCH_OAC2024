#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>


double f(double x) {
    return sin(x);
} 

double trapezoidal_rule_parallel(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}

int main(int argc, char * argv[]) {
    double a = 0.0; // limite inferior 
    double b = M_PI; // limite superior
    int slices = atoi(argv[2]); // definindo o numero de trapézios
    omp_set_num_threads(atoi(argv[1]));
    clock_t start = clock();
    double result = trapezoidal_rule_parallel(a, b, slices);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%.8f\n", result);
    printf("%f\n", cpu_time_used);
    printf("%li\n", (end-start));
    return 0;
}