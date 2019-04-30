/*
* @Author: Vyn
* @Date:   2019-02-02 11:29:39
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-07 15:26:48
*/

#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include <float.h>

#include "Network.h"
#include "Layer.h"
#include "Neuron.h"
#include "Connection.h"

#define ABS(x) (x < 0 ? -x : x)

namespace vyn
{
	namespace neuralnetwork
	{
		Network::Network()
		{

		}

		void					Network::AddLayer(int nbNeuron, int neuronType, int weightInitializationFunctionId, int nbBias)
		{
			Layer	*newLayer;
			newLayer = new Layer(nbNeuron, neuronType, weightInitializationFunctionId, nbBias);
			AddLayer(newLayer);
		}

		void					Network::AddLayer(Layer *layer)
		{
			Layer	*lastLayer;

			layer->SetParentNetwork(this);
			if (layers.size() == 0)
			{
				layers.push_back(layer);
				return ;
			}
			lastLayer = layers[layers.size() - 1];
			lastLayer->ConnectTo(layer);
			layers.push_back(layer);
		}

		void					Network::SetCostFunction(int id)
		{
			costFunctionId = id;
			if (id == COST_FUNCTION_MSE)
			{
				costFunction = &SquaredError;
				costFunctionDerivative = &SquaredErrorDerivative;
			}
			else if (id == COST_FUNCTION_CE)
			{
				costFunction = &CrossEntropy;
				costFunctionDerivative = &CrossEntropyDerivative;
			}
		}

		std::vector<value_t>	Network::Predict(std::vector<value_t> inputs)
		{
			std::vector<Neuron *>	inputLayerNeurons;
			std::vector<Neuron *>	outputLayerNeurons;
			std::vector<value_t>	outputValues;

			if (layers.size() < 2)
				throw std::string("There must be minimum 2 layers (input & output)");
			inputLayerNeurons = layers[0]->GetNeurons();
			if (inputLayerNeurons.size() - layers[0]->GetBiasCount() != inputs.size())
				throw std::string("Missing inputs");
			for (std::vector<Neuron *>::size_type i = 0; i < inputs.size(); ++i)
				inputLayerNeurons[i]->SetValue(inputs[i]);
			for (std::vector<Layer *>::size_type i = 1; i < layers.size(); ++i)
				layers[i]->ComputeValues();
			outputLayerNeurons = layers[layers.size() - 1]->GetNeurons();
			for (std::vector<Neuron *>::size_type i = 0; i < outputLayerNeurons.size(); ++i)
				outputValues.push_back(outputLayerNeurons[i]->GetValue());
			lastPredictionValues = outputValues;
			return (outputValues);
		}

		value_t					Network::GetCost(values_t expectedOutput)
		{
			if (costFunction != nullptr)
				return ((*costFunction)(GetOutputLayer()->GetNeurons(), expectedOutput));
			throw std::string("No cost function defined");
		}

		value_t					Network::GetDerivedCost(values_t expectedOutput, Neuron *outputNeuron)
		{
			if (costFunctionDerivative != nullptr)
				return ((*costFunctionDerivative)(GetOutputLayer()->GetNeurons(), expectedOutput, outputNeuron));
			throw std::string("No cost function derivative defined");
		}

		Layer					*Network::GetInputLayer() const
		{
			if (layers.size() > 0)
				return (layers[0]);
			return (nullptr);
		}

		Layer					*Network::GetOutputLayer() const
		{
			if (layers.size() > 1)
				return (layers[layers.size() - 1]);
			return (nullptr);
		}

		void					Network::SaveTo(std::string fileName)
		{
			std::ofstream file;
			file.open(fileName);
			file << VYN_NEURALNETWORK_STRING << std::endl;
			file << VYN_NEURALNETWORK_VERSION << std::endl;
			file << layers.size() << std::endl;
			for (std::vector<Layer *>::size_type i = 0; i < layers.size(); ++i)
			{
				std::vector<Neuron *> neurons;
				neurons = layers[i]->GetNeurons();
				for (std::vector<Neuron *>::size_type j = 0; j < neurons.size(); ++j)
				{
					file << neurons[j]->GetActivationFunctionId() << " ";
				}
				file << std::endl;
			}
			file << this->GetCostFunctionId() << std::endl;

			for (std::vector<Connection *>::size_type i = 0; i < connections.size(); ++i)
			{
				file << connections[i]->GetWeight() << " ";
			}
			file.close();
		}

		void					Network::RandomizeConnectionsWeight()
		{
			for (int i = 0; i < connections.size(); ++i)
			{
				connections[i]->SetWeight(connections[i]->GetInput()->GetParentLayer()->NewWeightValue());
			}
		}
	}
}