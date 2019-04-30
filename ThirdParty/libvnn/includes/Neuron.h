#ifndef NEURON_H
#define NEURON_H

#include <vector>

#include "Layer.h"
#include "types.h"
#include "activationFunctions.h"

namespace vyn
{
	namespace neuralnetwork
	{
		/** 
		*	Neuron component of the neural network
		*/

		class Neuron {

		/*
		**	Global neural network
		*/
		private:

			static int					nbNeuron;

			const int					id = nbNeuron;
			std::vector<Connection *>	inputs;
			std::vector<Connection *>	outputs;
			value_t						rawValue;
			value_t						value = 1;
			value_t						(*activationFuntion)(Neuron *, value_t) = nullptr;
			value_t						(*activationFuntionDerivative)(Neuron *, value_t) = nullptr;
			int							activationFunctionId = 0;
			bool						isBias = false;

			Layer						*parentLayer = nullptr;
			friend void					Layer::AddNeuron(int functionId);
			friend void					Layer::AddBias();
			void						SetParentLayer(Layer *layer) {parentLayer = layer;};

		public:

			Neuron();
			Neuron(int type);
			
			void						ConnectTo(Neuron *neuron);
			void						AddInputConnection(Connection *newConnection);
			void						ComputeValue();
			void						ActivateFunction();
			void						SetValue(value_t newValue) {value = newValue;};
			void						SetBias(bool newValue) {isBias = newValue;};

			void						SetActivationFunction(int id);
			void						SetActivationFunction(value_t (*f)(Neuron *, value_t)) {activationFunctionId = 0; activationFuntion = f;};

			bool						IsBias() const {return (isBias);};

			int							GetActivationFunctionId() const {return (activationFunctionId);};
			std::vector<Connection *>	GetInputConnections() const {return (inputs);};
			std::vector<Connection *>	GetOutputConnections() const {return (outputs);};
			int							GetId() const {return (id);};
			Layer						*GetParentLayer() const {return (parentLayer);};

			value_t						GetValue() const {return (value);};
			value_t						GetRawValue() const {return (rawValue);};

			value_t						(*GetActivationFunction(void))(Neuron *, value_t) {return (activationFuntion);};
		/*
		**	Back propagation
		*/
		private:

			value_t						derivedError = 0;

		public:

			void						SetDerivedError(value_t newValue) {derivedError = newValue;};

			value_t						GetDerivedValue(Connection *connection); // derived with respect to weight
			value_t						GetDerivedValue(Neuron *neuron); // derived with respect to neuron
			value_t						GetDerivedError() const {return (derivedError);};

			void						SetActivationFunctionDerivative(value_t (*f)(Neuron *, value_t)) {activationFunctionId = 0; activationFuntionDerivative = f;};

		};
	}
}

#endif