#ifndef TYPES_H
#define TYPES_H

#include <vector>

namespace vyn
{
	namespace neuralnetwork
	{
		class Neuron;
		class Connection;
		class Layer;
		class Network;
		class Population;

		typedef double value_t;
		typedef double weight_t;
		typedef std::vector<value_t> values_t;
	}
}

#endif