#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    float x;
    float y;
} vec2_t;

typedef struct
{
    float x;
    float y;
    float z;
} vec3_t;

vec3_t rotate_x(vec3_t vec, float angle);
vec3_t rotate_y(vec3_t vec, float angle);
vec3_t rotate_z(vec3_t vec, float angle);

#endif