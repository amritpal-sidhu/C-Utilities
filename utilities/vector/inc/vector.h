#pragma once


typedef struct {

    float i;
    float j;

} vector2d_t;

typedef struct {

    float i;
    float j;
    float k;

} vector3d_t;

typedef struct {

    float theta;
    float phi;

} sphere_angles_t;


float vector2d__mag(const vector2d_t a);
float vector2d__distance(const vector2d_t a, const vector2d_t b);
vector2d_t vector2d__add(const vector2d_t a, const vector2d_t b);
vector2d_t vector2d__sub(const vector2d_t a, const vector2d_t b);
vector2d_t vector2d__scale(const vector2d_t a, const float scalar);
float vector2d__dot_product(const vector2d_t a, const vector2d_t b);

float vector3d__mag(const vector3d_t a);
float vector3d__distance(const vector3d_t a, const vector3d_t b);
vector3d_t vector3d__add(const vector3d_t a, const vector3d_t b);
vector3d_t vector3d__sub(const vector3d_t a, const vector3d_t b);
vector3d_t vector3d__scale(const vector3d_t a, const float scalar);
float vector3d__dot_product(const vector3d_t a, const vector3d_t b);
vector3d_t vector3d__cross_product(const vector3d_t a, const vector3d_t b);
