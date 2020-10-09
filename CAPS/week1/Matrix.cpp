#include <iostream>
#include <assert.h>

struct Matrix
{
    Matrix(int row,int col) :
	_row(row), _col(col)
    {
	alloc();
    }
    
    Matrix(const Matrix& copy) :
	_row(copy._row), _col(copy._col)
    {
	alloc();
	for(int rows = 0; rows < _row; rows++){
	    for(int cols = 0; cols < _col; cols++){
		table[rows][cols] = copy.table[rows][cols];
	    }
	}
    }
    
    Matrix& operator=(const Matrix& rhs){
	if(this == &rhs)
	    return *this;

	if(_row != rhs._row || _col != rhs._col){
	    for(size_t i = 0; i < _row; i++){
		delete [] table[i];
	    }
	    delete[] table;
	    _row = rhs._row;
	    _col = rhs._col;
	    alloc();
	}
	for(int rows = 0; rows < _row; rows++){
	    for(int cols = 0; cols < _col; cols++){
		table[rows][cols] = rhs.table[rows][cols];
	    }
	}
	return *this;
    }

    void print(){
	for(int rows = 0; rows < _row; rows++){
	    for(int cols = 0; cols < _col; cols++){
		std::cout << table[rows][cols] << " ";
	    }
	    std::cout << "\n";
	}
	std::cout << "\n";
    }
    
    double& operator()(const int row, const int col){
	return table[row][col];
    }
    
    ~Matrix()
    {
	for(size_t i = 0; i < _row; i++){
	    delete[] table[i];
	}
	delete[] table;
    }
    Matrix operator*(const Matrix& rhs){
	assert(_col == rhs._row);
	Matrix m(_row, rhs._col);
	for(int rows = 0 ; rows < _row; rows++){
	    for(int cols = 0; cols < _col; cols++){
		for(int trav = 0; trav < m._row; trav++){
		    m(rows,cols) += table[rows][trav] * rhs.table[trav][cols];
		}
	    }
	}
	return m;
    }
    int _row, _col;
    double** table;
    
private:
    void alloc(){
	table = new double*[_row];
	for(size_t cols = 0; cols < _row; cols++){
	    table[cols] = new double[_col];
	}
    }
};

int main()
{
    Matrix m(3,5);
    for(int i = 0 ; i < 3;i++){
	for(int j = 0; j < 5; j++){
	    m(i,j) = j*i+(i+j);
	}
    }
    Matrix n(5,3);
    for(int i = 0 ; i < 5;i++){
	for(int j = 0; j < 3; j++){
	    n(i,j) = j*i+(i+j);
	}
    }
    Matrix p = m * n;
    //m.print();
    //n.print();
    p.print();
    return 0;
}
