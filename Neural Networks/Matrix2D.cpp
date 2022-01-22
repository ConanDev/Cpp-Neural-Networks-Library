#include "Matrix2D.h"
#include <iostream>

using namespace std;
typedef Matrix2D Matrix;

void Matrix2D::init()
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			mat[i][j] = defaultValue;
		}
	}
}

double Matrix2D::vectorMultiply(double** a, double** b, int aRow, int bCol, int length)
{
	//multiplies row 'aRow' from matrix 'a'
	//with column 'bCol' from matrix 'b'
	//both have length 'length'
	double sum = 0;
	for (size_t i = 0; i < length; i++)
	{
		sum += a[aRow][i] * b[i][bCol];
	}
	return sum;
}

void Matrix2D::allocate()
{
	mat = new double* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		mat[i] = new double[cols];
	}
}

void Matrix2D::print()
{
	cout << "Matrix " << name << ":" << endl;
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}



void Matrix2D::fill(double* data[])
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			mat[i][j] = data[i][j];
		}
	}
}

void Matrix2D::fill(double* data)
{
	if (cols == 1) {
		for (size_t i = 0; i < rows; i++)
		{
			mat[i][0] = data[i];
		}
	}
	else if (rows == 1) {
		for (size_t i = 0; i < cols; i++)
		{
			mat[0][i] = data[i];
		}
	}
	else {
		cerr << "Warning: fill(double*) should not be used here." << endl;
	}
}

void Matrix2D::multiply(Matrix2D& other, Matrix2D& dest)
{
	if (cols != other.rows) {
		cerr << "Error: Attempting to multiply matrices with dimensions "
			<< rows << " x " << cols << " with " << other.rows << " x " << other.cols
			<< ". Aborting." << endl;
		return;
	}
	Matrix res(rows, other.cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < other.cols; j++)
		{
			res.mat[i][j] = vectorMultiply(mat, other.mat, i, j, cols);
		}
	}
	dest = res;
}

void Matrix2D::scale(double scalar)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			mat[i][j] *= scalar;
		}
	}
}

void Matrix2D::apply(double(*actFn)(double))
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			mat[i][j] = actFn(mat[i][j]);
		}
	}
}

Matrix2D Matrix2D::get()
{
	return Matrix2D(2, 2);
}

void Matrix2D::operator=(Matrix2D& other)
{
	rows = other.rows;
	cols = other.cols;
	allocate();
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			mat[i][j] = other.mat[i][j];
		}
	}
}

Matrix2D::Matrix2D(string N) : name(N)
{
}

Matrix2D::Matrix2D(int R, int C, string N) : rows(R), cols(C), name(N)
{
	allocate();
	init();
}

Matrix2D::~Matrix2D()
{
	for (size_t i = 0; i < rows; i++)
	{
		delete[] mat[i];
	}
	delete[] mat;
}
