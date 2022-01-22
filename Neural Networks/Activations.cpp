#include "Activations.h"
#include <math.h>

double Sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double Relu(double x)
{
    return x < 0 ? 0 : x;
}

double Identity(double x)
{
    return x;
}
