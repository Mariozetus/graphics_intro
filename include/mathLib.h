#pragma once
#include "common.h"
using namespace std;

namespace mathLib{

    typedef struct{
        union{ // Nos permite hacer acceso directo vec4float.v[0] seria lo mismo en memoria que vec4float.x
            struct{
                float x;
                float y;
                float z;
                float w;
            };
            float v[4];
        };
        
    } vec4float;

    typedef struct{
        union{ // Nos permite hacer acceso directo matrix[0] seria lo mismo en memoria que matrixVect[0].x
            float matrix[16]; 
            vec4float matrixVec[4];
        };
    }matrix4x4f;

    vec4float makeVector4(float x, float y, float z, float w);
    vec4float normalize(vec4float v);
    float dotProduct(vec4float v1, vec4float v2);
    vec4float operator +(vec4float v1, vec4float v2);
    vec4float operator -(vec4float v1, vec4float v2);
    vec4float operator *(vec4float v1, vec4float v2);

    
    matrix4x4f makeIdentityf();
    matrix4x4f makeTraslate(float x, float y, float z);
    matrix4x4f makeRotate(float roll, float pitch, float yaw);
    matrix4x4f makeScale(float x, float y, float z);
    matrix4x4f operator+(matrix4x4f m1, matrix4x4f m2);
    matrix4x4f operator-(matrix4x4f m1, matrix4x4f m2);
    matrix4x4f operator*(matrix4x4f m1, matrix4x4f m2);
    vec4float operator*(matrix4x4f m, vec4float v);
    matrix4x4f operator*(matrix4x4f m, float n);
    matrix4x4f transpose(matrix4x4f m);
    float determinant4x4(matrix4x4f m);
    float determinant3x3(float a0, float b0, float c0, float a1, float b1, float c1, float a2, float b2, float c2);
    matrix4x4f inverse(matrix4x4f m);

    
    vec4float makeQuaternion(float x, float y, float z, float angle);
    matrix4x4f makeRotate(vec4float quaternion);
}
