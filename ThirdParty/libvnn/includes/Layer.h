#ifndef LAYER_H
#define LAYER_H

#define LAYER_UNCONNECTED 0
#define LAYER_INPUT 1
#define LAYER_HIDDEN 2
#define LAYER_OUTPUT 3

#define WEIGHT_INIT_0 0
#define WEIGHT_INIT_1 1

#include <vector>
#include "types.h"

namespace vyn
{
	namespace neuralnetwork
	{
		class Layer {

		private:

			static int	nbLayer;

			const int										id = nbLayer;

			Network											*parentNetwork = nullptr;
			std::vector<vyn::neuralnetwork::Neuron *>		neurons;
			Layer											*input = nullptr;
			Layer											*output = nullptr;
			int												type = LAYER_UNCONNECTED;
			int												nbBias = 0;
			bool											twoStepActivationEnabled = true;

			value_t											(*weightInitializationFunction)(Layer *) = nullptr;

		public:

			Layer();
			Layer(int nbNeuron, int functionId, int weightInitializationFunctionId, int nbBias = 0);

			void											SetParentNetwork(Network *network) {parentNetwork = network;};
			Network											*GetParentNetwork() const {return (parentNetwork);};

			void											ConnectTo(Layer *layer);
			void											AddInput(Layer *layer);
			void											AddNeuron(int functionId);
			void											AddBias();
			void											ComputeValues();
			void											Describe(bool showNeuronsValue = false);
			void											EnableTwoStepActivation(bool newValue) {twoStepActivationEnabled = newValue;};

			void											SetWeightInitialization(int initializationId);
			value_t											NewWeightValue() {return ((*weightInitializationFunction)(this));};

			std::vector<vyn::neuralnetwork::Neuron *>		GetNeurons() const {return (neurons);};
			std::vector<value_t>							GetValues() const;
			int												GetBiasCount() const {return (nbBias);};
		};
	}
}
#endif