/*
* @Author: Vyn
* @Date:   2019-03-24 10:06:27
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-13 18:39:18
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

		void					Network::CalcNeuron(Neuron *neuron)
		{
			std::vector<Connection *>	connections;
			value_t 					currentDerivedValue;

			currentDerivedValue = 0;
			connections = neuron->GetOutputConnections();
			for (std::vector<Connection *>::size_type i = 0; i < connections.size(); ++i)
			{
				DEBUG_CHECK_VALUE(connections[i]->GetOutput()->GetDerivedError(), "Current derived value at output neuron");
				DEBUG_CHECK_VALUE(connections[i]->GetOutput()->GetDerivedValue(neuron), "Derived value w.r.t neuron (self)");
				DEBUG_CHECK_VALUE(currentDerivedValue, "Current derived value for self");
				currentDerivedValue += (connections[i]->GetOutput()->GetDerivedError() * connections[i]->GetOutput()->GetDerivedValue(neuron));
				DEBUG_CHECK_VALUE(currentDerivedValue, "New current derived value for self (" + std::to_string(connections[i]->GetOutput()->GetDerivedError()) + " * " + std::to_string(connections[i]->GetOutput()->GetDerivedValue(neuron)));
			}

			if (std::isinf(currentDerivedValue))
				throw std::string("current derived value inf");
			neuron->SetDerivedError(currentDerivedValue);
			UpdateNeuronWeights(neuron);
		}

		void					Network::UpdateNeuronWeights(Neuron *neuron)
		{
			std::vector<Connection *>	connections;
			
			connections = neuron->GetInputConnections();
			for (std::vector<Connection *>::size_type i = 0; i < connections.size(); ++i)
			{
				weight_t	gradient;

				DEBUG_CHECK_VALUE(neuron->GetDerivedError(), "Current derived error");
				DEBUG_CHECK_VALUE(neuron->GetDerivedValue(connections[i]), "Derived value w.r.t connection");
				gradient = neuron->GetDerivedError() * neuron->GetDerivedValue(connections[i]);
				//std::cout << neuron->GetDerivedError() << " * " << neuron->GetDerivedValue(connections[i]) << " " << neuron->GetActivationFunctionId() << std::endl;
				DEBUG_CHECK_VALUE(gradient, "gradient of weight");

				connections[i]->SetGradient(gradient);
				connections[i]->SetShouldUpdate(true);
			}
		}

		void					Network::Propagate(values_t goodValues, values_t derivedCost)
		{
			std::vector<Neuron *>		outputLayerNeurons;
			std::vector<Neuron *>		neurons;

			outputLayerNeurons = this->GetOutputLayer()->GetNeurons();
			for (std::vector<Neuron *>::size_type i = 0; i < outputLayerNeurons.size(); ++i)
			{
				DEBUG_CHECK_VALUE(derivedCost[i], "Derived cost");
				outputLayerNeurons[i]->SetDerivedError(derivedCost[i]);
				UpdateNeuronWeights(outputLayerNeurons[i]);
			}
			
			for (std::vector<Layer *>::size_type i = 0; i < layers.size() - 1; ++i)
			{
				neurons = layers[(layers.size() - 2) - i]->GetNeurons();
				for (std::vector<Neuron *>::size_type j = 0; j < neurons.size(); ++j)
				{
					if (!neurons[j]->IsBias())
						CalcNeuron(neurons[j]);
				}
			}
			this->UpdateWeights();
		}

		void					Network::Propagate(values_t goodValues)
		{
			std::vector<Neuron *>		outputLayerNeurons;
			values_t					derivedCost;

			outputLayerNeurons = this->GetOutputLayer()->GetNeurons();
			for (std::vector<Neuron *>::size_type i = 0; i < outputLayerNeurons.size(); ++i)
			{
				derivedCost.push_back(this->GetDerivedCost(goodValues, outputLayerNeurons[i]));
			}
			this->Propagate(goodValues, derivedCost);
		}

		void					Network::UpdateWeights()
		{
			value_t							maxGradient;
			bool							maxGradientFound = false;

			if (normalizedGradient)
			{
				for (std::vector<Connection *>::size_type i = 0; i < connections.size(); ++i)
				{
					if (connections[i]->ShouldUpdate())
					{
						value_t gradient;

						gradient = connections[i]->GetGradient();
						if (maxGradientFound == false || ABS(gradient) > maxGradient)
						{
							maxGradient = ABS(gradient);
							maxGradientFound = true;
						}
					}
				}
				if (maxGradient < 1)
					maxGradient = 1;
			}
			for (std::vector<Connection *>::size_type i = 0; i < connections.size(); ++i)
			{
				if (connections[i]->ShouldUpdate())
				{
					value_t gradient;

					gradient = connections[i]->GetGradient();
					if (normalizedGradient)
					{
						gradient = gradient / maxGradient;
						//std::cout << maxGradient << std::endl;
						DEBUG_CHECK_VALUE(gradient, "gradient value after normalization");
					}
					gradient = learningRate * gradient;
					DEBUG_CHECK_VALUE(gradient, "gradient value after learning rate");
					if (gradientClipping != 0)
					{
						if (gradient > gradientClipping)
							gradient = gradientClipping;
						else if (gradient < -gradientClipping)
							gradient = -gradientClipping;
					}
					connections[i]->SetWeight(connections[i]->GetWeight() - gradient);
					connections[i]->SetShouldUpdate(false);

					if (connections[i]->GetWeight() < -100 || connections[i]->GetWeight() > 100)
						throw std::string("Weight too high");

				}
			}
		}
	}
}