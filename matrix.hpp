#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <sstream>
#include <list>
#include <iterator>
#include <numeric>
#include <vector>
#include <stdint.h>
#include <exception>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits.h>
#include <cmath>
#include <cstdio> 
#include <errno.h>
using namespace std;

#ifndef MATRIX_HPP
#define MATRIX_HPP


/* structure to store matrix dimensions */
typedef struct{
	uint64_t row; 			// height
	uint64_t column;		// width
}Size;


/* Dimension: works like a constructor for the 
   Size structure */
Size Dimension(uint64_t r, uint64_t c) {
	Size dim;
	dim.row = r;
	dim.column = c;
	return dim;
}

/* isEqual: compares two dimensions */
bool isEqual(Size d1, Size d2){
	return d1.row == d2.row && d1.column == d2.column;		
}

/* abs: returns absolute of a numeric value of any type */
template <typename T> T abs(T number) {
	const T ret[2] = { number, -number };
    return ret [number < 0];	
}

/** some required prototype declarations */
template <typename T> class Matrix;

template<typename T> Matrix<T> 
operator+(const T num, const Matrix<T> &mat);

template<typename T> Matrix<T> 
operator-(const T num, const Matrix<T> &mat);

template<typename T> Matrix<T> 
operator*(const T num, const Matrix<T> &mat);

/*------------------------------------ **/

/** 
	Matrix class that supports operations on 
	all  numeric type. So please show some decency 
	and please use it only with numeric types
*/
template <typename T>
class Matrix {

	vector < vector <T> >array;
	Size dimension;
	
public:

	explicit Matrix() : dimension({0,0}) {}
	explicit Matrix(Size dim);
	explicit Matrix(uint64_t row, uint64_t column);
	inline Size get_dim();
	inline void set_dim(Size dim);
	inline void set_dim(uint64_t row, uint64_t column);
	inline void set_item(uint64_t row, uint64_t column, T value);
	inline T get_item(uint64_t row, uint64_t column);
	inline void resize(uint64_t row, uint64_t column);	
	void input(vector < vector <T> >array);
	void print();
	Matrix transpose();
	Matrix add(Matrix mat);
	Matrix add(T num);	
	Matrix subtract(Matrix mat);
	Matrix subtract(T num);
	Matrix difference(Matrix mat);
	Matrix difference(T num);
	Matrix multiply(Matrix mat);
	Matrix multiply(T num);
	Matrix operator+(Matrix mat);
	Matrix operator-(Matrix mat);
	Matrix operator*(Matrix mat);
	Matrix operator+(T num);
	Matrix operator-(T num);
	Matrix operator*(T num);
	friend Matrix (::operator+ <T>) (
		const T num, const Matrix &mat);
	friend Matrix (:: operator- <T>) (
		const T num, const Matrix &mat);
	friend Matrix (:: operator* <T>) (
		const T num, const Matrix &mat);
	Matrix add_padding(uint8_t margin, T value);
	void copy_to(Matrix &m);
	void copy_from(Matrix m);
	void f_copy_to(Matrix &m);
	void f_copy_from(Matrix m);	
	


	class Proxy {
    public:
        Proxy(Matrix <T> &m, uint64_t index) : parent(m), i(index) { }

        T operator[](uint64_t j) {
        	if (i >= parent.get_dim().row || j>= parent.get_dim().column) {
	    		fprintf(stderr, "Error in line %d in %s: Index out of bounds!\n", __LINE__, __FILE__);
	    		return EBADR;
	    	}            
            return parent.get_item(i, j);
        }
    private:
        uint64_t i;
        Matrix <T> parent;
    };

    Proxy operator[](uint64_t index) {
    	
        return Proxy(*this, index);
    }
};

template <typename T>
Matrix<T> :: Matrix(Size dim){ 
	/**
		Constructor assigning dimensions:
			Matrix m(dimension);
			Matrix *m = new Matrix(dimension);
		type(dimension) = Size
		Size = Structure {row, 		column} 
			 = 			 {uint64_t, uint64_t}
	*/
	this->dimension.row = dim.row;
	this->dimension.column = dim.column; 
	this->array.resize(dim.row, std::vector<T>(dim.column, 0));
}

