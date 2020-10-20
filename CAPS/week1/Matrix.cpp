#include <cstddef>
#include <iostream>
#include <cstring>
#include <assert.h>
#include <thread>
#include <vector>

struct Matrix
{
    Matrix(const int rows, const int cols) : table(nullptr), _rows(rows), _cols(cols)
    {
        table = new float[(rows * cols)];
    }
    float& operator()(const int row, const int col) const
    {
        return table[col + row * _cols];
    }
    Matrix(const Matrix& other)
        : table(nullptr), _rows(other._rows), _cols(other._cols)
    {
        memory_allocation();
        const auto capacity = _rows * _cols;
        for (int i = 0; i < capacity; i++)
            table[i] = other.table[i];
    }
    Matrix operator*(const Matrix& rhs)
    {
	assert(_cols == rhs._rows);
	auto single_cell_calc = [] (const int current_row,
				      const int current_col,
				      const int max,
				      const Matrix& rhs,
				      const Matrix& lhs,
				      Matrix& result){
		for(int k = 0; k < max; k++){
            result(current_row,current_col) += (rhs)(current_row, k) + (lhs)(k, current_col);
        }};
    std::vector<std::thread> threads;
	Matrix m(_rows, rhs._cols);
	for(int i = 0; i < _rows; i++){
	    for(int j = 0; j < rhs._cols; j++){
		for(int k = 0; k < _cols; k++){
		    m(i,j) += (*this)(i,k) * rhs(k,j);
		}
	    }
	}
	return m;
    }
    Matrix& operator=(const Matrix& rhs)
    {
        if(this != &rhs)
        {
            if(this->capacity() != rhs.capacity())
            {
                if(table){
                    delete [] table;
                }
                _rows = rhs._rows;
                _cols = rhs._cols;
                memory_allocation();
                memcpy(table, rhs.table, sizeof(float) * this->capacity());
            }
        }
        return *this;
    }
    const int capacity() const
    {
        return _rows * _cols;
    }
    ~Matrix()
    {
        if(table)
            delete [] table;
    }
    float* table;
    int _rows, _cols;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    private:
    void memory_allocation()
    {
        table = new float[_rows * _cols];
    }
};
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for(int row = 0; row < m._rows; row++){
        for(int col = 0; col < m._cols; col++){
            os << m(row,col) << " ";
        }
        os << "\n";
    }
    os << "\n";
    return os; 
}
int main()
{
    Matrix m(4,4);
    for(int i = 0; i < m._rows; i++){
	for(int j = 0; j < m._cols; j++){
	    m(i,j) = i+j;
	}
    }
    Matrix k = m;
    Matrix v = m * k;
    std::cout<< k << "\n\n";
    std::cout << m;
    std::cout << v;
    return 0;
}
