#include "vector.h"

#include <math.h>


float vector2d__mag(const vector2d_t a)
{
    return sqrt(a.i*a.i + a.j*a.j);
}

float vector2d__distance(const vector2d_t a, const vector2d_t b)
{
    const float i = a.i - b.i;
    const float j = a.j - b.j;

    return sqrt(i*i + j*j);
}

vector2d_t vector2d__add(const vector2d_t a, const vector2d_t b)
{
    vector2d_t c;

    c.i = a.i + b.i;
    c.j = a.j + b.j;

    return c;
}

vector2d_t vector2d__sub(const vector2d_t a, const vector2d_t b)
{
    vector2d_t c;

    c.i = a.i - b.i;
    c.j = a.j - b.j;

    return c;
}

vector2d_t vector2d__scale(const vector2d_t a, const float scalar)
{
    vector2d_t result = {.i = scalar * a.i, .j = scalar * a.j};
    return result;
}

float vector2d__dot_product(const vector2d_t a, const vector2d_t b)
{
    return a.i*b.i + a.j*b.j;
}

float vector3d__mag(const vector3d_t a)
{
    return sqrt(a.i*a.i + a.j*a.j + a.k*a.k);
}

float vector3d__distance(const vector3d_t a, const vector3d_t b)
{
    const float i = a.i - b.i;
    const float j = a.j - b.j;
    const float k = a.k - b.k;

    return sqrt(i*i + j*j + k*k);
}

vector3d_t vector3d__add(const vector3d_t a, const vector3d_t b)
{
    vector3d_t c;

    c.i = a.i + b.i;
    c.j = a.j + b.j;
    c.k = a.k + b.k;

    return c;
}

vector3d_t vector3d__sub(const vector3d_t a, const vector3d_t b)
{
    vector3d_t c;

    c.i = a.i - b.i;
    c.j = a.j - b.j;
    c.k = a.k - b.k;

    return c;
}

vector3d_t vector3d__scale(const vector3d_t a, const float scalar)
{
    vector3d_t result = {.i = scalar * a.i, .j = scalar * a.j, .k = scalar * a.k};
    return result;
}

float vector3d__dot_product(const vector3d_t a, const vector3d_t b)
{
    return a.i*b.i + a.j*b.j + a.k*b.k;
}

vector3d_t vector3d__cross_product(const vector3d_t a, const vector3d_t b)
{
    vector3d_t c;

    c.i = a.j*b.k - a.k*b.j;
    c.j = a.k*b.i - a.i*b.k;
    c.k = a.i*b.j - a.j*b.i;

    return c;
}