template <typename T>
Matrix<T> :: Matrix(uint64_t row, uint64_t column) { 
	/**
		Constructor assigning dimension explicitly:
			Matrix m(row, column);
			Matrix *m = new Matrix(row, column)
	*/
	this->dimension = Dimension(row, column);
	this->array.resize(row, std::vector<T>(column, 0));
}

template <typename T>
Size Matrix<T> :: get_dim() {
	/**
	    matrix.get_dim();
	    
	    @param none
	    @return dimesion of matrix
	    @return_type Size
	*/
	return this->dimension;
}

template <typename T>
void Matrix<T> :: set_dim(Size dim) {
	/**
	    matrix.set_dim(dimension);
	    Sets dimension of a new matrix.
	    It doesn't actually resize the matrix in memory.
	    *Use it carefully on a non-empty matrix to prevent data loss.*

	    @param dimesion: dimension of type Size
	    @return none    
	*/
	this->dimension.row = dim.row;
	this->dimension.column = dim.column;
}

template <typename T>
void Matrix<T> :: set_dim(uint64_t row, uint64_t column) {
	/**
	    matrix.set_dim(row_size, column_size);
	    Sets dimension of a new matrix explicitly.
	    It doesn't actually resize the matrix in memory.
	    *Use it carefully on a non-empty matrix to prevent data loss.*

	    @param row: row size (height)
	    @param column: column size (width)
	    @return none    
	*/
	this->dimension = Dimension(row, column);
}

template <typename T>
void Matrix<T> :: set_item(uint64_t row, uint64_t column, T value) {
	/**
	    matrix.set_item(row_index, column_index, value);
	    Changes value in matrix at a specific location	    

	    @param row: row index
	    @param column: column index
	    @param value: value to put at the given location
	    @return none    
	*/
	this->array[row][column] = value;
}

template <typename T>
T Matrix<T> :: get_item(uint64_t row, uint64_t column){
	/**
	    matrix.get_item(row_index, column_index);
	    Returns value from matrix from a specific location	    

	    @param row: row index
	    @param column: column index
	    @return none    
	*/
	return this->array[row][column];
}

template <typename T>
void Matrix<T> :: resize(uint64_t row, uint64_t column) {
	/**
	    matrix.resize(row_size, column_size);
	    Resizes a matrix size, but clears all data. Use cautiously.	    

	    @param row: row size
	    @param column: column size
	    @return none    
	*/
	this->dimension = Dimension(row, column);
	this->array.resize(row, std::vector<T>(column, (T)0));
}

template <typename T>
void Matrix<T> :: input(vector < vector <T> > array){
	/**
	    matrix.input(array);
	    Copies data from a 2d vector.	    

	    @param array: a 2d vector
	    @return none    
	*/
	uint64_t row    = array.size(),
			 column = array[0].size();

	this->resize(row, column);


	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			this->set_item(i, j, array[i][j]);
}

template <typename T>
Matrix<T> Matrix<T> :: transpose() {	
	/**
		matrix.transpose();
		Changes rows to columns and columns to rows

		@param none
		@return A new transposed matrix
	*/
	
	uint64_t row    = this->dimension.row,
			 column = this->dimension.column;
	Matrix <T> mat(column, row);		 

	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			mat.set_item(j, i, this->array[i][j]);

	return mat;			 
}

template <typename T>
void Matrix<T> :: print() {
	/**
		matrix.print();
		Prints the whole matrix, row by row.

		@param none
		@return none
	*/

	uint64_t row    = this->dimension.row,
			 column = this->dimension.column;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++)
			cout << setw(3) << left << this->array[i][j] << " ";		
		cout << endl;
	}
	cout << endl;
}

