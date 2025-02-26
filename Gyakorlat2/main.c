#include <stdio.h>
#include "matrix.c"

int main(int argc, char* argv[]) 
{
    float a[3][3] = 
    {
        {1.0f, -2.0f, 3.0f},
        {5.0f, -3.0f, 0.0f},
        {-2.0f, 1.0f, -4.0f}
    };
    float b[3][3];
    float c[3][3];
    float point[3] = {1.0f, 1.0f, 1.0f}; // Homogén koordináták

    init_zero_matrix(b);
    b[1][1] = 8.0f;
    b[2][0] = -3.0f;
    b[2][2] = 5.0f;

    print_matrix(a);
    print_matrix(b);

    add_matrices(a, b, c);
    printf("Matrix A + B:\n");
    print_matrix(c);

    multiply_matrix_scalar(a, 2.0f, c);
    printf("Matrix A * 2:\n");
    print_matrix(c);

    multiply_matrices(a, b, c);
    printf("Matrix A * B:\n");
    print_matrix(c);

    printf("Transforming point with matrix A:\n");
    transform_point(a, point);
    printf("Transformed point: (%4.4f, %4.4f)\n", point[0], point[1]);

    printf("Applying scale transformation:\n");
    scale(a, 2.0f, 2.0f);
    print_matrix(a);

    printf("Applying shift transformation:\n");
    shift(a, 5.0f, 3.0f);
    print_matrix(a);

    printf("Applying rotate transformation:\n");
    rotate(a, 45.0f);
    print_matrix(a);

    return 0;
}
