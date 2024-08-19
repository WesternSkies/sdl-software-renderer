
#include "../headers/define.h"
#include "../headers/draw.h"
#include "../headers/draw3d.h"

//float cam_pos.x = 0.0, cam_pos.y = 0.0, cam_pos.z = 200.0;
vec3 cam_pos = {-55.0f, 0.0f, 0.0f};
vec2 cam_rot = {0.0f, 0.0f};
vec2 cam_rot_speed = {0.0f, 0.0f};

float x_speed, y_speed = -1, z_speed;
//float cam_rot.x = 0.0 ,cam_rot.y = 0.0;
//float cam_rot_speed.x = 0.0 ,cam_rot_speed.y = 0.0;
float draw_dist = 10000.0;
float cam_speed = 3.0;
float zbuffer[WIDTH*HEIGHT];
clock_t start;
clock_t end;
float fps;
float average;
float high = 0;
float low = 1000;

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH,
                                        HEIGHT,
                                        0);
  SDL_Surface *window_surface = SDL_GetWindowSurface(window);
  unsigned int *pixels = window_surface->pixels;
  int x = 10, y = 30, width = window_surface->w, height = window_surface->h;
  

  Uint32 pixel = SDL_MapRGBA(window_surface->format, 200, 130, 100, 255);
  Uint8 r, g, b, a;

  SDL_GetRGBA(pixel, window_surface->format, &r, &g, &b, &a);



  uint8_t ticker = 0;
  uint16_t ticker2 = 0;
  rgb color[] = {
      {255,   0,   0 }, // Red
      {  0, 255,   0 }, // Green
      {  0,   0, 255 }, // Blue
      {255,   0, 255 }, // Purple
      {255,   255, 255},// White
      {0,   255, 255 }, // Cyan
      {255,   255, 0},  // Yellow
      {240,   150, 9},  // Orange
      {140,   191, 38}, // Lime
      {255,   255, 127},// Tan
  };

  /* Main Loop */
  while (1)
  {
    SDL_Event event;
    /* Input Handling */
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) exit(0);
      if (event.type == SDL_WINDOWEVENT) { /* Redraw if resized */
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
          window_surface = SDL_GetWindowSurface(window);
          pixels = window_surface->pixels;
        }
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_s:
             z_speed = 2*cos(RAD(cam_rot.x));
             x_speed = -2*sin(RAD(cam_rot.x));
             break;
            case SDLK_d:
             z_speed = -2*sin(RAD(cam_rot.x));
             x_speed = -2*cos(RAD(cam_rot.x));
             break;
            case SDLK_w:
             z_speed = -2*cos(RAD(cam_rot.x));
             x_speed = 2*sin(RAD(cam_rot.x));
             break;
            case SDLK_a:
             z_speed = 2*sin(RAD(cam_rot.x));
             x_speed = 2*cos(RAD(cam_rot.x));
             break;
            case SDLK_SPACE:
             y_speed = 1;
             break;
            case SDLK_LSHIFT:
             y_speed = -1;
             break;
            case SDLK_RIGHT:
             cam_rot_speed.x = -1.0;
             break;
            case SDLK_LEFT:
             cam_rot_speed.x = 1.0;
            default:
             break;
            case SDLK_UP:
             cam_rot_speed.y = -1.0;
             break;
            case SDLK_DOWN:
             cam_rot_speed.y = 1.0;
             break;
        }
      }
      if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
             x_speed = 0;
             z_speed = 0;
             break;
            case SDLK_a:
             x_speed = 0;
             z_speed = 0;
             break;
            case SDLK_s:
             z_speed = 0;
             x_speed = 0;
             break;
            case SDLK_d:
             x_speed = 0;
             z_speed = 0;
             break;
            case SDLK_SPACE:
             y_speed = 0;
             break;
            case SDLK_LSHIFT:
             y_speed = 0;
             break;
            case SDLK_RIGHT:
             cam_rot_speed.x = 0;
             break;
            case SDLK_LEFT:
             cam_rot_speed.x = 0;
             break;
            case SDLK_UP:
             cam_rot_speed.y = 0;
             break;
            case SDLK_DOWN:
             cam_rot_speed.y = 0;
             break;
            default:
             break;
        }
      }
    }

    SDL_UpdateWindowSurface(window);

    /* Ticking */
    start = clock();
    ticker++;
    ticker2++;
    if (ticker > 8) {
      for (y = 0; y < height; ++y) {
        for (x = 0; x < width; ++x) {
          pixels[x + y * width] = 0;
          zbuffer[x + y * width] = draw_dist;
        }
    }
    if (ticker2 > 3600) {
        cam_pos.x = 0;
        cam_pos.y = 0;
        cam_pos.z = 0;
        cam_rot.x = 0;
        cam_rot.y = 0;
        ticker2 = 0;
    }


    /* Anim */
    z_speed = -2*sin(RAD(cam_rot.x));
    x_speed = -2*cos(RAD(cam_rot.x));
    if (cam_pos.y < -200) {
        y_speed = 1.5;
        cam_rot_speed.y = 0.25;
    }
    else if (cam_pos.y > 200) {
        y_speed = -1.5;
        cam_rot_speed.y = -0.25;
    }
    cam_rot_speed.x = 1;


    /* Update Camera Speed */
    cam_pos.x += x_speed;
    cam_pos.y += y_speed;
    cam_pos.z += z_speed;
    if (cam_rot.x > 180) cam_rot.x = -180;
    if (cam_rot.x < -180) cam_rot.x = 180;
    cam_rot.x += cam_rot_speed.x;
    cam_rot.y += cam_rot_speed.y;
    /* Testing Code */
    vec3 pos = {cam_pos.x, cam_pos.y, cam_pos.z+100};
    vec3 size = {50, 50, 50};
    /* Front Face */
    pos.y = cam_pos.y;
    pos.x = cam_pos.x;
    pos.z = cam_pos.z+55;
    for (int y = 0; y < 3; y++) {
        pos.x = cam_pos.x;
        for (int x = 0; x < 3; x++) {
            cube3dtoggle(pos, cam_pos, cam_rot, size, color[0], pixels, zbuffer,1,0,0,0,0,0);
            pos.x+=55;
        }
        pos.y+=55;
    }
    /* Back Face */
    pos.y = cam_pos.y;
    pos.x = cam_pos.x;
    pos.z += 120;
    for (int y = 0; y < 3; y++) {
        pos.x = cam_pos.x;
        for (int x = 0; x < 3; x++) {
            cube3dtoggle(pos, cam_pos, cam_rot, size, color[1], pixels, zbuffer,0,1,0,0,0,0);
            pos.x+=55;
        }
        pos.y+=55;
    }
    /* Left Face */
    pos.y = cam_pos.y;
    pos.x = cam_pos.x+110;
    for (int y = 0; y < 3; y++) {
        pos.z = cam_pos.z+170;
        for (int z = 0; z < 3; z++) {
            cube3dtoggle(pos, cam_pos, cam_rot, size, color[6], pixels, zbuffer,0,0,0,1,0,0);
            pos.z-=55;
        }
        pos.y+=55;
    }
    /* Right Face */
    pos.y = cam_pos.y;
    pos.x = cam_pos.x;
    for (int y = 0; y < 3; y++) {
        pos.z = cam_pos.z+170;
        for (int z = 0; z < 3; z++) {
            cube3dtoggle(pos, cam_pos, cam_rot, size, color[2], pixels, zbuffer,0,0,1,0,0,0);
            pos.z-=55;
        }
        pos.y+=55;
    }
    /* Top Face */
    pos.y = cam_pos.y-5;
    pos.x = cam_pos.x;
    for (int x = 0; x < 3; x++) {
        pos.z = cam_pos.z+170;
        for (int z = 0; z < 3; z++) {
            cube3dtoggle(pos, cam_pos, cam_rot, size, color[4], pixels, zbuffer,0,0,0,0,1,0);
            pos.z-=55;
        }
        pos.x+=55;
    }
    /* Bottom Face */
    pos.y = cam_pos.y+115;
    pos.x = cam_pos.x;
    for (int x = 0; x < 3; x++) {
        pos.z = cam_pos.z+170;
        for (int z = 0; z < 3; z++) {
            cube3dtoggle(pos, cam_pos, cam_rot, size, color[7], pixels, zbuffer,0,0,0,0,0,1);
            pos.z-=55;
        }
        pos.x+=55;
    }
    //pos.x = cam_pos.x+70;
    //cube3d(pos, size, red, pixels);
    //pos.z = cam_pos.z+70;
    //cube3d(pos, size, red, pixels);
    //vec3 vecs[] = {
    //    {30,    0,       30}, /* Front of Feet */
    //    {0,     0,       30},
    //    {30,    30,      30},
    //    {0,     30,      30},
    //
    //    {90,     0,      30},
    //    {60,     0,      30},
    //    {90,    30,      30},
    //    {60,    30,      30},

    //    {0,    -60,      30}, /* Core */
    //    {90,   -60,      30},
    //
    //    {90,   -120,      30}, /* Forehead */
    //    {0,    -120,      30},
    //    {90,   -90,      30},
    //    {0,    -90,      30},
    //

    //    {30,    0,       90}, /* Back of feet */
    //    {0,     0,       90},
    //    {30,    30,      90},
    //    {0,     30,      90},
    //
    //    {90,     0,      90},
    //    {60,     0,      90},
    //    {90,    30,      90},
    //    {60,    30,      90},

    //
    //    {0,    -30,      90}, /* Back of Core */
    //    {90,   -30,      90},

    //    /* Backpack */
    //    {0,    -30,      120},
    //    {90,   -30,      120},
    //    {0,    -90,      120},
    //    {90,   -90,      120},

    //    /* Back of Head */
    //    {0,    -90,      90},
    //    {90,   -90,      90},
    //    {0,    -120,     90},
    //    {90,   -120,     90},

    //    /* Left Side */
    //    {0,        30,       30},
    //    {0,     -120,       30},
    //    {0,        30,       90},
    //    {0,     -120,       90},
    //
    //    /* Right Side */
    //    {90,       30,       30},
    //    {90,     -120,       30},
    //    {90,       30,       90},
    //    {90,     -120,       90},

    //    /* Scalp */
    //    {0,      -120,       30},
    //    {90,     -120,       30},
    //    {0,      -120,       90},
    //    {90,     -120,       90},
    //
    //    /* Left Backback side */
    //    {0,    -30,      120},
    //    {0,    -90,      120},
    //    {0,    -30,      90},
    //    {0,    -90,      90},
    //    /* Right Backback side */
    //    {90,    -30,      120},
    //    {90,    -90,      120},
    //    {90,    -30,      90},
    //    {90,    -90,      90},
    //    /* Top Backback side */
    //    {0,    -90,      120},
    //    {90,   -90,      120},
    //    {0,    -90,      90},
    //    {90,   -90,      90},
    //    /* Bottom Backback side */
    //    {0,    -30,      120},
    //    {90,   -30,      120},
    //    {0,    -30,      90},
    //    {90,   -30,      90},
    //    /* Bottom Left Foot */
    //    {0,    30,       30},
    //    {0,    30,       90},
    //    {30,    30,       30},
    //    {30,    30,       90},
    //    /* Bottom Right Foot */
    //    {60,    30,       30},
    //    {60,    30,       90},
    //    {90,    30,       30},
    //    {90,    30,       90},
    //    /* Crotch */
    //    {30,    0,       30},
    //    {30,    0,       90},
    //    {60,    0,       30},
    //    {60,    0,       90},
    //    /* Inner Left Leg */
    //    {30,    0,       30},
    //    {30,    0,       90},
    //    {30,    30,       30},
    //    {30,    30,       90},
    //    /* Inner Right Leg */
    //    {60,    0,       30},
    //    {60,    0,       90},
    //    {60,    30,       30},
    //    {60,    30,       90},

    //    /* Front Glass */
    //    {0,     -60,     0},
    //    {0,     -90,     0},
    //    {90,     -60,     0},
    //    {90,     -90,     0},
    //    /* Left Glass */
    //    {0,     -60,     0},
    //    {0,     -90,     0},
    //    {0,     -60,     30},
    //    {0,     -90,     30},
    //    /* Right Glass */
    //    {90,     -60,     0},
    //    {90,     -90,     0},
    //    {90,     -60,     30},
    //    {90,     -90,     30},
    //    /* Top Glass */
    //    {0,     -90,     0},
    //    {0,     -90,     30},
    //    {90,    -90,     0},
    //    {90,    -90,     30},
    //    /* Bottom Glass */
    //    {0,     -60,     0},
    //    {0,     -60,     30},
    //    {90,    -60,     0},
    //    {90,    -60,     30},
    //};
    //int quads[][4] = {
    //    {0,1,2,3},
    //    {4,5,6,7},
    //    {9,8,4,1},
    //    {10,11,12,13},
    //    {16,17,14,15},
    //    {20,21,18,19},
    //    {22,23,15,18},
    //    {25,24,27,26},
    //    {29,28,31,30},
    //    {32,33,34,35},
    //    {37,36,39,38},
    //    {40,41,42,43},
    //    {45,44,47,46},
    //    {48,49,50,51},
    //    {53,52,55,54},
    //    {56,57,58,59},
    //    {60,61,62,63},
    //    {64,65,66,67},
    //    {68,69,70,71},
    //    {73,72,75,74},
    //    {76,77,78,79},
    //    {81,80,83,82},
    //    {84,85,86,87},
    //    {89,88,91,90},
    //    {93,92,95,94},
    //    {96,97,98,99},
    //};

    //quad3d(vecs[quads[0][0]], vecs[quads[0][1]],vecs[quads[0][2]],vecs[quads[0][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[1][0]], vecs[quads[1][1]],vecs[quads[1][2]],vecs[quads[1][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[2][0]], vecs[quads[2][1]],vecs[quads[2][2]],vecs[quads[2][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[3][0]], vecs[quads[3][1]],vecs[quads[3][2]],vecs[quads[3][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[4][0]], vecs[quads[4][1]],vecs[quads[4][2]],vecs[quads[4][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[5][0]], vecs[quads[5][1]],vecs[quads[5][2]],vecs[quads[5][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[6][0]], vecs[quads[6][1]],vecs[quads[6][2]],vecs[quads[6][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[7][0]], vecs[quads[7][1]],vecs[quads[7][2]],vecs[quads[7][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[8][0]], vecs[quads[8][1]],vecs[quads[8][2]],vecs[quads[8][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[9][0]], vecs[quads[9][1]],vecs[quads[9][2]],vecs[quads[9][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[10][0]], vecs[quads[10][1]],vecs[quads[10][2]],vecs[quads[10][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[11][0]], vecs[quads[11][1]],vecs[quads[11][2]],vecs[quads[11][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[12][0]], vecs[quads[12][1]],vecs[quads[12][2]],vecs[quads[12][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[13][0]], vecs[quads[13][1]],vecs[quads[13][2]],vecs[quads[13][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[14][0]], vecs[quads[14][1]],vecs[quads[14][2]],vecs[quads[14][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[15][0]], vecs[quads[15][1]],vecs[quads[15][2]],vecs[quads[15][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[16][0]], vecs[quads[16][1]],vecs[quads[16][2]],vecs[quads[16][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[17][0]], vecs[quads[17][1]],vecs[quads[17][2]],vecs[quads[17][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[18][0]], vecs[quads[18][1]],vecs[quads[18][2]],vecs[quads[18][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[19][0]], vecs[quads[19][1]],vecs[quads[19][2]],vecs[quads[19][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[20][0]], vecs[quads[20][1]],vecs[quads[20][2]],vecs[quads[20][3]], pixels, width, height, red, zbuffer);
    //quad3d(vecs[quads[21][0]], vecs[quads[21][1]],vecs[quads[21][2]],vecs[quads[21][3]], pixels, width, height, blue, zbuffer);
    //quad3d(vecs[quads[22][0]], vecs[quads[22][1]],vecs[quads[22][2]],vecs[quads[22][3]], pixels, width, height, blue, zbuffer);
    //quad3d(vecs[quads[23][0]], vecs[quads[23][1]],vecs[quads[23][2]],vecs[quads[23][3]], pixels, width, height, blue, zbuffer);
    //quad3d(vecs[quads[24][0]], vecs[quads[24][1]],vecs[quads[24][2]],vecs[quads[24][3]], pixels, width, height, blue, zbuffer);
    //quad3d(vecs[quads[25][0]], vecs[quads[25][1]],vecs[quads[25][2]],vecs[quads[25][3]], pixels, width, height, blue, zbuffer);

    ticker = 0; /* Tick Reset */
    }
    //low = (fps < low) ? fps : low;
    //high = (fps > high) ? fps : high;
  }
  //printf("\e[1;1H\e[2J");

}
