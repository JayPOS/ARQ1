#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IDENTIDADE 1
#define ALEATORIA 0
#define VETORIZADA 1
#define NORMAL 0

typedef struct matriz_vetorizada
{
    int l;
    int c;
    int *matriz;
} Matriz_V;
int modulo(int a)
{
    if (a < 0)
        return (a * (-1));
    return a;
}
int soma_modulos(Matriz_V *mat)
{
    int i, j, soma = 0;
    int auxLin = mat->l;
    int auxCol = mat->c;
    for (i = 0; i < auxLin; i++)
    {
        for (j = 0; j < auxCol; j++)
            soma += mat->matriz[(i*auxLin)+j];
    }
    return soma;
}
Matriz_V *gera_matriz(int tipo, int l, int c)
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
int checa_diagonal(Matriz_V *mat)
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
int checa_quadrada(Matriz_V *mat)
{
    if(mat->l != mat->c)
    {
        return 0;
    }
    return 1;
}
int eh_identidade0(Matriz_V *mat)
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
int eh_identidade1(Matriz_V *mat)
{
    int i, j;
    int auxCol = mat->c;
    int auxLin = mat->l;
    int soma;
    if(checa_quadrada(mat))
    {
        for (i = 0; i < auxCol; i++)
        {
            if(mat->matriz[(i*auxCol)+i] != 1)
                return 0;
        }
        if(soma_modulos(mat) != auxLin)
            return 0;
        // for (i = 0; i < auxLin; i++)
        // {
        //     soma = 0;
        //     for(j = 0; j < auxCol; j++)
        //     {
        //         soma += mat->matriz[(i*auxLin)+j];
        //     }
        //     if(soma != 1)
        //         return 0;
        // }
    }
    else 
    {
        return 0;
    }
    return 1;
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
int main()
{    
    Matriz_V *opa2 = gera_matriz(IDENTIDADE, 10000, 10000);
    clock_t tempo = clock();
    printf("Matriz Vet1: %d\n", eh_identidade1(opa2));
    tempo = clock() - tempo;
    printf("Tempo: %lf\n", ((double) tempo / CLOCKS_PER_SEC));
    clock_t tempo2 = clock();
    printf("Matriz Vet0: %d\n", eh_identidade0(opa2));
    tempo2 = clock() - tempo2;
    printf("Tempo: %lf\n", ((double) tempo2 / CLOCKS_PER_SEC));
    
    // printa_matrizV(opa2);
}