#include "vet02.c"
#include "origem.c"
#include <stdio.h>

#define SEC_AS_NANO 1000000000.0

double ident_tempoN(Matriz_N *mat)
{

    struct timespec ini, fim;
    clock_gettime(CLOCK_REALTIME, &ini);
    //SEU CODIGO VEM AQUI
    printf("Matriz Origem: %d\n", eh_identidadeN(mat));
    clock_gettime(CLOCK_REALTIME, &fim);
    double iniSec = ini.tv_sec + ini.tv_nsec / SEC_AS_NANO;
    double fimSec = fim.tv_sec + fim.tv_nsec / SEC_AS_NANO;

    return (fimSec - iniSec);
}
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
double ident_tempo04(Matriz_V *mat)
{
    struct timespec ini, fim;
    clock_gettime(CLOCK_REALTIME, &ini);
    //SEU CODIGO VEM AQUI
    printf("Matriz VetAVX2: %d\n", eh_identidade4(mat));
    clock_gettime(CLOCK_REALTIME, &fim);
    double iniSec = ini.tv_sec + ini.tv_nsec / SEC_AS_NANO;
    double fimSec = fim.tv_sec + fim.tv_nsec / SEC_AS_NANO;

    return (fimSec - iniSec);
}
int main()
{
    int i;
    for (i = 1000; i <= 5000; i+=1000)
    {
        printf("\n%iX%i\n\n", i, i);
        Matriz_N *opa1 = gera_matrizN(IDENTIDADE, i, i);
        Matriz_V *opa2 = gera_matriz(IDENTIDADE, i, i);
        // printf("%d\n", opa2->matriz[399999999]);
        printf("TempoAVX2: %lf\n", ident_tempo04(opa2));
        printf("TempoAVX: %lf\n", ident_tempo03(opa2));
        printf("Tempo1: %lf\n", ident_tempo01(opa2));
        printf("Tempo0: %lf\n", ident_tempo(opa2));
        printf("Tempo Origem: %lf\n", ident_tempoN(opa1));
    }
    
}