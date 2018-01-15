/**
	2-dimensional array [matrix] manipulation utilities

	@author Akshay
	@version 0.1 29-Dec-17
	@version 0.2 14-Jan-18
*/


#ifndef MATRIX_HPP
#define MATRIX_HPP

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
using namespace std;

/* declaring constants */
enum {
	MAX_MAT_DIM = 0x0fff,
	ERROR 		= 0xf001
};


/* structure to store matrix dimensions */
typedef struct{
	uint64_t row, 
	         column;
}Size;

/* Dimension: works like a constructor for the 
   Size structure */
Size Dimension(uint64_t r, uint64_t c) {
	Size dim = {r, c}; 
	return dim;
}

/* isEqual: compares two dimensions */
bool isEqual(Size d1, Size d2){
	if (d1.row == d2.row && d1.column == d2.column)
		return true;
	return false;
}

/* abs: returns absolute of a numeric value of any type */
template <typename whatever> whatever abs(whatever number) {
	if (number < 0)
		return -1*number;
	return number;
}

/** some required prototype declarations */
template <typename whatever> class Matrix;

template<typename whatever> Matrix<whatever> 
operator+(const whatever num, const Matrix<whatever> &mat);

template<typename whatever> Matrix<whatever> 
operator-(const whatever num, const Matrix<whatever> &mat);

template<typename whatever> Matrix<whatever> 
operator*(const whatever num, const Matrix<whatever> &mat);

/*------------------------------------ **/

/** 
	Matrix class that supports operations on 
	all  numeric type. So please show some decency 
	and please use it only with numeric types
*/
template <typename whatever>
class Matrix {

	vector < vector <whatever> >array;
	Size dimension;
	
public:

	Matrix();
	Matrix(Size dim);
	Matrix(uint64_t row, uint64_t column);
	inline Size get_dim();
	inline void set_dim(Size dim);
	inline void set_dim(uint64_t row, uint64_t column);
	inline void set_item(uint64_t row, uint64_t column, whatever value);
	inline whatever get_item(uint64_t row, uint64_t column);
	inline void resize(uint64_t row, uint64_t column);	
	void input(vector < vector <whatever> >array);
	void print();
	Matrix transpose();
	Matrix add(Matrix mat);
	Matrix add(whatever num);	
	Matrix subtract(Matrix mat);
	Matrix subtract(whatever num);
	Matrix difference(Matrix mat);
	Matrix difference(whatever num);
	Matrix multiply(Matrix mat);
	Matrix multiply(whatever num);
	Matrix operator+(Matrix mat);
	Matrix operator-(Matrix mat);
	Matrix operator*(Matrix mat);
	Matrix operator+(whatever num);
	Matrix operator-(whatever num);
	Matrix operator*(whatever num);
	friend Matrix (::operator+ <whatever>) (
		const whatever num, const Matrix &mat);
	friend Matrix (:: operator- <whatever>) (
		const whatever num, const Matrix &mat);
	friend Matrix (:: operator* <whatever>) (
		const whatever num, const Matrix &mat);
	Matrix add_padding(uint8_t margin, whatever value);
	// add convolve
	

};


template <typename whatever>
Matrix<whatever> :: Matrix() {
	/** 
		Default constructor :
			Matrix m;
			Matrix *m = new Matrix();
		Dimension = MAX_MAT_DIM X MAX_MAT_DIM  
					(constant declared at the top)	
	*/
	this->array.resize(MAX_MAT_DIM, std::vector<whatever>(MAX_MAT_DIM, 0));
}


template <typename whatever>
Matrix<whatever> :: Matrix(Size dim){ 
	/**
		Constructor assigning dimensions:
			Matrix m(dimension);
			Matrix *m = new Matrix(dimension);
		type(dimension) = Size
		Size = Structure {row, 		column} 
			 = 			 {uint64_t, uint64_t}
	*/
	this->dimension = dim; 
	this->array.resize(dim.row, std::vector<whatever>(dim.column, 0));
}


