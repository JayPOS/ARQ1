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
typedef struct matriz_vetorizada
{
    int l;
    int c;
    int *matriz;
} Matriz_V;
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
Matriz_V *gera_matrizV(int tipo, int l, int c)
{
    Matriz_V *mat = (Matriz_V *)malloc(sizeof(Matriz_V));
    mat->matriz = (int *)malloc(sizeof(int)*l*c);
    mat->l = l;
    mat->c = c;
    int i;
    if(tipo == IDENTIDADE)
    {
        
        int j;
        for(i = 0; i < l; i++)
        {
            for(j = 0; j < c; j++)
            {
                if(i == j)
                {
                    // printf("%d\n", ((i*l)+j));
                    mat->matriz[(i*l)+j] = 1;
                }
                else
                {
                    mat->matriz[(i*l)+j] = 0;
                }
            }
        }
    }
    else if(tipo == ALEATORIA)
    {
        srand((time(0)));
        for(i = 0; i < (l*c); i++)
        {
            mat->matriz[i] = rand()%(l*c);
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
int checa_diagonalV(Matriz_V *mat)
{
    int i, soma = 0;
    for(i = 0; i < mat->c; i++)
    {
        soma += mat->matriz[(i*mat->c)+i];
    }
    if(soma != mat->c)
        return 0;
    return 1;
}
int checa_quadradaV(Matriz_V *mat)
{
    if(mat->l != mat->c)
    {
        return 0;
    }
    return 1;
}
int eh_identidadeV(Matriz_V *mat)
{
    int i, j;
    // printf("Quad: %d // Diag: %d\n", checa_quadrada(mat), checa_diagonal(mat));
    if(checa_quadrada(mat) && checa_diagonal(mat))
    {
        for (i = 0; i < mat->l; i++)
        {
            for (j = 0; j < mat->c; j++)
            {
                if(i == j && mat->matriz[(i*mat->l)+j] != 1)
                    return 0;
                else if(i != j && mat->matriz[(i*mat->l)+j] != 0)
                    return 0;
            }
        }
        return 1;
    }
    return 0;
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
void printa_matrizV(Matriz_V *mat)
{
    int i, j;
    for(i = 0; i < mat->l; i++)
    {
        for(j = 0; j < mat->c; j++)
        {
            printf("%d ", mat->matriz[(i*mat->l)+j]);
        }
        printf("\n");
    }
}
