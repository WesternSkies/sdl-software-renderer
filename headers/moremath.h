#ifndef MOREMATH_H_
#define MOREMATH_H_
#include "define.h"
#include "structs.h"
float getZ(float x, float y, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
vec3 lerp(vec3 v1, vec3 v2, float z);
vec3 calculateNormal(vec3 v1, vec3 v2, vec3 v3);
float dot(vec3 v1, vec3 v2);
float calculateAngle(float x1, float y1, float x2, float y2);
int rgb2hex(uint8_t r, uint8_t g, uint8_t b);
#endif //MOREMATH_H_
