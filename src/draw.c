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
void fill (int x, int y, int *display, int width, int height, int color) {
  if (x < WIDTH && y < HEIGHT && x > 0 && y > 0) {
    if (display[x+y*width] != color ) {
      display[x+y*width] = color;
      fill(x+1, y, display, width, height, color);
      fill(x-1, y, display, width, height, color);
      fill(x, y+1, display, width, height, color);
      fill(x, y-1, display, width, height, color);
    }
  }
  else return;
}



void line (float x1, float y1, float x2, float y2, int *display, int width, int height, int color) {
  float xdiff, ydiff;
  float x,y;

  if (x2 >= x1) { /* xdiff */
    xdiff = x2-x1;
    x = x1;
    ydiff = y2-y1;
    y = y1;
  } else {
    xdiff = x1-x2;
    x = x2;
    ydiff = y1-y2;
    y = y2;
  }

  float length = sqrt((xdiff*xdiff) + (ydiff*ydiff));
  float radians = atan((float)ydiff/(float)xdiff);

  for (int i = 0; i <= (int)length+1; i++) {
    if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
      display[(int)x + (int)y * width] = color;

    x += (cos(radians) <= 1.0 && cos(radians) >= -1.0) ? cos(radians) : 1;
    y += (sin(radians) <= 1.0 && sin(radians) >= -1.0) ? sin(radians) : 1;
  }
}

void tri(float x1, float y1, float x2, float y2, float x3, float y3, int *display, int width, int height, int color) {
  line(x1, y1, x2, y2, display, width, height, color);
  line(x3, y3, x2, y2, display, width, height, color);
  line(x1, y1, x3, y3, display, width, height, color);
}

void trifill(float x1, float y1, float x2, float y2, float x3, float y3, int *display, int width, int height, int color) {
  /* Distance */
  float xav,yav;

  float high_x, mid_x, low_x;

  high_x = x1;
  if (x2 > high_x) {
    mid_x = high_x;
    high_x = x2;
  } else {
    mid_x = x2;
  }
  if (x3 > mid_x) {
    if (x3 > high_x) {
      mid_x = high_x;
      high_x = x3;
    } else {
      low_x = mid_x;
      mid_x = x3;
    }
  } else {
    low_x = x3;
  }

  float high_y, mid_y, low_y;

  high_y = y1;

  if (y2 > high_y) {
    mid_y = high_y;
    high_y = y2;
  } else {
    mid_y = y2;
  }
  if (y3 > mid_y) {
    if (y3 > high_y) {
      mid_y = high_y;
      high_y = y3;
    } else {
      low_y = mid_y;
      mid_y = y3;
    }
  } else {
    low_y = y3;
  }
  xav = (x1+x2+x3) / 3;
  yav = (y1+y2+y3) / 3;
  tri(x1,y1,x2,y2,x3,y3, display, width, height, color);

  if (display[(int)xav + (int)yav*width] != color)
    fill((int)xav, (int)yav, display, width, height, color);
}

void newTriFill(int x1, int y1, int x2, int y2, int x3, int y3, int *display, int width, int height, int color) {

    int temp;

    /* Sort Vertices Vertically */
    if (y2 > y3) {
        temp = x2;
        x2 = x3;
        x3 = temp;
        temp = y2;
        y2 = y3;
        y3 = temp;
    }
    if (y1 > y2) {
        temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    if (y2 > y3) {
        temp = x2;
        x2 = x3;
        x3 = temp;
        temp = y2;
        y2 = y3;
        y3 = temp;
    }

    //printf("y3: %d\ny2: %d\ny1: %d\n", y3, y2, y1);
    
    
    

    /* Calculate Slopes */
    double slope1 = (double)(x2-x1) / (y2-y1+1);
    double slope2 = (double)(x3-x1) / (y3-y1+1);
    double slope3 = (double)(x3-x2) / (y3-y2+1);

    //double xf = x1;
    //double xt = x1 + slope1;

    for (int y = y1; y <= y3; y++) {
        int xStart, xEnd;
        //printf("xStart: %d\nxEnd: %d", xStart, xEnd);

        if (y < y2) {
            xStart = x1 + slope1 * (y - y1);
            xEnd = x1 + slope2 * (y - y1);
        } else {
            xStart = x2 + slope3 * (y - y2);
            xEnd = x1 + slope2 * (y - y1);
        }

        // Ensure xStart is less than xEnd
        if (xStart > xEnd) { int temp = xStart; xStart = xEnd; xEnd = temp; }
        if (xEnd > width) xEnd = width;
        for (int x = xStart; x <= xEnd; x++) {
            if (x >= width)
             break;
            else {
                if (x < 0) x = 0;
                display[y*width + x] = color;
            }
        }
    }
}


void newTriFill3d(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int *display, int width, int height, int color, float zbuffer[]) {


    /* Sort Vertices Vertically */
    if (y2 > y3) {
       swap(&x2, &x3); 
       swap(&y2, &y3);
    }
    if (y1 > y2) {
       swap(&x1, &x2); 
       swap(&y1, &y2);
    }
    if (y2 > y3) {
       swap(&x2, &x3); 
       swap(&y2, &y3);
    }

    //printf("y3: %d\ny2: %d\ny1: %d\n", y3, y2, y1);

    double slope2 = (double)(x3-x1) / (y3-y1+1);
    double slope1 = (double)(x2-x1) / (y2-y1+1);
    double slope3 = (double)(x3-x2) / (y3-y2+1);

    //double xf = x1;
    //double xt = x1 + slope1;


    // If y1 == y2, special case
    for (int y = y1; y <= y3; y++) {
        int xStart, xEnd;
        //printf("xStart: %d\nxEnd: %d", xStart, xEnd);

        if (y < y2) {
            xStart = x1 + slope1 * (y - y1);
            xEnd = x1 + slope2 * (y - y1);
        } else {
            xStart = x2 + slope3 * (y - y2);
            xEnd = x1 + slope2 * (y - y1);
        }

        // Ensure xStart is less than xEnd
        if (xStart > xEnd) { int temp = xStart; xStart = xEnd; xEnd = temp; }
        for (int x = xStart; x <= xEnd; x++) {
            display[y*width + x] = color;
        }
    }
}
