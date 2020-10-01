#include <vector>
#include <iostream>
#include <assert.h>
#include <memory>

struct Matrix
{
    Matrix(const int col, const int row, const std::vector<int>& values = {}) :
        col(col), row(row)
    {
        const unsigned int grid_size = row * col;
        table = std::make_unique<int*>(new int[grid_size]);

        for (unsigned int index = 0; index < grid_size; ++index)
        {
            if (values.size() > index)
                (*table)[index] = values[index];
            else
                (*table)[index] = 0;
        }
    }

    const int matrixSize() const {
        return col * row;
    }

    void print() const {
        for (int _row = 0; _row < row; _row++) {
            std::cout << "\n";
            for (int _col = 0; _col < col; _col++) {
                std::cout << " " << (*this)(_col, _row);
            }
        }
        std::cout << "\n";
    }

    int& operator()(const int _col, const int _row) const {
        return (*table)[_row + row * _col];
    }

    Matrix operator*(const Matrix& other) {
        assert(other.row == col);
        Matrix m(row, other.col);
        for (int _col = 0; _col < m.col; _col++) {
            for (int _row = 0; _row < m.row; _row++) {
                for (int traverse = 0; traverse < m.row; traverse++) {
                    (*m.table)[_row + m.row * _col] += (*table)[_row + traverse * m.row] * (*other.table)[traverse + _col * m.row];
                }
            }
        }
        return m;
    }
    int col, row;
    std::unique_ptr<int*> table;
};
int main()
{
    Matrix m(3, 2, std::vector<int> {1, 2, 3, 4, 5, 6});
    Matrix n(2, 3, std::vector<int> {1, 2, 3, 4, 5, 6});
    Matrix multi = m * n;
    m.print();
    n.print();
    multi.print();
    return 0;
}
