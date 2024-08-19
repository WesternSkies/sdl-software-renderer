#include "../headers/define.h"
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void fswap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}