template <typename T>
Matrix<T> Matrix<T> :: add(Matrix mat) {
	/**
		matrix1.add(matrix2);
		Adds two matrices

		@param mat: a second matrix to add
		@return a new matrix containing the sum
	*/

	assert(isEqual(mat.dimension, this->dimension)); // making sure the orders are same
	Matrix <T> sum(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			sum.set_item(i, j, (this->get_item(i,j) + mat.get_item(i,j)));

	return sum;
}

template <typename T>
Matrix<T> Matrix<T> :: add(T num) {
	/**
		matrix1.add(num);
		Adds a number to all elements in a matrix

		@param num: the number to add
		@return a new matrix containing the sum
	*/

	Matrix <T> sum(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			sum.set_item(i, j, (this->get_item(i,j) + num));

	return sum;
}


template <typename T>
Matrix<T> Matrix<T> :: subtract(Matrix mat) {
	/**
		matrix1.subtract(matrix2);
		Subtracts one matrix from another

		@param mat: a second matrix to subtract
		@return a new matrix containing the difference
	*/

	assert(isEqual(mat.dimension, this->dimension));
	Matrix<T> diff(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			diff.set_item(i, j, (this->get_item(i,j) - mat.get_item(i,j)));

	return diff;
}

template <typename T>
Matrix<T> Matrix<T> :: subtract(T num) {
	/**
		matrix1.subtract(num);
		Subtracts a number from all elements in a matrix

		@param num: the number to subtract
		@return a new matrix containing the difference
	*/
	
	Matrix<T> diff(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			diff.set_item(i, j, (this->get_item(i,j) - num));

	return diff;
}


template <typename T>
Matrix<T> Matrix<T> :: difference(Matrix mat) {
	/**
		matrix1.difference(mat);
		Finds the absoulute difference between two matrices

		@param mat: the matrix to subtract
		@return a new matrix containing the absolute difference
	*/

	assert(isEqual(mat.dimension, this->dimension));
	Matrix<T> absdiff(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			absdiff.set_item(i, j, abs(this->get_item(i,j) - mat.get_item(i,j)));

	return absdiff;
}

template <typename T>
Matrix<T> Matrix<T> :: difference(T num) {
	/**
		matrix1.difference(num);
		Subtracts a number from all elements in a matrix
		and returns absolute value

		@param num: the number to subtract
		@return a new matrix containing the absolute difference
	*/

	Matrix<T> absdiff(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			absdiff.set_item(i, j, abs(this->get_item(i,j) - num));

	return absdiff;
}

template <typename T>
Matrix<T> Matrix<T> :: multiply(Matrix mat) {
	/**
		matrix1.multiply(mat);
		Multiplies two matrices

		@param mat: the second matrix to multiply
		@return a new matrix containing the product
	*/

	assert(this->dimension.column == mat.dimension.row);
	Matrix <T> product(this->dimension.row, mat.dimension.column);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < mat.dimension.column; j++){
			T prod = 0;
			for (int k = 0; k < this->dimension.column; k++)
				prod += (this->get_item(i, k) * mat.get_item(k, j));
			product.set_item(i, j, prod);
		}
	return product;
}

template <typename T>
Matrix<T> Matrix<T> :: multiply(T num) {
	/**
		matrix1.multiply(num);
		Multiplies a number to all elements of a matrix

		@param num: the number to multiply
		@return a new matrix containing the product
	*/

	Matrix<T> product(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			product.set_item(i, j, abs(this->get_item(i,j) * num));

	return product;
}

/** Functions to overload operators for basic arithmetic operations */
template <typename T>
Matrix<T> Matrix<T> :: operator+(Matrix mat) {
	/**
		Usage:
			matrix3 = matrix1 + matrix2
	*/
	return this->add(mat);
}

template <typename T>
Matrix<T> Matrix<T> :: operator-(Matrix mat) {
	/**
		Usage:
			matrix3 = matrix1 - matrix2
	*/
	return this->subtract(mat);
}

template <typename T>
Matrix<T> Matrix<T> :: operator*(Matrix mat) {
	/**
		Usage:
			matrix3 = matrix1 * matrix2
	*/
	return this->multiply(mat);
}


template <typename T>
Matrix<T> Matrix<T> :: operator+(T num){
	/**
		Usage:
			matrix2 = matrix1 + number
	*/
	return this->add(num);
}

template <typename T>
Matrix<T> Matrix<T> :: operator-(T num){
	/**
		Usage:
			matrix2 = matrix1 - number
	*/
	return this->subtract(num);
}

template <typename T>
Matrix<T> Matrix<T> :: operator*(T num){
	/**
		Usage:
			matrix2 = matrix1 * number
	*/
	return this->multiply(num);
}

template <typename T>
Matrix<T>  operator+(const T num , const Matrix<T> &mat){
	/**
		Usage:
			matrix2 = number + matrix1
	*/
	Matrix<T> &mat1 = const_cast<Matrix <T> &>(mat);
	return mat1.add(num);
}

template <typename T>
Matrix<T> operator-(const T num , const Matrix<T> &mat){
	/**
		Usage:
			matrix2 = number - matrix1
	*/
	Matrix<T> &mat1 = const_cast<Matrix <T> &>(mat);
	Matrix<T> res =  num + (-1)*mat1;
	return res;
}

template <typename T>
Matrix<T> operator*(const T num , const Matrix<T> &mat){
	/**
		Usage:
			matrix2 = num * matrix1
	*/
	Matrix<T> &mat1 = const_cast<Matrix <T> &>(mat);
	return mat1.multiply(num);
}
/*----------------END OF OPERATOR OVERLOADING FUNCTIONS---------------------**/


template <typename T>
Matrix<T> Matrix<T> :: add_padding(
							uint8_t margin, 
							T value) {
	/**
		matrix1.add_padding(margin, value);
		adds padding to a matrix on all sides

		@param margin: number of rows and columns of padding to add
		@param value: what value to pad with
		@return a new padded matrix
	*/

	uint64_t row    = this->dimension.row + (2 * margin),
			 column = this->dimension.column + (2 * margin);
	Matrix <T> paddedMat(row, column);	

	for (int i = margin; i < row - margin; i++)
		for (int j = margin; j < column - margin; j++)
			paddedMat.set_item(i, j, this->get_item(i - margin, j - margin));

	if (margin == 0) return paddedMat;	

	for (int i = 0; i < margin; i++)
		for (int j = 0; j < column; j++){
			paddedMat.set_item(i, j, value);	
			paddedMat.set_item(row - i - 1, j, value);
		}

	for (int i = 0; i < row; i++)
		for (int j = 0; j < margin; j++){
			paddedMat.set_item(i, j, value);	
			paddedMat.set_item(i, column - j - 1, value);
		}	
	return paddedMat;
}

template <typename T> 
void Matrix <T> :: copy_from (Matrix m) {

	if (not (isEqual(this->dimension, m.get_dim()))) {
		fprintf(stderr, "Incompatible dimensions for copying\n");
		return;
	}

	for (uint64_t i = 0; i < dimension.row; i++)
		for (uint64_t j = 0; j < dimension.column; j++)
			this->set_item(i, j, m.get_item(i, j));

}

template <typename T>
void Matrix <T> :: copy_to (Matrix &m) {

	if (not (isEqual(this->dimension, m.get_dim()))) {
		fprintf(stderr, "Incompatible dimensions for copying\n");
		return;
	}

	for (uint64_t i = 0; i < dimension.row; i++)
		for (uint64_t j = 0; j < dimension.column; j++)
			m.set_item(i, j, this->get_item(i, j));

}

template <typename T>
void Matrix <T> :: f_copy_from (Matrix m)
{
	if (not (isEqual(this->dimension, m.get_dim()))) {
		this->resize(m.get_dim().row, m.get_dim().column);
	}

	for (uint64_t i = 0; i < dimension.row; i++)
		for (uint64_t j = 0; j < dimension.column; j++)
			this->set_item(i, j, m.get_item(i, j));
}


template <typename T>
void Matrix <T> :: f_copy_to (Matrix &m) {

	if (not (isEqual(this->dimension, m.get_dim()))) {
		m.resize(this->get_dim().row, this->get_dim().column);
	}

	for (uint64_t i = 0; i < dimension.row; i++)
		for (uint64_t j = 0; j < dimension.column; j++)
			m.set_item(i, j, this->get_item(i, j));

}

#endif