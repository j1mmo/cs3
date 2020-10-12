#pragma once
#include <math.h> // remember to add _USE_MATH_DEFINES to the project settings
#include <memory.h>
#include <stdio.h>

/*
  All 4x4 matrices are assumed to be stored as a 1D array as illustrated below:
  m[0] m[4] m[8]  m[12]
  m[1] m[5] m[9]  m[13]
  m[2] m[6] m[10] m[14]
  m[3] m[7] m[11] m[15]
  */
class Matrix
{
public:
  // Sets up the indentify matrix
  static void setIdentity(float* matrix);

  // Multiplies the lhs matrix by the rhs matrix and stores the result in result: result = lhs x rhs
  static void multiplyMatrix(float* result, const float* lhs, const float* rhs);

  // Applys a translation matrix to the matrix provided.  The result is stored back in the same block of memory)
  // e.g. matrix = matrix x translation (where the translation matrix is created using tx, ty, and tz to represent the translation vector
  static void translate(float* matrix, const float tx, const float ty, const float tz);

  // Applys a scale matrix to the matrix provided.  The result is stored back in the same block of memory
  // e.g. matrix = matrix x scale (where the scale matrix is created using sx, sy, and sz to represent the axis scaling values)
  static void scale(float* matrix, const float sx, const float sy, const float sz);

  // Applys a rotation about the x-axis matrix to the matrix provided.  The result is stored back in the same block of memory
  // e.g. matrix = matrix x rotationX (where the rotation matrix is created by the angle provided in degrees)
  static void rotateX(float* matrix, const float degs);

  // Applys a rotation about the y-axis matrix to the matrix provided.  The result is stored back in the same block of memory
  // e.g. matrix = matrix x rotationY (where the rotation matrix is created by the angle provided in degrees)
  static void rotateY(float* matrix, const float degs);

  // Applys a rotation about the z-axis matrix to the matrix provided.  The result is stored back in the same block of memory
  // e.g. matrix = matrix x rotationZ (where the rotation matrix is created by the angle provided in degrees)
  static void rotateZ(float* matrix, const float degs);

private:
  // helper method to convert between degrees and radians
  static float degreesToRadians(const float degrees);
};

inline float Matrix::degreesToRadians(const float degrees)
{
  return degrees*(float) (M_PI/180.0);
}

inline void Matrix::setIdentity(float* matrix)
{
  memset(matrix, 0, sizeof(float)*16);
  matrix[0]=matrix[5]=matrix[10]=matrix[15]=1;
}

inline void Matrix::multiplyMatrix(float* result, const float* lhs, const float* rhs)
{
    memset(result, 0, sizeof(float)*16);
    for(size_t row = 0; row < 4; row++){
	for(size_t col = 0; col < 4; col++){
	    for(size_t traverse = 0; traverse < 4; traverse++){
		result[row + 4*col] += lhs[row + 4*traverse] * rhs[traverse + 4*col]; 
	    }
	}
    }
}

inline void Matrix::translate(float* matrix, const float tx, const float ty, const float tz)
{
    float copy[16], translationMatrix[16];
    
    memcpy(copy, matrix, sizeof(float)*16);
    setIdentity(translationMatrix);
    
    translationMatrix[12] = tx;
    translationMatrix[13] = ty;
    translationMatrix[14] = tz;
    
    multiplyMatrix(matrix,copy,translationMatrix);
}

inline void Matrix::scale(float* matrix, const float sx, const float sy, const float sz)
{
    float copy[16], scaleMatrix[16];
    
    memcpy(copy, matrix, sizeof(float)*16);
    
    scaleMatrix[0] = sx;
    scaleMatrix[5] = sy;
    scaleMatrix[10] = sz;
    scaleMatrix[15] = 1;
    
    multiplyMatrix(matrix, copy, scaleMatrix);
}
inline void Matrix::rotateX(float* matrix, const float degs)
{
    const float radians = Matrix::degreesToRadians(degs);
    float rotationMatrix[16], copy[16];
    
    memcpy(copy, matrix, sizeof(float)*16);
    setIdentity(rotationMatrix);
    
    rotationMatrix[5] = rotationMatrix[10] = cos(radians);
    rotationMatrix[6] = sin(radians);
    rotationMatrix[9] = -rotationMatrix[6];

    multiplyMatrix(matrix, copy, rotationMatrix);
}

inline void Matrix::rotateY(float* matrix, const float degs)
{
    const float radians = Matrix::degreesToRadians(degs);
    float rotationMatrix[16], copy[16];
    
    memcpy(copy, matrix, sizeof(float)*16);
    setIdentity(rotationMatrix);

    rotationMatrix[0] = rotationMatrix[10] = cos(radians);
    rotationMatrix[2] = sin(radians);
    rotationMatrix[10] = -rotationMatrix[2];

    MultiplyMatrix(matrix, copy, rotationMatrix);
}

inline void Matrix::rotateZ(float* matrix, const float degs)
{
    const float radians = Matrix::degreesToRadians(degs);
    float rotationMatrix[16], copy[16];

    memcpy(copy, matrix, sizeof(float)*16);
    setIdentity(rotationMatrix);
    
    rotationMatrix[0] = rotationMatrix[5] = cos(radians);
    rotationMatrix[1] = sin(radians);
    rotationMatrix[4] = -rotationMatrix[1];

    MultiplyMatrix(matrix, copy, rotationMatrix);
}
