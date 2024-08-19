#ifndef DRAW_3D_H_
#define DRAW_3D_H_
#include "define.h"
#include "draw.h"

//float getZ(int x, int y, int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3);
void fill3d (int x, int y, int *display, int width, int height, int color, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float zbuffer[WIDTH*HEIGHT]);
void trifill3d(vec3 v1, vec3 v2, vec3 v3, vec3 cam_pos, vec2 cam_rot, uint32_t *display, int width, int height, rgb color, float zbuffer[]);
void quad3d(vec3 v1, vec3 v2, vec3 v3, vec3 v4,vec3 cam_pos, vec2 cam_rot, uint32_t *display, int width, int height, rgb color, float zbuffer[]);
void line3d(float x1, float y1, float z1, float x2, float y2, float z2, uint32_t *display, int width, int height, rgb color, float zbuffer[WIDTH*HEIGHT]);
void cube3d(vec3 pos, vec3 cam_pos, vec2 cam_rot, vec3 size, rgb color, uint32_t *display, float zbuffer[]);
void cube3dtoggle(vec3 pos, vec3 cam_pos, vec2 cam_rot, vec3 size, rgb color, uint32_t *display, float zbuffer[], bool zn, bool zp, bool xn, bool xp, bool yn, bool yp);


//void newTriFill3d(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int *display, int width, int height, int color, float zbuffer[]) {
#endif // DRAW_3D_H_
