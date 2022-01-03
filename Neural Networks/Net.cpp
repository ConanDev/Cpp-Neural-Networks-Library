#include "Net.h"
#include <iostream>
#include <string>

using namespace std;

void Net::setRow2Row(double* a, double* b, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		a[i] = b[i];
	}
}

void Net::setRow2Col(double* a, double** b, int col, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		a[i] = b[i][col];
	}
}

void Net::printArray(double* a, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		cout << a[i] << " ";
	}
}

void Net::printWeights()
{
	cout << "Network weights: " << endl;
	for (size_t l = 0; l < numOfLayers - 1; l++)
	{
		int current = nodesPerLayer[l];
		int next = nodesPerLayer[l + 1];
		for (size_t i = 0; i < next; i++)
		{
			for (size_t j = 0; j < current; j++)
			{
				cout << weights[l][i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void Net::printNodes()
{
	for (size_t l = 0; l < numOfLayers; l++)
	{
		int current = nodesPerLayer[l];
		cout << "Layer " << l + 1 << ": ";
		for (size_t i = 0; i < current; i++)
		{
			cout << layers[l][i] << " ";
		}
		cout << endl;
	}
}

void Net::feedForward(double* input)
{
	if (input != NULL) {
		setRow2Row(layers[0], input, inputSize);
	}
	for (size_t i = 0; i < numOfLayers - 1; i++)
	{
		//inefficient
		int current = nodesPerLayer[i];
		int next = nodesPerLayer[i + 1];
		Matrix2D weight(next, current);
		weight.fill(weights[i]);

		Matrix2D layer(current, 1);
		layer.fill(layers[i]);//problem here

		Matrix2D res("Layer " + to_string(i));
		weight.multiply(layer, res);
		setRow2Col(layers[i + 1], res.mat, 0, next);
	}
	cout << "FeedForward:" << endl;
	printArray(layers[numOfLayers - 1], outputSize);
}

Net::Net(int nodesPerLayer[], int numOfLayers, WeightInit wInit) : numOfLayers(numOfLayers)
{
	this->nodesPerLayer = new int[numOfLayers];
	layers = new double* [numOfLayers];
	for (size_t i = 0; i < numOfLayers; i++)
	{
		this->nodesPerLayer[i] = nodesPerLayer[i];
		layers[i] = new double[nodesPerLayer[i]];
	}
	//weights is an array of 2d matrices
	weights = new double** [numOfLayers];
	for (size_t l = 0; l < numOfLayers - 1; l++)
	{
		//number of nodes of current and next layers
		int current = nodesPerLayer[l]; //weights.cols
		int next = nodesPerLayer[l + 1]; //weights.rows
		weights[l] = new double* [next];
		for (size_t i = 0; i < next; i++)
		{
			weights[l][i] = new double[current];
			//initialize weights
			for (size_t j = 0; j < current; j++)
			{
				double w;
				switch (wInit) {
				case zeros:
					w = 0;
					break;
				case ones:
					w = 1;
					break;
				case random:
					w = (double) (rand() % 100);
				}

				weights[l][i][j] = w;
			}
		}
	}
	inputSize = nodesPerLayer[0];
	outputSize = nodesPerLayer[numOfLayers - 1];
}

Net::~Net()
{
	//actual layers
	for (size_t i = 0; i < numOfLayers; i++)
	{
		delete[] layers[i];
	}
	delete[] layers;
	for (size_t l = 0; l < numOfLayers - 1; l++)
	{
		//free weights
		int next = nodesPerLayer[l + 1];
		for (size_t i = 0; i < next; i++)
		{
			delete[] weights[l][i];
		}
		delete[] weights[l];
	}
	delete[] weights;
	//layer nodes cardinalities
	delete[] nodesPerLayer;
}
