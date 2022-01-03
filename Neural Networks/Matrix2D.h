#pragma once
#include <string>

using namespace std;

class Matrix2D {
	string name = "";
	int rows = 0;
	int cols = 0;
	double defaultValue = 0;
	void init();
	double vectorMultiply(double** a, double** b, int aRow, int bCol, int length);
	void allocate();

public:
	double** mat;
	void print();
	void fill(double* data[]);
	void fill(double* data); //for vector matrices
	void multiply(Matrix2D& other, Matrix2D& res);
	Matrix2D get();
	void operator =(Matrix2D& other);

	Matrix2D(string N = "");
	Matrix2D(int R, int C, string N = "");
	~Matrix2D();
};