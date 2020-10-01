#include "stdio.h"
#include <initializer_list>

struct Matrix_4x1
{
    double table[4];
    
    void print()
    {
    for(int i = 0 ; i < 4; i++){
        printf("%f\n",table[i]);
    }
    printf("\n");
    }
};

struct Matrix_4x4
{
    double table[16];

    Matrix_4x4(int indentity=0)
    {
        if(indentity){
            table[0] = table[5] = table[10] = table[15] = 1;
        }
    }
    Matrix_4x4(const int x_scale, const int y_scale, const int z_scale)
    {
    table[0] = x_scale;
    table[5] = y_scale;
    table[10] = z_scale;
    table[15] = 1;
    }
    void print()
    {
    for(int i = 0; i < 4; i++){
        printf("%f %f %f %f\n",table[i], table[i+4], table[i+8], table[i+12]);
    }
        printf("\n");
    }
    
    Matrix_4x4 operator*(const Matrix_4x4& other)
    {
    Matrix_4x4 r_matrix;
        for(int row = 0; row < 4 ; row++){
        for(int col = 0; col < 4; col++){
        for(int k = 0; k < 4; k++){
            r_matrix.table[row+4*col] += table[row+k*4] *other.table[k+col*4];
        }
        }
    }
    return r_matrix;
    }

    Matrix_4x1 Translate(const Matrix_4x1& matrix)
    {
    Matrix_4x1 vector;
    vector.table[0] = table[0] * matrix.table[0] + table[12] * matrix.table[3];
    vector.table[1] = table[5] * matrix.table[1] + table[13] * matrix.table[3];
    vector.table[2] = table[10] * matrix.table[2] + table[14] * matrix.table[3];
    return vector;
    }
};

int main()
{
    Matrix_4x4 m(true);
    m.table[12] = 8;
    m.table[13] = -4;
    m.table[14] = -2;
    Matrix_4x1 n = { { 1, 2, 3, 1} };
    auto t = m.Translate(n);
    m.print();
    n.print();
    t.print();
}
