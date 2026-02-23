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
        
    } Vector4f;

    typedef struct{
        union{ // Nos permite hacer acceso directo matrix[0] seria lo mismo en memoria que matrixVect[0].x
            float matrix[16]; 
            float matrix2D[4][4];
            Vector4f matrixVec[4];
        };
    } Matrix4x4f;

    Vector4f makeVector4(float x, float y, float z, float w);
    Vector4f normalize(Vector4f v);
    float dotProduct(Vector4f v1, Vector4f v2);
    Vector4f operator +(Vector4f v1, Vector4f v2);
    Vector4f operator -(Vector4f v1, Vector4f v2);
    Vector4f operator *(Vector4f v1, Vector4f v2);
    Vector4f operator*(Vector4f v1, float v2);
    Vector4f operator*(float v2, Vector4f v1);

    
    Matrix4x4f makeIdentityf();
    Matrix4x4f makeTraslate(float x, float y, float z);
    Matrix4x4f makeRotate(float roll, float pitch, float yaw);
    Matrix4x4f makeScale(float x, float y, float z);
    Matrix4x4f operator+(Matrix4x4f m1, Matrix4x4f m2);
    Matrix4x4f operator-(Matrix4x4f m1, Matrix4x4f m2);
    Matrix4x4f operator*(Matrix4x4f m1, Matrix4x4f m2);
    Vector4f operator*(Matrix4x4f m, Vector4f v);
    Matrix4x4f operator*(Matrix4x4f m, float n);
    Matrix4x4f transpose(Matrix4x4f m);
    float determinant4x4(Matrix4x4f m);
    float determinant3x3(float a0, float b0, float c0, float a1, float b1, float c1, float a2, float b2, float c2);
    Matrix4x4f inverse(Matrix4x4f m);

    
    Vector4f makeQuaternion(float x, float y, float z, float angle);
    Matrix4x4f makeRotate(Vector4f quaternion);
}
