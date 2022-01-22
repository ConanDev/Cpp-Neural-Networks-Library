#pragma once
#include "Matrix2D.h"
#include "Activations.h"

using namespace std;
enum WeightInit {zeros, ones, random};
enum Activation {none, relu, sigmoid};

class Net
{
	int inputSize = 0;
	int outputSize = 0;
	int* nodesPerLayer; //*> number of nodes per layer
	int numOfLayers = 0;
	double** layers;
	double** biases;
	double*** weights;
	Activation* activations = NULL;
	template <class T>
	void setRow2Row(T* a, T* b, int length) {
		//changes the values of 'a' to match 'b'
		for (size_t i = 0; i < length; i++)
		{
			a[i] = b[i];
		}
	} 
	//for now, no need for template for setRow2Col
	void setRow2Col(double* a, double** b, int col, int length);
	void printArray(double* a, int length);

public:
	void printWeights();
	void printNodes();
	void feedForward(double* input = NULL);
	Net(int layers[], int numOfLayers, WeightInit wInit= random, Activation* acts = NULL);
	~Net();
};

