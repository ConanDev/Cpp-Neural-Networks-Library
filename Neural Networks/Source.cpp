#include "Matrix2D.h"
#include "Net.h"
#include <iostream>

using namespace std;

void Mat() {
	Matrix2D m1(2, 3, "m1");
	double m11[]{ 1,2,3 };
	double m12[]{ 4,5,6 };
	double* m1_[]{ m11, m12 };
	m1.fill(m1_);

	Matrix2D m2(3, 2, "m2");
	double m21[]{ 7,8 };
	double m22[]{ 9, 10 };
	double m23[]{ 11, 12 };
	double* m2_[]{ m21, m22, m23 };
	m2.fill(m2_);

	Matrix2D m3("m3");
	m1.multiply(m2, m3);
	m3.print();
}

void NN() {
	int nodesPerLayer[]{ 2,3,3,2 };
	Activation acts[]{ none, relu, sigmoid, sigmoid };
	Net n1(nodesPerLayer, 4, random, acts); //did not allow me to skip default arg wInit
	n1.printWeights();
	double input[]{ 1,2 };
	n1.feedForward(input);
	cout << endl;
	n1.printNodes();
}

int main() {
	NN();

	return 0;
}