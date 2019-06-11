#include <smmintrin.h>
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

#define INT 32
#define FLOAT 32
#define DOUBLE 64

int main()
{
    int *a = (int *)malloc(sizeof(int)*9);
    int i;
    for (i = 0; i < 9; i++)
        a[i] = -1;
    __m256i teste = _mm256_set1_epi32(0);
    __m256i teste2 = _mm256_load_si256(( __m256i *)&a[0]);
    teste2 = _mm256_hadd_epi32(teste2, teste2);
    teste2 = _mm256_hadd_epi32(teste2, teste2);
    teste2 = _mm256_abs_epi32(teste2);
    int sum = _mm256_extract_epi32(teste2, 0) + _mm256_extract_epi32(teste2, 7);
    printf("%d\n", sum);
    return 0;
}