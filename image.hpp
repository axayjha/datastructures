/**
	PGM image manipulation utilities	

	@author Akshay <akshayjha@live.in>

	@version 0.1 14-Jan-18
	@version 0.2 14-Jun-18
*/


#ifndef IMAGE_HPP
#define IMAGE_HPP


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
#include "matrix.hpp"
using namespace std;
/* declaring constants */
enum {
	IOERROR = 1
};

namespace {
	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;
	typedef uint64_t u64;
}

class Image {
	/** 
		Image class that supports operations on 
		PGM image files. The member variables are
		public for direct access to operations in
		other files using this library.
	*/	
public:
	Matrix <u16> pix_mat;
	Size dimension;
	Image() : dimension({0,0}){} 			// Default constructor
	Image(string filename);
	inline void set_dim(u16 height, u16 width);
	inline Size get_dim();
	int read(string filename);
	int write(string filename);
	inline void set_pixel(u16 row, u16 column, u16 val);
	inline u16 get_pixel(u16 row, u16 column);
	void resize(u16 height, u16 width);
	void copy_to(Image &im);
	Image p_threshold(u16 thresh);
	Image n_threshold(u16 thresh);
};

Image :: Image(string filename) {
	/** 
		Constructor that creates a new image
		taking inputs from a file:
			Image im(file);
			Image *im = new Image(file);
	*/
	this->read(filename);
}

void Image :: set_pixel(u16 row, u16 column, u16 val) {
	/**
	    image.set_pixel(row, column, val);
	    sets value at a specified pixel

	    @param row: row index
	    @param column: column index
	    @param val: pixel intensity to set
	    @return nothing
	*/
	this->pix_mat.set_item(row, column, val);
}

u16 Image :: get_pixel(u16 row, u16 column){
	/**
	    image.get_pixel(row, column);
	    gets value of a specified pixel

	    @param row: row index
	    @param column: column index
	    @return pixel intensity
	*/
	return this->pix_mat.get_item(row, column);
}


void Image :: set_dim(u16 height, u16 width) {
	/**
	    image.set_dim(height, width);
	    sets dimension of a new image.
	    It doesn't actually resize the matrix in memory.
	    *Use it carefully on a non-empty matrix to prevent data loss.*


	    @param height: number of rows/height
	    @param width: number of columns/width
	    @return nothing
	*/
	this->dimension.row 	= height,
	this->dimension.column  = width;

	this->pix_mat.set_dim(height, width);
}

Size Image :: get_dim() {
	/**
	    image.get_dim();
	    
	    @param none
	    @return dimesion of image
	    @return_type Size
	*/
	return this->dimension;
}

int Image :: read(string filename) {	
	/**
	    image.read(file);
	    reads data from a pgm image file to the Image object

	    @param filename: file to read
	    @return operation status
	*/

	ifstream input; 		// input file handler
	string magic_number, 	// to store PGM tag to assert
			line;			// temp string to read file line by line
	int width, height;		// width and height of the image 

    input.open(filename);	

    if (input.is_open()) {
        getline(input, magic_number);		// reading the first line (the tag)
		stringstream meta_stream(magic_number);		// using stringstream here to split by spaces
		meta_stream >> magic_number;								
		//assert(magic_number == "P2");		// assuring magic number is P2

        meta_stream >> width; meta_stream >> height;	        
        this->set_dim(height, width);
        this->pix_mat.resize(height, width);

        u16 buffer; 			// temp variable to store pixel values
        u64 pixel = 0;			// temp variable to store count of pixels

        while (getline(input, line)) {
            /*
				going through the rest of file and reading values as integers
			*/
			stringstream pix_stream(line);
			while (pix_stream >> buffer) {
				int row = (pixel / height) % width, 	
                    col = (pixel++) % height; 		// calculating row and column from pixel count
                if (row < height && col < width)
					this->pix_mat.set_item(row, col, buffer); // setting the value in image
			}
        }
        input.close();
    } else	{			// if file coudn't be read
		cout<< "[Error: I/O Error] Either File not found or No permission to read" << endl;
		return IOERROR;
	}
}

int Image :: write(string filename)
{
	/**
	    image.write(file);
	    writes data to a pgm image file from the Image object

	    @param filename: file to write to
	    @return operation status
	*/

	ofstream output;	// output file handler
    output.open(filename);

    u16 h = this->dimension.row,
    	w = this->dimension.column;

    if(output.is_open()) {
    	/* writing the PGM tag */
        output << "P2 " << w << " " << h << " 255\n";
		
		/* writing pixel values to file */
		for (int i = 0; i < h ; i++) {
			for (int j = 0; j < w; j++)          
				output << (int)this->pix_mat.get_item(i, j) << " ";			
			output << '\n';
        }

        std::cout << filename << " generated.\n";
        output.close();
        
    } else	{	// if file couldn't be written
		cout<< "[Error: I/O Error] No permission to write" << endl;
		return IOERROR;
	}
} 

void Image :: resize(u16 height, u16 width)
{
	this->dimension.row = height;
	this->dimension.column = width;
	this->pix_mat.resize(height, width);
}

void Image :: copy_to(Image &im)
{
	u16 h = this->get_dim().row, 
		w = this->get_dim().column;
	im.resize(h, w);
	im.pix_mat.copy_from(this->pix_mat);
}

Image Image :: p_threshold(u16 thresh)
{
	Image im;
	this->copy_to(im);
	u16 h = this->get_dim().row, 
		w = this->get_dim().column;
	for (u16 i = 0; i < h; i++)
		for (u16 j = 0; j < w; j++)
			if (im.get_pixel(i, j) > thresh)
				im.set_pixel(i, j, 255);
			else im.set_pixel(i , j, 0);
	return im;		
}

Image Image :: n_threshold(u16 thresh)
{
	Image im;
	this->copy_to(im);
	u16 h = this->get_dim().row, 
		w = this->get_dim().column;
	for (u16 i = 0; i < h; i++)
		for (u16 j = 0; j < w; j++)
			if (im.get_pixel(i, j) > thresh)
				im.set_pixel(i, j, 0);
			else im.set_pixel(i, j, 255);
	return im;		
}

#endif