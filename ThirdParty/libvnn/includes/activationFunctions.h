#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#define NEURON_FUNCTION_NONE 0
#define NEURON_FUNCTION_BIAS 1
#define NEURON_FUNCTION_SIGMOID 2
#define NEURON_FUNCTION_SOFTMAX 3

#include "types.h"

namespace vyn
{
	namespace neuralnetwork
	{
		value_t		Sigmoid(Neuron *, value_t x);
		value_t		SigmoidDerivative(Neuron *, value_t x);

		value_t		Softmax(Neuron *, value_t x);
		value_t		SoftmaxDerivative(Neuron *, value_t x);

		value_t		weightInitialization0(Layer *layer);
		value_t		weightInitialization1(Layer *layer);

		void		DefaultCrossOverFunction(Population *population);
	}
}
#endif