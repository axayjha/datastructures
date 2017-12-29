/**
	2-dimensional array [matrix] manipulation utilities

	@author: Akshay
	@version 0.1 29-Dec-17
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
using namespace std;

enum {
	MAX_MAT_DIM = 0x0fff,
	ERROR 		= 0xf001
};

typedef struct{
	uint16_t row, 
	         column;
}Size;

Size Dimension(uint16_t r, uint16_t c) {
	Size dim = {r, c}; 
	return dim;
}

bool isEqual(Size d1, Size d2){
	if (d1.row == d2.row && d1.column == d2.column)
		return true;
	return false;
}

template <typename whatever> whatever abs(whatever number) {
	if (number < 0)
		return -1*number;
	return number;
}

template <typename whatever> class Matrix;

template<typename whatever> Matrix<whatever> 
operator+(const whatever num, const Matrix<whatever> &mat);

template<typename whatever> Matrix<whatever> 
operator-(const whatever num, const Matrix<whatever> &mat);

template<typename whatever> Matrix<whatever> 
operator*(const whatever num, const Matrix<whatever> &mat);

template <typename whatever>
class Matrix {
	vector < vector <whatever> >array;
	Size dimension;
public:

	Matrix();
	Matrix(Size dim);
	Matrix(uint16_t row, uint16_t column);
	inline Size get_dim();
	inline void set_dim(Size dim);
	inline void set_dim(uint16_t row, uint16_t column);
	inline void set_item(uint16_t row, uint16_t column, whatever value);
	inline whatever get_item(uint16_t row, uint16_t column);
	inline void resize(uint16_t row, uint16_t column);	
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

	this->array.resize(MAX_MAT_DIM, std::vector<whatever>(MAX_MAT_DIM, 0));

}

template <typename whatever>
Matrix<whatever> :: Matrix(Size dim){ 
	this->dimension = dim; 
	this->array.resize(dim.row, std::vector<whatever>(dim.column, 0));
}

template <typename whatever>
Matrix<whatever> :: Matrix(uint16_t row, uint16_t column) { 
	this->dimension = Dimension(row, column);
	this->array.resize(row, std::vector<whatever>(column, 0));
}

template <typename whatever>
Size Matrix<whatever> :: get_dim() {
	return this->dimension;
}

template <typename whatever>
void Matrix<whatever> :: set_dim(Size dim) {
	this->dimension = dim;
}

template <typename whatever>
void Matrix<whatever> :: set_dim(uint16_t row, uint16_t column) {
	this->dimension = Dimension(row, column);
}

template <typename whatever>
void Matrix<whatever> :: set_item(uint16_t row, uint16_t column, whatever value) {
	this->array[row][column] = value;
}

template <typename whatever>
whatever Matrix<whatever> :: get_item(uint16_t row, uint16_t column){
	return this->array[row][column];
}

template <typename whatever>
void Matrix<whatever> :: resize(uint16_t row, uint16_t column) {
	this->dimension = Dimension(row, column);
	this->array.resize(row, std::vector<whatever>(column, (whatever)0));
}


template <typename whatever>
void Matrix<whatever> :: input(vector < vector <whatever> > array){

	uint16_t row    = array.size(),
			 column = array[0].size();

	this->resize(row, column);


	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			this->set_item(i, j, array[i][j]);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: transpose() {	
	uint16_t row    = this->dimension.row,
			 column = this->dimension.column;
	Matrix <whatever> mat(column, row);		 

	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			mat.set_item(j, i, this->array[i][j]);

	return mat;			 
}

template <typename whatever>
void Matrix<whatever> :: print() {

	uint16_t row    = this->dimension.row,
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
	assert(isEqual(mat.dimension, this->dimension));
	Matrix <whatever> sum(this->dimension);

	for(int i = 0; i < this->dimension.row; i++)
		for(int j = 0; j < this->dimension.column; j++)
			sum.set_item(i, j, (this->get_item(i,j) + mat.get_item(i,j)));

	return sum;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: add(whatever num) {
	
	Matrix <whatever> sum(this->dimension);

	for(int i = 0; i < this->dimension.row; i++)
		for(int j = 0; j < this->dimension.column; j++)
			sum.set_item(i, j, (this->get_item(i,j) + num));

	return sum;
}


template <typename whatever>
Matrix<whatever> Matrix<whatever> :: subtract(Matrix mat) {
	assert(isEqual(mat.dimension, this->dimension));
	Matrix<whatever> diff(this->dimension);

	for(int i = 0; i < this->dimension.row; i++)
		for(int j = 0; j < this->dimension.column; j++)
			diff.set_item(i, j, (this->get_item(i,j) - mat.get_item(i,j)));

	return diff;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: subtract(whatever num) {
	
	Matrix<whatever> diff(this->dimension);

	for(int i = 0; i < this->dimension.row; i++)
		for(int j = 0; j < this->dimension.column; j++)
			diff.set_item(i, j, (this->get_item(i,j) - num));

	return diff;
}


template <typename whatever>
Matrix<whatever> Matrix<whatever> :: difference(Matrix mat) {
	assert(isEqual(mat.dimension, this->dimension));
	Matrix<whatever> absdiff(this->dimension);

	for(int i = 0; i < this->dimension.row; i++)
		for(int j = 0; j < this->dimension.column; j++)
			absdiff.set_item(i, j, abs(this->get_item(i,j) - mat.get_item(i,j)));

	return absdiff;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: difference(whatever num) {
	
	Matrix<whatever> absdiff(this->dimension);

	for(int i = 0; i < this->dimension.row; i++)
		for(int j = 0; j < this->dimension.column; j++)
			absdiff.set_item(i, j, abs(this->get_item(i,j) - num));

	return absdiff;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: multiply(Matrix mat) {
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
	
	Matrix<whatever> product(this->dimension);

	for(int i = 0; i < this->dimension.row; i++)
		for(int j = 0; j < this->dimension.column; j++)
			product.set_item(i, j, abs(this->get_item(i,j) * num));

	return product;
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator+(Matrix mat) {
	return this->add(mat);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator-(Matrix mat) {
	return this->subtract(mat);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator*(Matrix mat) {
	return this->multiply(mat);
}


template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator+(whatever num){
	return this->add(num);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator-(whatever num){
	return this->subtract(num);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: operator*(whatever num){
	return this->multiply(num);
}

template <typename whatever>
Matrix<whatever>  operator+(const whatever num , const Matrix<whatever> &mat){
	Matrix<whatever> &mat1 = const_cast<Matrix <whatever> &>(mat);
	return mat1.add(num);
}

template <typename whatever>
Matrix<whatever> operator-(const whatever num , const Matrix<whatever> &mat){
	Matrix<whatever> &mat1 = const_cast<Matrix <whatever> &>(mat);
	Matrix<whatever> res=  num + (-1)*mat1;
	return res;
}

template <typename whatever>
Matrix<whatever> operator*(const whatever num , const Matrix<whatever> &mat){
	Matrix<whatever> &mat1 = const_cast<Matrix <whatever> &>(mat);
	return mat1.multiply(num);
}

template <typename whatever>
Matrix<whatever> Matrix<whatever> :: add_padding(
							uint8_t margin, 
							whatever value) {

		uint16_t row =this->dimension.row + (2 * margin);
		uint16_t column =this->dimension.column + (2 * margin);
		Matrix <whatever> paddedMat(row, column);	

		for(int i = margin; i < row - margin; i++)
			for(int j = margin; j < column - margin; j++)
				paddedMat.set_item(i, j, this->get_item(i-margin, j-margin));

		if (margin == 0) return paddedMat;	

		for(int i=0; i < margin; i++)
			for(int j=0; j < column; j++){
				paddedMat.set_item(i, j, value);	
				paddedMat.set_item(row-i-1, j, value);
			}

		for(int i=0; i < row; i++)
			for(int j=0; j < margin; j++){
				paddedMat.set_item(i, j, value);	
				paddedMat.set_item(i, column-j-1, value);
			}	
		return paddedMat;
}


#endif