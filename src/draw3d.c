#include "../headers/define.h"
#include "../headers/draw.h"
#define FOV 200
#define NEARPLANE 10
#define FNAN 0.0/0.0

void line3d(float x1, float y1, float z1, float x2, float y2, float z2, vec2 cam_rot, uint32_t *display, int width, int height, int color, float zbuffer[WIDTH*HEIGHT]) {
  /* Normalize to Center of Screen */
  x1 -=CENTERX;
  x2 -=CENTERX;
  y1 -=CENTERY;
  y2 -=CENTERY;
  float sinY = sin(cam_rot.y*(M_PI/180));
  float cosY = cos(cam_rot.y*(M_PI/180));
  float sinX = sin(cam_rot.x*(M_PI/180));
  float cosX = cos(cam_rot.x*(M_PI/180));
  
  float temp_x1 = x1;
  float temp_x2 = x2;
  float temp_z1 = z1;
  float temp_z2 = z2;
  float temp_y1 = y1;
  float temp_y2 = y2;

  /* X Rotation */
  z1 = ((temp_z1*cosX)-(temp_x1*sinX));
  x1 = ((temp_z1*sinX)+(temp_x1*cosX));
  z2 = ((temp_z2*cosX)-(temp_x2*sinX));
  x2 = ((temp_z2*sinX)+(temp_x2*cosX));

  /* Y Rotation */
  temp_x2 = x2;
  temp_z1 = z1;
  temp_z2 = z2;
  y1 = ((temp_y1*cosY)-(temp_z1*sinY));
  z1 = ((temp_y1*sinY)+(temp_z1*cosY));
  y2 = ((temp_y2*cosY)-(temp_z2*sinY));
  z2 = ((temp_y2*sinY)+(temp_z2*cosY));

  if (z1 < NEARPLANE && z2 < NEARPLANE) return; /* If out of screen bounds, return */

  if (z1 < NEARPLANE) {
      vec3 v1;
      v1.x = x1; v1.y = y1; v1.z = z1;
      vec3 v2;
      v2.x = x2; v2.y = y2; v2.z = z2;
      v1 = lerp(v1, v2, NEARPLANE);
      x1 = v1.x; y1 = v1.y; z1 = v1.z;
  }
  if (z2 < NEARPLANE ) {
      vec3 v1;
      v1.x = x1; v1.y = y1; v1.z = z1;
      vec3 v2;
      v2.x = x2; v2.y = y2; v2.z = z2;
      v2 = lerp(v2, v1, NEARPLANE);
      x2 = v2.x; y2 = v2.y; z2 = v2.z;
  }

  x1 = FOV*(x1/z1); y1 = FOV*(y1/z1);
  x2 = FOV*(x2/z2); y2 = FOV*(y2/z2);

  x1 += CENTERX; y1 += CENTERY;
  x2 += CENTERX; y2 += CENTERY;
  
  float xdiff, ydiff, zdiff;
  float x,y,z;
  if (x2 >= x1) {
    xdiff = x2-x1; x = x1;
    ydiff = y2-y1; y = y1;
    zdiff = z2-z1; z = z1;
  } else {
    xdiff = x1-x2; x = x2;
    ydiff = y1-y2; y = y2;
    zdiff = z1-z2; z = z2;
  }
  float length  = sqrt((xdiff*xdiff) + (ydiff*ydiff));
  float radians = atan((float)ydiff/(float)xdiff);
 
  /* Render line */
  float cosr = cos(radians);
  float sinr = sin(radians);
  for (int i = 0; i <= (int)length+1 ; i++) {
    int arpos = (int)x + (int)y*width;
    if ( arpos < width*height && arpos > 0)
       if (z <= zbuffer[arpos] && x > 0 && y > 0 && x < WIDTH && y < HEIGHT & z > 0) {
           zbuffer[arpos] = z;
           display[arpos] = color;
       }
    x += (cosr <= 1.0 && cosr >= -1.0) ? cosr : 1;
    y += (sinr <= 1.0 && sinr >= -1.0) ? sinr : 1;
    z += zdiff / length;
  }

}
void trifill3d(vec3 v1, vec3 v2, vec3 v3, vec3 cam_pos, vec2 cam_rot, uint32_t *display, int width, int height, rgb color, float zbuffer[]) {
    /* ---------------------------------------------------------------------*/
    /* Declarations                                                         */
    /* ---------------------------------------------------------------------*/
    v1.x += cam_pos.x;
    v2.x += cam_pos.x;
    v3.x += cam_pos.x;

    v1.y += cam_pos.y;
    v2.y += cam_pos.y;
    v3.y += cam_pos.y;

    v1.z += cam_pos.z;
    v2.z += cam_pos.z;
    v3.z += cam_pos.z;
    float sinY = sin(cam_rot.y*(M_PI/180));
    float cosY = cos(cam_rot.y*(M_PI/180));
    float sinX = sin(cam_rot.x*(M_PI/180));
    float cosX = cos(cam_rot.x*(M_PI/180));
    vec3 tempv1 = v1;
    vec3 tempv2 = v2;
    vec3 tempv3 = v3;
    /* ---------------------------------------------------------------------*/
    /* Make 0,0 the center of the screen                                    */
    /* ---------------------------------------------------------------------*/
    v1.x -=CENTERX;
    v2.x -=CENTERX;
    v3.x -=CENTERX;
    v1.y -=CENTERY;
    v2.y -=CENTERY;
    v3.y -=CENTERY;
    /* ---------------------------------------------------------------------*/
    /* X Rotation                                                           */
    /* ---------------------------------------------------------------------*/
    v1.z = ((tempv1.z*cosX)-(tempv1.x*sinX));
    v1.x = ((tempv1.z*sinX)+(tempv1.x*cosX));
    v2.z = ((tempv2.z*cosX)-(tempv2.x*sinX));
    v2.x = ((tempv2.z*sinX)+(tempv2.x*cosX));
    v3.z = ((tempv3.z*cosX)-(tempv3.x*sinX));
    v3.x = ((tempv3.z*sinX)+(tempv3.x*cosX));
    /* ---------------------------------------------------------------------*/
    /* Y Rotation                                                           */
    /* ---------------------------------------------------------------------*/
    tempv1.x = v1.x;
    tempv2.x = v2.x;
    tempv3.x = v3.x;
    tempv1.z = v1.z;
    tempv2.z = v2.z;
    tempv3.z = v3.z;
    v1.y = ((tempv1.y*cosY)-(tempv1.z*sinY));
    v1.z = ((tempv1.y*sinY)+(tempv1.z*cosY));
    v2.y = ((tempv2.y*cosY)-(tempv2.z*sinY));
    v2.z = ((tempv2.y*sinY)+(tempv2.z*cosY));
    v3.y = ((tempv3.y*cosY)-(tempv3.z*sinY));
    v3.z = ((tempv3.y*sinY)+(tempv3.z*cosY));
    /* ---------------------------------------------------------------------*/
    /* Lighting                                                             */
    /* ---------------------------------------------------------------------*/
    vec3 centroid = {(v1.x+v2.x+v3.x)/3,(v1.y+v2.y+v3.y)/3,(v1.z+v2.z+v3.z)/3 };
    if (centroid.z < NEARPLANE) return; // Behind Camera. Return.
    vec3 normal = calculateNormal(v1, v2, v3);
    float normalSum = fabs(normal.x)+fabs(normal.y)+fabs(normal.z);
    color.r /= normalSum+(centroid.z/200);
    color.g /= normalSum+(centroid.z/200);
    color.b /= normalSum+(centroid.z/200);
    /* ---------------------------------------------------------------------*/
    /* Linear Interpolation                                                 */
    /* ---------------------------------------------------------------------*/
    if (v1.z < NEARPLANE)   v1 = lerp(v1, v2, NEARPLANE);
    if (v2.z < NEARPLANE)   v2 = lerp(v2, v1, NEARPLANE);
    if (v3.z < NEARPLANE)   v3 = lerp(v3, v1, NEARPLANE);
    /* ---------------------------------------------------------------------*/
    /* Finalizing Positions                                                 */
    /* ---------------------------------------------------------------------*/
    v1.x = FOV*(v1.x/v1.z);
    v1.y = FOV*(v1.y/v1.z);
    v2.x = FOV*(v2.x/v2.z);
    v2.y = FOV*(v2.y/v2.z);
    v3.x = FOV*(v3.x/v3.z);
    v3.y = FOV*(v3.y/v3.z);
    v1.y += CENTERY;
    v2.y += CENTERY;
    v3.y += CENTERY;
    v1.x += CENTERX;
    v2.x += CENTERX;
    v3.x += CENTERX;
    /* ---------------------------------------------------------------------*/
    /* If triangle is inside out, return */
    /* ---------------------------------------------------------------------*/
    if ((v2.x-v1.x)*(v3.y-v1.y)-(v3.x-v1.x)*(v2.y-v1.y) < 0) return; 
    /* ---------------------------------------------------------------------*/
    /* Out of Bounds Check */
    /* ---------------------------------------------------------------------*/
    if ((v1.x > width  || v1.x < 0) && (v2.x > width  || v2.x < 0) && (v3.x > width  || v3.x < 0)) return;
    if ((v1.y > height || v1.y < 0) && (v2.y > height || v2.y < 0) && (v3.y > height || v3.y < 0)) return;
    if (v1.z < NEARPLANE && v2.z < NEARPLANE && v3.z < NEARPLANE) return; /* Behind Camera Check */
    /* ---------------------------------------------------------------------*/
    /* Sort Vertices */
    /* ---------------------------------------------------------------------*/
    if (v2.y > v3.y) {
       fswap(&v2.x, &v3.x); 
       fswap(&v2.y, &v3.y);
    } if (v1.y > v2.y) {
       fswap(&v1.x, &v2.x); 
       fswap(&v1.y, &v2.y);
    } if (v2.y > v3.y) {
       fswap(&v2.x, &v3.x); 
       fswap(&v2.y, &v3.y);
    }
    /* ---------------------------------------------------------------------*/
    /* Prevents absurdly large position values                              */
    /* ---------------------------------------------------------------------*/
    if (isnan(v1.x) || isnan(v1.y) || isnan(v1.z) || isnan(v2.x) || isnan(v2.y) || isnan(v2.z) || isnan(v3.x) || isnan(v3.y) || isnan(v3.z)) return;
    /* ---------------------------------------------------------------------*/
    /* Rasterize */
    /* ---------------------------------------------------------------------*/
    double slope1 = (double)(v2.x-v1.x) / (v2.y-v1.y+1);
    double slope2 = (double)(v3.x-v1.x) / (v3.y-v1.y+1);
    double slope3 = (double)(v3.x-v2.x) / (v3.y-v2.y+1);

    for (int y = (int)v1.y; y <= (int)v3.y && y < height; y++) { 
        if (y <= 0) y = 1;
        if (y <= height) {
            int xStart, xEnd;

            if (y < (int)v2.y) {
                xStart = (int)v1.x + slope1 * (y - (int)v1.y);
                xEnd   = (int)v1.x + slope2 * (y - (int)v1.y);
            } else {
                xStart = (int)v2.x + slope3 * (y - (int)v2.y);
                xEnd   = (int)v1.x + slope2 * (y - (int)v1.y);
            }

            xEnd = (xEnd < 0) ? 0 : (xEnd > width) ? width-1 : xEnd;
            xStart = (xStart < 0) ? 0 : (xStart > width) ? width-1 : xStart;

            if (xStart > xEnd)   swap(&xStart, &xEnd);

            float z;
            for (int x = xStart; x <= xEnd; x++) {
                if (x >= width)
                    break;
                else
                    if (x < 0)
                      x = -1;
                    else if (x > 0 && x < width && y > 0 && y < height) {
                          z = getZ(x, y, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
                          if (z <= zbuffer[y*width+x] ) {
                            zbuffer[y*width+x] = z;
                            display[y*width+x] = rgb2hex(color.r, color.g, color.b);
                          }
                    }
            }
        } else break;
    }
    /* ---------------------------------------------------------------------*/
}

void quad3d(vec3 v1, vec3 v2, vec3 v3, vec3 v4, vec3 cam_pos, vec2 cam_rot, uint32_t *display, int width, int height, rgb color, float zbuffer[]) {
  trifill3d(v1, v3, v2, cam_pos, cam_rot, display, width, height, color, zbuffer);
  trifill3d(v2, v3, v4, cam_pos, cam_rot, display, width, height, color, zbuffer);
}

void cube3d(vec3 pos, vec3 cam_pos, vec2 cam_rot, vec3 size, rgb color, uint32_t *display, float zbuffer[]) {
    /* ---------------------------------------------------------------------*/
    /* -Z Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    vec3 v1; v1.x = pos.x;              v1.y = pos.y;           v1.z = pos.z;
    vec3 v2; v2.x = pos.x;              v2.y = pos.y+size.y;    v2.z = pos.z;
    vec3 v3; v3.x = pos.x+size.x;       v3.y = pos.y;           v3.z = pos.z;
    vec3 v4; v4.x = pos.x+size.x;       v4.y = pos.y+size.y;    v4.z = pos.z;
    quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    /* ---------------------------------------------------------------------*/
    /* +Z Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    v4.x = pos.x;        v1.y = pos.y;          v1.z = pos.z+size.z;
    v3.x = pos.x;        v2.y = pos.y+size.y;   v2.z = pos.z+size.z;      
    v2.x = pos.x+size.x; v3.y = pos.y;          v3.z = pos.z+size.z;           
    v1.x = pos.x+size.x; v4.y = pos.y+size.y;   v4.z = pos.z+size.z;    
    quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    /* ---------------------------------------------------------------------*/
    /* -X Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    v1.x = pos.x;        v1.y = pos.y;        v4.z = pos.z;
    v2.x = pos.x;        v2.y = pos.y+size.y; v3.z = pos.z;      
    v3.x = pos.x;        v3.y = pos.y;        v2.z = pos.z+size.z;           
    v4.x = pos.x;        v4.y = pos.y+size.y; v1.z = pos.z+size.z;    
    quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    /* ---------------------------------------------------------------------*/
    /* +X Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    v1.x = pos.x+size.x; v1.y = pos.y;        v1.z = pos.z;
    v2.x = pos.x+size.x; v2.y = pos.y+size.y; v2.z = pos.z;      
    v3.x = pos.x+size.x; v3.y = pos.y;        v3.z = pos.z+size.z;           
    v4.x = pos.x+size.x; v4.y = pos.y+size.y; v4.z = pos.z+size.z;    
    quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    /* ---------------------------------------------------------------------*/
    /* -Y Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    v1.x = pos.x;        v1.y = pos.y;        v1.z = pos.z;
    v2.x = pos.x+size.x; v2.y = pos.y;        v2.z = pos.z;      
    v3.x = pos.x;        v3.y = pos.y;        v3.z = pos.z+size.z;           
    v4.x = pos.x+size.x; v4.y = pos.y;        v4.z = pos.z+size.z;    
    quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    /* ---------------------------------------------------------------------*/
    /* +Y Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    v4.x = pos.x;        v4.y = pos.y+size.z; v1.z = pos.z;
    v3.x = pos.x+size.x; v3.y = pos.y+size.z; v2.z = pos.z;      
    v2.x = pos.x;        v2.y = pos.y+size.z; v3.z = pos.z+size.z;           
    v1.x = pos.x+size.x; v1.y = pos.y+size.z; v4.z = pos.z+size.z;    
    quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    /* ---------------------------------------------------------------------*/
}

void cube3dtoggle(vec3 pos, vec3 cam_pos, vec2 cam_rot, vec3 size, rgb color, uint32_t *display, float zbuffer[], bool zn, bool zp, bool xn, bool xp, bool yn, bool yp) {
    /* ---------------------------------------------------------------------*/
    /* Declaration */ 
    /* ---------------------------------------------------------------------*/
    vec3 v1; 
    vec3 v2; 
    vec3 v3; 
    vec3 v4; 
    /* ---------------------------------------------------------------------*/
    /* -Z Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    if (zn) {
        v1.x = pos.x;              v1.y = pos.y;           v1.z = pos.z;
        v2.x = pos.x;              v2.y = pos.y+size.y;    v2.z = pos.z;
        v3.x = pos.x+size.x;       v3.y = pos.y;           v3.z = pos.z;
        v4.x = pos.x+size.x;       v4.y = pos.y+size.y;    v4.z = pos.z;
        quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    }
    /* ---------------------------------------------------------------------*/
    /* +Z Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    if (zp) { 
        v4.x = pos.x;        v1.y = pos.y;          v1.z = pos.z+size.z;
        v3.x = pos.x;        v2.y = pos.y+size.y;   v2.z = pos.z+size.z;      
        v2.x = pos.x+size.x; v3.y = pos.y;          v3.z = pos.z+size.z;           
        v1.x = pos.x+size.x; v4.y = pos.y+size.y;   v4.z = pos.z+size.z;    
        quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    }
    /* ---------------------------------------------------------------------*/
    /* -X Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    if (xn) {
        v1.x = pos.x;        v1.y = pos.y;        v4.z = pos.z;
        v2.x = pos.x;        v2.y = pos.y+size.y; v3.z = pos.z;      
        v3.x = pos.x;        v3.y = pos.y;        v2.z = pos.z+size.z;           
        v4.x = pos.x;        v4.y = pos.y+size.y; v1.z = pos.z+size.z;    
        quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    }
    /* ---------------------------------------------------------------------*/
    /* +X Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    if (xp) {
        v1.x = pos.x+size.x; v1.y = pos.y;        v1.z = pos.z;
        v2.x = pos.x+size.x; v2.y = pos.y+size.y; v2.z = pos.z;      
        v3.x = pos.x+size.x; v3.y = pos.y;        v3.z = pos.z+size.z;           
        v4.x = pos.x+size.x; v4.y = pos.y+size.y; v4.z = pos.z+size.z;    
        quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    }
    /* ---------------------------------------------------------------------*/
    /* -Y Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    if (yn) {
        v1.x = pos.x;        v1.y = pos.y;        v1.z = pos.z;
        v2.x = pos.x+size.x; v2.y = pos.y;        v2.z = pos.z;      
        v3.x = pos.x;        v3.y = pos.y;        v3.z = pos.z+size.z;           
        v4.x = pos.x+size.x; v4.y = pos.y;        v4.z = pos.z+size.z;    
        quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    }
    /* ---------------------------------------------------------------------*/
    /* +Y Face                                                              */ 
    /* ---------------------------------------------------------------------*/
    if (yp) {
        v4.x = pos.x;        v4.y = pos.y+size.z; v1.z = pos.z;
        v3.x = pos.x+size.x; v3.y = pos.y+size.z; v2.z = pos.z;      
        v2.x = pos.x;        v2.y = pos.y+size.z; v3.z = pos.z+size.z;           
        v1.x = pos.x+size.x; v1.y = pos.y+size.z; v4.z = pos.z+size.z;    
        quad3d(v1, v2, v3, v4, cam_pos, cam_rot, display, WIDTH, HEIGHT, color, zbuffer);
    }
    /* ---------------------------------------------------------------------*/
}
