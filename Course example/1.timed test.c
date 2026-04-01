#include<stdio.h>
#include<time.h>
#include<math.h>

static const int N = 100;// 多项式最大项数
static const int n = 1e7;// 计算的次数



double f1(int n, double a[], double x);
double f2(int n, double a[], double x);
void run_f(double (*f)(int, double*, double), double a[], double x);

int main()
{
    double a[N];// 多项式的系数
    double x = 1.1;// 多项式的自变量
    a[0] = 1.0;
    for(int i = 1; i < N; i++)
        a[i] = 1.0 / i;

    run_f(f1, a, x);
    run_f(f2, a, x);

    return 0;
}

double f1(int n, double a[], double x)
{
    double p = a[0];
    for(int i = 1; i <= n; i++){
        p += a[i] * pow(x, i);
    }
    return p;
}
double f2(int n, double a[], double x)
{
    double p = a[n];
    for(int i = n - 1; i >= 0; i--){
        p = a[i] + x * p;
    }
    return p;
}

void run_f(double (*f)(int, double*, double), double a[], double x){
    clock_t start, end;
    double duration;
    start = clock();
    for(int i = 0; i < n; i++)
        f(N -1, a, x);
    end = clock();
    duration = (double)(end - start) / CLK_TCK / n;
    printf("ticks(%s)=%f\n", f == f1 ? "f1" : "f2", (double)(end - start));
    printf("duration(%s)=%6.2e\n", f == f1 ? "f1" : "f2", duration);
}
