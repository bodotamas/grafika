#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

void init_zero_matrix(float matrix[3][3]) 
{
    int i, j;
    for (i = 0; i < 3; ++i) 
    {
        for (j = 0; j < 3; ++j) 
        {
            matrix[i][j] = 0.0;
        }
    }
}

void init_identity_matrix(float matrix[3][3]) 
{
    int i, j;
    for (i = 0; i < 3; ++i) 
    {
        for (j = 0; j < 3; ++j) 
        {
            if (i == j) 
            {
                matrix[i][j] = 1.0;
            } 
            else 
            {
                matrix[i][j] = 0.0;
            }
        }
    }
}

void print_matrix(const float matrix[3][3]) 
{
    int i, j;
    for (i = 0; i < 3; ++i) 
    {
        for (j = 0; j < 3; ++j)
        {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
 {
    int i, j;
    for (i = 0; i < 3; ++i) 
    {
        for (j = 0; j < 3; ++j) 
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiply_matrix_scalar(const float matrix[3][3], float scalar, float result[3][3]) 
{
    int i, j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float result[3][3]) 
{
    int i, j, k;
    for (i = 0; i < 3; ++i) 
    {
        for (j = 0; j < 3; ++j) 
        {
            result[i][j] = 0.0;
            for (k = 0; k < 3; ++k) 
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transform_point(const float matrix[3][3], float point[3]) 
{
    float result[3] = {0.0, 0.0, 0.0};
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            result[i] += matrix[i][j] * point[j];
        }
    }
    point[0] = result[0];
    point[1] = result[1];
    point[2] = result[2];
}

void scale(float matrix[3][3], float sx, float sy) 
{
    float scaleMatrix[3][3];
    init_identity_matrix(scaleMatrix);
    scaleMatrix[0][0] = sx;
    scaleMatrix[1][1] = sy;
    multiply_matrices(scaleMatrix, matrix, matrix);
}

void shift(float matrix[3][3], float tx, float ty) 
{
    float shiftMatrix[3][3];
    init_identity_matrix(shiftMatrix);
    shiftMatrix[0][2] = tx;
    shiftMatrix[1][2] = ty;
    multiply_matrices(shiftMatrix, matrix, matrix);
}

void rotate(float matrix[3][3], float angle) 
{
    float radians = angle * (PI / 180.0);
    float rotationMatrix[3][3];
    init_identity_matrix(rotationMatrix);
    rotationMatrix[0][0] = cos(radians);
    rotationMatrix[0][1] = -sin(radians);
    rotationMatrix[1][0] = sin(radians);
    rotationMatrix[1][1] = cos(radians);
    multiply_matrices(rotationMatrix, matrix, matrix);
}
