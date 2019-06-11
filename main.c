#include "vet02.c"
#include <stdio.h>

#define SEC_AS_NANO 1000000000.0

double ident_tempo(Matriz_V *mat)
{

    struct timespec ini, fim;
    clock_gettime(CLOCK_REALTIME, &ini);
    //SEU CODIGO VEM AQUI
    printf("Matriz Vet0: %d\n", eh_identidade0(mat));
    clock_gettime(CLOCK_REALTIME, &fim);
    double iniSec = ini.tv_sec + ini.tv_nsec / SEC_AS_NANO;
    double fimSec = fim.tv_sec + fim.tv_nsec / SEC_AS_NANO;

    return (fimSec - iniSec);
}
double ident_tempo01(Matriz_V *mat)
{

    struct timespec ini, fim;
    clock_gettime(CLOCK_REALTIME, &ini);
    //SEU CODIGO VEM AQUI
    printf("Matriz Vet1: %d\n", eh_identidade1(mat));
    clock_gettime(CLOCK_REALTIME, &fim);
    double iniSec = ini.tv_sec + ini.tv_nsec / SEC_AS_NANO;
    double fimSec = fim.tv_sec + fim.tv_nsec / SEC_AS_NANO;

    return (fimSec - iniSec);
}
double ident_tempo02(Matriz_V *mat)
{
   

    struct timespec ini, fim;
    clock_gettime(CLOCK_REALTIME, &ini);
    //SEU CODIGO VEM AQUI
    printf("Matriz Vet2: %d\n", eh_identidade2(mat));
    clock_gettime(CLOCK_REALTIME, &fim);
    double iniSec = ini.tv_sec + ini.tv_nsec / SEC_AS_NANO;
    double fimSec = fim.tv_sec + fim.tv_nsec / SEC_AS_NANO;

    return (fimSec - iniSec);
}
double ident_tempo03(Matriz_V *mat)
{
   

    struct timespec ini, fim;
    clock_gettime(CLOCK_REALTIME, &ini);
    //SEU CODIGO VEM AQUI
    printf("Matriz VetAVX: %d\n", eh_identidade3(mat));
    clock_gettime(CLOCK_REALTIME, &fim);
    double iniSec = ini.tv_sec + ini.tv_nsec / SEC_AS_NANO;
    double fimSec = fim.tv_sec + fim.tv_nsec / SEC_AS_NANO;

    return (fimSec - iniSec);
}
int main()
{
    Matriz_V *opa2 = gera_matriz(IDENTIDADE, 20000, 20000);
    // printf("%d\n", opa2->matriz[399999999]);
    printf("TempoAVX: %lf\n", ident_tempo03(opa2));
    printf("Tempo1: %lf\n", ident_tempo01(opa2));
    
}