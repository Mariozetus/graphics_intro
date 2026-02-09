#include "mathLib.h"

namespace mathLib{
    vec4float makeVector4(float x, float y, float z, float w){
        vec4float v = { x, y, z, w};
        return v;
    }

    vec4float normalize(vec4float v){
        float x2 = pow(v.x, 2);
        float y2 = pow(v.y, 2);
        float z2 = pow(v.z, 2);
        float modulus = sqrt(x2 + y2 + z2);

        if(modulus == 0)
            return v;

        return makeVector4(v.x / modulus, v.y / modulus, v.z / modulus, v.w);
    }

    float dotProduct(vec4float v1, vec4float v2){
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    vec4float operator +(vec4float v1, vec4float v2){
        vec4float vres = { 
            v1.x + v2.x,
            v1.y + v2.y,
            v1.z + v2.z,
            v1.w + v2.w,
        };
        return vres;

    }

    vec4float operator -(vec4float v1, vec4float v2){
        vec4float vres = { 
            v1.x - v2.x,
            v1.y - v2.y,
            v1.z - v2.z,
            v1.w - v2.w,
        };
        return vres;
    }

    vec4float operator *(vec4float v1, vec4float v2){
        vec4float vres = { 
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x,
            0,
        };
        return vres;
    }

    matrix4x4f makeIdentityf(){
        matrix4x4f m;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(i == j)
                    m.matrix[4 * i + j] = 1;
                else    
                    m.matrix[4 * i + j] = 0;
            }
        }
        return m;
    }
    
    matrix4x4f makeTranslate(float x, float y, float z){
        matrix4x4f m = makeIdentityf();
        m.matrixVec[0].w = x;
        m.matrixVec[1].w = y;
        m.matrixVec[2].w = z;
        return m;
    }

    /// @brief Rotacion con Euler
    /// @param roll rotacion en x 
    /// @param pitch rotacion en y
    /// @param yaw rotacion en z
    matrix4x4f makeRotate(float roll, float pitch, float yaw){
        matrix4x4f m;

        float sinRoll = sin(roll);
        float cosRoll = cos(roll);
        float sinPitch = sin(pitch);
        float cosPitch = cos(pitch);
        float sinYaw = sin(yaw);
        float cosYaw = cos(yaw);

        m.matrix[0] = cosPitch * cosYaw;
        m.matrix[1] = sinRoll * sinPitch * cosYaw - cosRoll * sinYaw;
        m.matrix[2] = cosRoll * sinPitch * cosYaw + sinRoll * sinYaw;
        m.matrix[3] = 0;

        m.matrix[4] = cosPitch * sinYaw;
        m.matrix[5] = sinRoll * sinPitch * sinYaw + cosRoll * cosYaw;
        m.matrix[6] = cosRoll * sinPitch * sinYaw - sinRoll * cosYaw;
        m.matrix[7] = 0;

        m.matrix[8] = -sinPitch;
        m.matrix[9] = sinRoll * cosPitch;
        m.matrix[10] = cosRoll * cosPitch;
        m.matrix[11] = 0;

        m.matrix[12] = 0;
        m.matrix[13] = 0;
        m.matrix[14] = 0;
        m.matrix[15] = 1;

        return m;
    }

    matrix4x4f makeScale(float x, float y, float z){
        matrix4x4f m = makeIdentityf();
        m.matrixVec[0].x = x;
        m.matrixVec[1].y = y;
        m.matrixVec[2].z = z;
        return m;
    }

    matrix4x4f operator+(matrix4x4f m1, matrix4x4f m2){
        matrix4x4f res;

        for(int i = 0; i < 4 ; i++){
            for(int j = 0; j < 4; j++){
                res.matrix[i * 4 + j] = m1.matrix[i * 4 + j] + m2.matrix[i * 4 + j];
            }
        }

        return res;
    }

    matrix4x4f operator-(matrix4x4f m1, matrix4x4f m2){
        matrix4x4f res;

        for(int i = 0; i < 4 ; i++){
            for(int j = 0; j < 4; j++){
                res.matrix[i * 4 + j] = m1.matrix[i * 4 + j] - m2.matrix[i * 4 + j];
            }
        }

        return res;
    }

    matrix4x4f operator*(matrix4x4f m1, matrix4x4f m2){
        matrix4x4f res;
        for(int i = 0; i < 4 ; i++){
            for(int j = 0; j < 4; j++){
                res.matrix[i * 4 + j] = 
                    m1.matrix[i * 4 + 0] * m2.matrix[0 * 4 + j] +
                    m1.matrix[i * 4 + 1] * m2.matrix[1 * 4 + j] +
                    m1.matrix[i * 4 + 2] * m2.matrix[2 * 4 + j] +
                    m1.matrix[i * 4 + 3] * m2.matrix[3 * 4 + j];
            }
        }
        
        return res;
    }

    vec4float operator*(matrix4x4f m, vec4float v){
        vec4float res;
        for(int i = 0; i < 4; i++){
            res.v[i] = 
                m.matrix[4 * i + 0] * v.x + 
                m.matrix[4 * i + 1] * v.y + 
                m.matrix[4 * i + 2] * v.z +
                m.matrix[4 * i + 3] * v.w;
        }

        return res;
    }

    matrix4x4f operator*(matrix4x4f m, float n){
        matrix4x4f res;
        
        for(int i = 0; i < 4 * 4; i++){
            res.matrix[i] = m.matrix[i] * n;
        }

        return res;
    }

    matrix4x4f transpose(matrix4x4f m){
        matrix4x4f res;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                res.matrixVec[i].v[j] = m.matrixVec[j].v[i]; 
            }
        }
        return res;
    }

    float getMinor(matrix4x4f m, int row, int col){
        float subMatrix3x3[9];
        int subIndex = 0;

        for(int i = 0; i < 4; i++){
            if(i == row) 
                continue;
            
            for(int j = 0; j < 4; j++){
                if(j == col)
                    continue;
                
                subMatrix3x3[subIndex] = m.matrix[i * 4 + j];
                subIndex++;
            }
        }

        return determinant3x3(subMatrix3x3[0], subMatrix3x3[1], subMatrix3x3[2], 
            subMatrix3x3[3], subMatrix3x3[4], subMatrix3x3[5], 
            subMatrix3x3[6], subMatrix3x3[7], subMatrix3x3[8]);
    }

    float determinant4x4(matrix4x4f m){
        float determinant = 0;

        for(int i = 0; i < 4; i++){
            float sign;
            if(i % 2 == 0)
                sign = 1;
            else
                sign = -1;
            
            determinant += sign * m.matrix[i] * getMinor(m, 0, i); 
        }

        return determinant;
    }

    float determinant3x3(float a0, float b0, float c0, float a1, float b1, float c1, float a2, float b2, float c2){
        return a0 * (b1 * c2 - b2 * c1) - b0 * (a1 * c2 - a2 * c1) + c0 * (a1 * b2 - a2 * b1);
    }

    matrix4x4f inverse(matrix4x4f m){
        float determinant = determinant4x4(m);

        matrix4x4f adjugate;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                float sign;
                if((i + j) % 2 == 0)
                    sign = 1;
                else    
                    sign = -1;

                adjugate.matrix[j * 4 + i] = sign * getMinor(m, i, j);
            }
        }

        return adjugate * (1.0f / determinant);
    }

    vec4float makeQuaternion(float x, float y, float z, float angle){
        vec4float vector = { x, y, z, 0 };
        vec4float normalizedVector = normalize(vector);

        float sinHalfAngle = sin(angle / 2);

        return vec4float{
            normalizedVector.x * sinHalfAngle,
            normalizedVector.y * sinHalfAngle,
            normalizedVector.z * sinHalfAngle,
           cos(angle)
        };
    }

    /// @brief Rotacion con quaternions
    /// @param quaternion 
    /// @return 
    matrix4x4f makeRotate(vec4float quaternion){
        matrix4x4f m;

        float x = quaternion.x;
        float y = quaternion.y;
        float z = quaternion.z;
        float w = quaternion.w;
        
        float x2 = pow(x, 2);
        float y2 = pow(y, 2);
        float z2 = pow(z, 2);

        m.matrix[0]  = 1 - 2 * y2 - 2 * z2;
        m.matrix[1]  = 2 * x * y - 2 * z * w;
        m.matrix[2]  = 2 * x * z + 2 * y * w;
        m.matrix[3]  = 0;

        m.matrix[4]  = 2 * x * y + 2 * z * w;
        m.matrix[5]  = 1 - 2 * x2 - 2 * z2;
        m.matrix[6]  = 2 * y * z - 2 * x * w;
        m.matrix[7]  = 0;

        m.matrix[8]  = 2 * x * z - 2 * y * w;
        m.matrix[9]  = 2 * y * z + 2 * x * w;
        m.matrix[10] = 1 - 2 * x2 - 2 * y2;
        m.matrix[11] = 0;

        m.matrix[12] = 0;
        m.matrix[13] = 0;
        m.matrix[14] = 0;
        m.matrix[15] = 1;

        return m;
    }

}

