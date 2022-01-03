#pragma once
#include "Matrix2D.h"

using namespace std;
enum WeightInit {zeros, ones, random};
class Net
{
	int inputSize = 0;
	int outputSize = 0;
	int* nodesPerLayer; //*> number of nodes per layer
	int numOfLayers = 0;
	double** layers;
	double*** weights;
	void setRow2Row(double* a, double* b, int length); //changes the values of 'a' to match 'b'
	void setRow2Col(double* a, double** b, int col, int length);
	void printArray(double* a, int length);

public:
	void printWeights();
	void printNodes();
	void feedForward(double* input = NULL);
	Net(int layers[], int numOfLayers, WeightInit wInit= random);
	~Net();
};

