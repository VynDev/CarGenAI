#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>
#include <sstream>
#include <float.h>

#include "types.h"
#include "utils.h"
#include "costFunctions.h"

#define VYN_NEURALNETWORK_STRING "VYN_NEURALNETWORK"
#define VYN_NEURALNETWORK_VERSION "0.0.0"

//#define DEBUG // Comment this line to disable debug mode
#ifdef DEBUG
	#define DEBUG_CHECK_VALUE(x, msg) debug::CheckValue(x, std::string(__FUNCTION__) + std::string(": ") + msg)
#else
	#define DEBUG_CHECK_VALUE(x, msg)
#endif

namespace vyn
{
	namespace neuralnetwork
	{
		typedef struct								TrainingParameters_s
		{
			std::vector<std::vector<value_t>>		trainingSetInputs;
			std::vector<std::vector<value_t>>		trainingSetOutputs;
			std::vector<std::vector<value_t>>		validationSetInputs;
			std::vector<std::vector<value_t>>		validationSetOutputs;
			std::stringstream 						*trainingCsv = nullptr;
			std::stringstream 						*validationCsv = nullptr;

		}											TrainingParameters_t;

		class Network {

		/*
		**	Global neural network
		*/
		private:

			

			std::vector<Layer *>		layers;
			std::vector<Connection *>	connections;

			value_t						(*costFunction)(std::vector<Neuron *>, values_t) = nullptr;
			value_t						(*costFunctionDerivative)(std::vector<Neuron *>, values_t, Neuron *) = nullptr;
			int							costFunctionId = 0;
			std::vector<value_t>		lastPredictionValues;

		public:

			Network();


			Layer						*GetInputLayer() const;
			Layer						*GetOutputLayer() const;
			std::vector<Layer *>		GetLayers() const {return (layers);};
			std::vector<Connection *>	GetConnections() const {return (connections);};

			void						AddConnection(Connection *newConnection) {connections.push_back(newConnection);};
			void						RandomizeConnectionsWeight();

			void						AddLayer(Layer *layer);
			void						AddLayer(int nbNeuron, int neuronType = 0, int weightInitializationFunctionId = 0, int nbBias = 0);
			
			std::vector<value_t>		Predict(std::vector<value_t> inputs);

			void						SaveTo(std::string fileName);

		/*
		**	Back propagation
		*/

		private:

			value_t						learningRate = 0.1;
			value_t						gradientClipping = 0;
			bool						normalizedGradient = false;
			bool						earlyStoppingEnabled = false;
			value_t						errorPropagationLimit = 0;


			void						UpdateWeights();

		public:

			value_t						GetLearningRate() const {return (learningRate);};
			void						SetLearningRate(value_t newValue) {learningRate = newValue;};

			value_t						GetCost(values_t expectedOutput);
			value_t						GetDerivedCost(values_t expectedOutput, Neuron *outputNeuron);
			int							GetCostFunctionId() const {return (costFunctionId);};

			void						SetCostFunction(int functionId);
			void						SetCostFunction(value_t (*f)(std::vector<Neuron *>, values_t)) {costFunctionId = 0; costFunction = f;};
			void						SetCostFunctionDerivative(value_t (*f)(std::vector<Neuron *>, values_t, Neuron *)) {costFunctionId = 0; costFunctionDerivative = f;};

			void						SetGradientClipping(value_t newValue) {gradientClipping = (newValue < 0 ? -newValue : newValue);};
			void						EnableNormalizedGradient(bool newValue) {normalizedGradient = newValue;};
			void						EnableEarlyStopping(bool newValue) {earlyStoppingEnabled = newValue;};
			void						SetErrorPropagationLimit(value_t newValue) {errorPropagationLimit = newValue;};

			void						Fit(TrainingParameters_t parameters, int batchSize, int nbIteration);
			value_t						TrainBatch(Network *network, std::vector<std::vector<value_t>> &inputs, std::vector<std::vector<value_t>> &expectedOutputs, int batchSize, int i);
			void						Propagate(values_t goodValues);
			void						Propagate(values_t goodValues, values_t derivedCost);
			void						UpdateNeuronWeights(Neuron *neuron);
			void						CalcNeuron(Neuron *neuron);

		};
	}
}
#endif