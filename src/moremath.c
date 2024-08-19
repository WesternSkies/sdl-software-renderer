#include "../headers/define.h"
float getZ(float x, float y, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {

    float abc = 0.5*(float)fabs(((x2-x1)*(y3-y1))-((x3-x1)*(y2-y1)));
    float pbc = 0.5*(float)fabs(((x2-x)*(y3-y))-((x3-x)*(y2-y)));
    float pac = 0.5*(float)fabs(((x1-x)*(y3-y))-((x3-x)*(y1-y)));
    float pab = 0.5*(float)fabs(((x1-x)*(y2-y))-((x2-x)*(y1-y)));
    float alpha = pbc/abc;
    float beta = pac/abc;
    float gamma = pab/abc;

    return (alpha*z1) + (beta*z2) + (gamma*z3);
}

vec3 lerp(vec3 v1, vec3 v2, float z) {
    vec3 result;
    float clip_distance;

    clip_distance = (fabs(z - v1.z)/(fabs(v2.z - v1.z)));

    result.x = v1.x + (v2.x - v1.x) * clip_distance;
    result.y = v1.y + (v2.y - v1.y) * clip_distance;
    result.z = v1.z + (v2.z - v1.z) * clip_distance;
    return result;
}

vec3 calculateNormal(vec3 v1, vec3 v2, vec3 v3) { 
    /* Edge Vectors */
   vec3 ab = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z}; 
   vec3 ac = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};
    
   /* Cross Product */
   vec3 n = {   
                (ab.y * ac.z) - (ab.z * ac.y),
                (ab.z * ac.x) - (ab.x * ac.z),
                (ab.x * ac.y) - (ab.y * ac.x)
   };
   float length = sqrt((n.x*n.x) + (n.y*n.y) + (n.z*n.z));

   n.x /= length;
   n.y /= length;
   n.z /= length;

   return n;
}
float dot(vec3 v1, vec3 v2) {
    return (v1.x*v2.x)+(v1.y*v2.y)+(v1.z*v2.z);
}

float calculateAngle(float x1, float y1, float x2, float y2) {
    return atan2f((y2-y1), (x2-x1));
}

int rgb2hex(uint8_t r, uint8_t g, uint8_t b) {
    return (65536*r)+(256*g)+b;
}