template <typename whatever>
Matrix<whatever> :: Matrix(uint64_t row, uint64_t column) { 
	/**
		Constructor assigning dimension explicitly:
			Matrix m(row, column);
			Matrix *m = new Matrix(row, column)
	*/
	this->dimension = Dimension(row, column);
	this->array.resize(row, std::vector<whatever>(column, 0));
}


template <typename whatever>
Size Matrix<whatever> :: get_dim() {
	/**
	    matrix.get_dim();
	    
	    @param none
	    @return dimesion of matrix
	    @return_type Size
	*/
	return this->dimension;
}


template <typename whatever>
void Matrix<whatever> :: set_dim(Size dim) {
	/**
	    matrix.set_dim(dimension);
	    Sets dimension of a new matrix.
	    It doesn't actually resize the matrix in memory.
	    *Use it carefully on a non-empty matrix to prevent data loss.*

	    @param dimesion: dimension of type Size
	    @return none    
	*/
	this->dimension = dim;
}

template <typename whatever>
void Matrix<whatever> :: set_dim(uint64_t row, uint64_t column) {
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

template <typename whatever>
void Matrix<whatever> :: set_item(uint64_t row, uint64_t column, whatever value) {
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

template <typename whatever>
whatever Matrix<whatever> :: get_item(uint64_t row, uint64_t column){
	/**
	    matrix.get_item(row_index, column_index);
	    Returns value from matrix from a specific location	    

	    @param row: row index
	    @param column: column index
	    @return none    
	*/
	return this->array[row][column];
}

template <typename whatever>
void Matrix<whatever> :: resize(uint64_t row, uint64_t column) {
	/**
	    matrix.resize(row_size, column_size);
	    Resizes a matrix size, but clears all data. Use cautiously.	    

	    @param row: row size
	    @param column: column size
	    @return none    
	*/
	this->dimension = Dimension(row, column);
	this->array.resize(row, std::vector<whatever>(column, (whatever)0));
}


template <typename whatever>
void Matrix<whatever> :: input(vector < vector <whatever> > array){
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

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: transpose() {	
	/**
		matrix.transpose();
		Changes rows to columns and columns to rows

		@param none
		@return A new transposed matrix
	*/
	
	uint64_t row    = this->dimension.row,
			 column = this->dimension.column;
	Matrix <whatever> mat(column, row);		 

	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			mat.set_item(j, i, this->array[i][j]);

	return mat;			 
}

template <typename whatever>
void Matrix<whatever> :: print() {
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

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: add(Matrix mat) {
	/**
		matrix1.add(matrix2);
		Adds two matrices

		@param mat: a second matrix to add
		@return a new matrix containing the sum
	*/

	assert(isEqual(mat.dimension, this->dimension)); // making sure the orders are same
	Matrix <whatever> sum(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			sum.set_item(i, j, (this->get_item(i,j) + mat.get_item(i,j)));

	return sum;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: add(whatever num) {
	/**
		matrix1.add(num);
		Adds a number to all elements in a matrix

		@param num: the number to add
		@return a new matrix containing the sum
	*/

	Matrix <whatever> sum(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			sum.set_item(i, j, (this->get_item(i,j) + num));

	return sum;
}


template <typename whatever>
Matrix<whatever> Matrix<whatever> :: subtract(Matrix mat) {
	/**
		matrix1.subtract(matrix2);
		Subtracts one matrix from another

		@param mat: a second matrix to subtract
		@return a new matrix containing the difference
	*/

	assert(isEqual(mat.dimension, this->dimension));
	Matrix<whatever> diff(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			diff.set_item(i, j, (this->get_item(i,j) - mat.get_item(i,j)));

	return diff;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: subtract(whatever num) {
	/**
		matrix1.subtract(num);
		Subtracts a number from all elements in a matrix

		@param num: the number to subtract
		@return a new matrix containing the difference
	*/
	
	Matrix<whatever> diff(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			diff.set_item(i, j, (this->get_item(i,j) - num));

	return diff;
}


template <typename whatever>
Matrix<whatever> Matrix<whatever> :: difference(Matrix mat) {
	/**
		matrix1.difference(mat);
		Finds the absoulute difference between two matrices

		@param mat: the matrix to subtract
		@return a new matrix containing the absolute difference
	*/

	assert(isEqual(mat.dimension, this->dimension));
	Matrix<whatever> absdiff(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			absdiff.set_item(i, j, abs(this->get_item(i,j) - mat.get_item(i,j)));

	return absdiff;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: difference(whatever num) {
	/**
		matrix1.difference(num);
		Subtracts a number from all elements in a matrix
		and returns absolute value

		@param num: the number to subtract
		@return a new matrix containing the absolute difference
	*/

	Matrix<whatever> absdiff(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			absdiff.set_item(i, j, abs(this->get_item(i,j) - num));

	return absdiff;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: multiply(Matrix mat) {
	/**
		matrix1.multiply(mat);
		Multiplies two matrices

		@param mat: the second matrix to multiply
		@return a new matrix containing the product
	*/

	assert(this->dimension.column == mat.dimension.row);
	Matrix <whatever> product(this->dimension.row, mat.dimension.column);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < mat.dimension.column; j++){
			whatever prod = 0;
			for (int k = 0; k < this->dimension.column; k++)
				prod += (this->get_item(i, k) * mat.get_item(k, j));
			product.set_item(i, j, prod);
		}
	return product;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: multiply(whatever num) {
	/**
		matrix1.multiply(num);
		Multiplies a number to all elements of a matrix

		@param num: the number to multiply
		@return a new matrix containing the product
	*/

	Matrix<whatever> product(this->dimension);

	for (int i = 0; i < this->dimension.row; i++)
		for (int j = 0; j < this->dimension.column; j++)
			product.set_item(i, j, abs(this->get_item(i,j) * num));

	return product;
}

/** Functions to overload operators for basic arithmetic operations */
template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator+(Matrix mat) {
	/**
		Usage:
			matrix3 = matrix1 + matrix2
	*/
	return this->add(mat);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator-(Matrix mat) {
	/**
		Usage:
			matrix3 = matrix1 - matrix2
	*/
	return this->subtract(mat);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator*(Matrix mat) {
	/**
		Usage:
			matrix3 = matrix1 * matrix2
	*/
	return this->multiply(mat);
}


template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator+(whatever num){
	/**
		Usage:
			matrix2 = matrix1 + number
	*/
	return this->add(num);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator-(whatever num){
	/**
		Usage:
			matrix2 = matrix1 - number
	*/
	return this->subtract(num);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator*(whatever num){
	/**
		Usage:
			matrix2 = matrix1 * number
	*/
	return this->multiply(num);
}

template <typename whatever>
Matrix<whatever>  operator+(const whatever num , const Matrix<whatever> &mat){
	/**
		Usage:
			matrix2 = number + matrix1
	*/
	Matrix<whatever> &mat1 = const_cast<Matrix <whatever> &>(mat);
	return mat1.add(num);
}

template <typename whatever>
Matrix<whatever> operator-(const whatever num , const Matrix<whatever> &mat){
	/**
		Usage:
			matrix2 = number - matrix1
	*/
	Matrix<whatever> &mat1 = const_cast<Matrix <whatever> &>(mat);
	Matrix<whatever> res =  num + (-1)*mat1;
	return res;
}

template <typename whatever>
Matrix<whatever> operator*(const whatever num , const Matrix<whatever> &mat){
	/**
		Usage:
			matrix2 = num * matrix1
	*/
	Matrix<whatever> &mat1 = const_cast<Matrix <whatever> &>(mat);
	return mat1.multiply(num);
}
/*----------------END OF OPERATOR OVERLOADING FUNCTIONS---------------------**/


template <typename whatever>
Matrix<whatever> Matrix<whatever> :: add_padding(
							uint8_t margin, 
							whatever value) {
	/**
		matrix1.add_padding(margin, value);
		adds padding to a matrix on all sides

		@param margin: number of rows and columns of padding to add
		@param value: what value to pad with
		@return a new padded matrix
	*/

	uint64_t row    = this->dimension.row + (2 * margin),
			 column = this->dimension.column + (2 * margin);
	Matrix <whatever> paddedMat(row, column);	

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


#endif