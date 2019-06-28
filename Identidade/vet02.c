#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <smmintrin.h>
#include <immintrin.h>

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
            soma += abs(mat->matriz[(i*auxLin)+j]);
    }
    return soma;
}
int soma_modulosAVX(Matriz_V *mat)
{
    int i, soma = 0;
    int auxTot = mat->l*mat->c;
    __m256i avx = _mm256_set1_epi32(0);
    // __m256i avx5;
    for (i = 0; i < auxTot; i+=8)
    {
        avx = _mm256_set1_epi32(0);
        avx = _mm256_loadu_si256(( __m256i *)&mat->matriz[i]);
        avx = _mm256_abs_epi32(avx);
        avx = _mm256_hadd_epi32(avx, avx);
        avx = _mm256_hadd_epi32(avx, avx);
        soma += (_mm256_extract_epi32(avx, 0) + _mm256_extract_epi32(avx, 7));
    }
    return soma;
}
int soma_modulosAVX2(Matriz_V *mat)
{
    int i, soma = 0;
    int auxTot = mat->l*mat->c;
    __m256i avx = _mm256_set1_epi32(0);
    __m256i avx2;
    __m256i avx3;
    __m256i avx4;
    // __m256i avx5;
    for (i = 0; i < auxTot; i+=32)
    {
        avx = _mm256_set1_epi32(0);
        avx = _mm256_loadu_si256(( __m256i *)&mat->matriz[i]);
        avx = _mm256_abs_epi32(avx);
        avx = _mm256_hadd_epi32(avx, avx);
        avx = _mm256_hadd_epi32(avx, avx);
        soma += (_mm256_extract_epi32(avx, 0) + _mm256_extract_epi32(avx, 7));
        avx2 = _mm256_set1_epi32(0);
        avx2 = _mm256_loadu_si256(( __m256i *)&mat->matriz[i+8]);
        avx2 = _mm256_abs_epi32(avx);
        avx2 = _mm256_hadd_epi32(avx, avx);
        avx2 = _mm256_hadd_epi32(avx, avx);
        soma += (_mm256_extract_epi32(avx, 0) + _mm256_extract_epi32(avx, 7));
        avx3 = _mm256_set1_epi32(0);
        avx3 = _mm256_loadu_si256(( __m256i *)&mat->matriz[i+16]);
        avx3 = _mm256_abs_epi32(avx);
        avx3 = _mm256_hadd_epi32(avx, avx);
        avx3 = _mm256_hadd_epi32(avx, avx);
        soma += (_mm256_extract_epi32(avx, 0) + _mm256_extract_epi32(avx, 7));
        avx4 = _mm256_set1_epi32(0);
        avx4 = _mm256_loadu_si256(( __m256i *)&mat->matriz[i+24]);
        avx4 = _mm256_abs_epi32(avx);
        avx4 = _mm256_hadd_epi32(avx, avx);
        avx4 = _mm256_hadd_epi32(avx, avx);
        soma += (_mm256_extract_epi32(avx, 0) + _mm256_extract_epi32(avx, 7));

        // printf("AA %d %d\n", i, auxLin*auxCol);
    }
    return soma;
}
int checa_linhas(Matriz_V *mat)
{
    int i, j;
    int auxLin = mat->l;
    // int aux;
    for (i = 0; i < auxLin; i++)
    {
        // aux = auxLin*i;
        for (j = 0; mat->matriz[(i*auxLin)+j] == 0; j++);
        if(i != j)
            return 0;
        for (j = auxLin-1; mat->matriz[(auxLin*i)+j] == 0; j--);
        if(i != j)
            return 0;
    }
    return 1;
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
    if(checa_quadrada(mat))
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
    int i;
    int auxCol = mat->c;
    int auxLin = mat->l;
    if(checa_quadrada(mat))
    {
        for (i = 0; i < auxCol; i+=2)
        {
            if(mat->matriz[(i*auxCol)+i] != 1)
                return 0;
            if(mat->matriz[((i+1)*auxCol)+(i+1)] != 1)
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
int eh_identidade2(Matriz_V *mat)
{
    int i;
    int auxCol = mat->c;
    // int auxLin = mat->l;
    if(checa_quadrada(mat))
    {
        for (i = 0; i < auxCol; i++)
        {
            if(mat->matriz[(i*auxCol)+i] != 1)
                return 0;
        }
        // if(soma_modulos(mat) != auxLin)
        //     return 0;
        // if (!checa_linhas(mat))
        //     return 0;
        return checa_linhas(mat);
    }
    else 
    {
        return 0;
    }
    return 1;
}
int eh_identidade3(Matriz_V *mat)
{
    int i;
    int auxCol = mat->c;
    int auxLin = mat->l;
    if(checa_quadrada(mat))
    {
        for (i = 0; i < auxCol; i++)
        {
            if(mat->matriz[(i*auxCol)+i] != 1)
                return 0;
        }
        if(soma_modulosAVX(mat) != auxLin)
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
int eh_identidade4(Matriz_V *mat)
{
     int i;
    int auxCol = mat->c;
    int auxLin = mat->l;
    if(checa_quadrada(mat))
    {
        for (i = 0; i < auxCol; i++)
        {
            if(mat->matriz[(i*auxCol)+i] != 1)
                return 0;
        }
        if(soma_modulosAVX2(mat) != auxLin)
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