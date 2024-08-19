#ifndef DRAW_H_
#define DRAW_H_
#include "define.h"
void swap(int *a, int *b);
void fswap(float *a, float *b);
void fill (int x, int y, int *display, int width, int height, int color);
void line (float x1, float y1, float x2, float y2, int *display, int width, int height, int color); 
void tri(float x1, float y1, float x2, float y2, float x3, float y3, int *display, int width, int height, int color); 
void trifill(float x1, float y1, float x2, float y2, float x3, float y3, int *display, int width, int height, int color); 
void newTriFill(int x1, int y1, int x2, int y2, int x3, int y3, int *display, int width, int height, int color);
#endif // DRAW_H_
