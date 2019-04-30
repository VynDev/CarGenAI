#ifndef CONNECTION_H
#define CONNECTION_H

#include <vector>
#include <cstdlib>

#include "types.h"

namespace vyn
{
	namespace neuralnetwork
	{
		class Connection {

		/*
		**	Global neural network
		*/
		private:


			Neuron								*input = nullptr;
			Neuron								*output = nullptr;
			weight_t							weight = 0;

		public:

			Connection();

			void								SetInput(Neuron *neuron) {input = neuron;};
			void								SetOutput(Neuron *neuron) {output = neuron;};
			void								SetWeight(weight_t newWeight) {weight = newWeight;};


			Neuron								*GetInput() const {return (input);};
			Neuron								*GetOutput() const {return (output);};
			weight_t							GetWeight() const {return (weight);};
		/*
		**	Back propagation
		*/
		private:

			value_t								gradient = 0;
			bool								shouldUpdate = false;

		public:

			void								SetGradient(value_t newGradient) {gradient = newGradient;};
			void								SetShouldUpdate(bool a) {shouldUpdate = a;};

			weight_t							GetGradient() const {return (gradient);};
			bool								ShouldUpdate() const {return (shouldUpdate);};
		};
	}
}
#endif