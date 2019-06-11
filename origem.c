#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IDENTIDADE 1
#define ALEATORIA 0
#define VETORIZADA 1
#define NORMAL 0

typedef struct matriz_normal
{
    int l;
    int c;
    int **matriz;
} Matriz_N;
Matriz_N *gera_matrizN(int tipo, int l, int c)
{
    Matriz_N *mat = (Matriz_N *)malloc(sizeof(Matriz_N));
    mat->matriz = (int **)malloc(sizeof(int *)*l);
    mat->l = l;
    mat->c = c;
    int i;
    for (i = 0; i < l; i++)
    {
        mat->matriz[i] = (int *)malloc(sizeof(int)*c);
    }
    if(tipo == IDENTIDADE)
    {
        int j;
        for(i = 0; i < l; i++)
        {
            for(j = 0; j < c; j++)
            {
                if(i == j)
                {
                    mat->matriz[i][j] = 1;
                }
                else
                {
                    mat->matriz[i][j] = 0;
                }
            }
        }
    }
    else if(tipo == ALEATORIA)
    {
        int j;
        srand((time(0)));
        for(i = 0; i < l; i++)
        {
            for(j = 0; j < c; j++)
            {
                mat->matriz[i][j] = rand()%(l*c);
            }
        }
    }
    return mat;   
}
int eh_identidadeN(Matriz_N *mat)
{
    int i, j;
    for (i = 0; i < mat->l; i++)
    {
        for (j = 0; j < mat->c; j++)
        {
            if(i == j && mat->matriz[i][j] != 1)
                return 0;
            else if(i != j && mat->matriz[i][j] != 0)
                return 0;
        }
    }
    return 1;
}
void printa_matrizN(Matriz_N *mat)
{
    int i, j;
    for(i = 0; i < mat->l; i++)
    {
        for(j = 0; j < mat->c; j++)
        {
            printf("%d ", mat->matriz[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    Matriz_N *opa = gera_matrizN(IDENTIDADE, 10000, 10000);
    clock_t tempo = clock();
    printf("Matriz Normal: %d\n", eh_identidadeN(opa));
    tempo = clock() - tempo;
    printf("Tempo: %lf\n", ((double) tempo / CLOCKS_PER_SEC));
    // printa_matrizV(opa);
}