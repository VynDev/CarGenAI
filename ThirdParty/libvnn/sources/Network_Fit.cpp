/*
* @Author: Vyn
* @Date:   2019-03-10 18:33:50
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-19 14:22:53
*/

#include "Network.h"
#include "Layer.h"
#include "Neuron.h"
#include "Connection.h"

#include <iostream>
#include <cmath>

namespace vyn
{

	namespace neuralnetwork
	{
		value_t			PredictOne(Network *network, std::vector<value_t> &inputs, std::vector<value_t> &expectedOutputs)
		{
			network->Predict(inputs);
			return (network->GetCost(expectedOutputs));
		}

		value_t			Network::TrainBatch(Network *network, std::vector<std::vector<value_t>> &inputs, std::vector<std::vector<value_t>> &expectedOutputs, int batchSize, int i)
		{
			value_t								totalCost;
			std::vector<Neuron *>				outputLayerNeurons;
			std::vector<value_t>				derivedCosts;

			totalCost = 0;
			outputLayerNeurons = network->GetOutputLayer()->GetNeurons();

			for (std::vector<Neuron *>::size_type k = 0; k < outputLayerNeurons.size(); ++k)
			{
				derivedCosts.push_back(0);
			}
			if (inputs.size() - i < batchSize)
				batchSize = inputs.size() - i;
			for (int j = 0; j < batchSize; ++j)
			{
				totalCost += PredictOne(network, inputs[i + j], expectedOutputs[i + j]);
				for (std::vector<Neuron *>::size_type k = 0; k < outputLayerNeurons.size(); ++k)
				{
					derivedCosts[k] = derivedCosts[k] + network->GetDerivedCost(expectedOutputs[i + j], outputLayerNeurons[k]);
				}
			}
			totalCost = totalCost / batchSize;
			for (std::vector<value_t>::size_type k = 0; k < outputLayerNeurons.size(); ++k)
			{
				derivedCosts[k] = derivedCosts[k] / batchSize;
			}
			if (totalCost > errorPropagationLimit)
				network->Propagate(expectedOutputs[i], derivedCosts);
			return (totalCost);
		}

		value_t					ValidationSet(Network *network, TrainingParameters_t &parameters)
		{
			value_t	totalCost;

			totalCost = 0;
			for (int i = 0; i < parameters.validationSetInputs.size(); ++i)
			{
				totalCost += PredictOne(network, parameters.validationSetInputs[i], parameters.validationSetOutputs[i]);
			}
			totalCost = totalCost / parameters.validationSetInputs.size();
			return (totalCost);
		}

		void					Network::Fit(TrainingParameters_t parameters, int batchSize, int nbIteration)
		{
			value_t					totalCost;
			value_t					validationCost = -1;
			value_t					lastValidationCost = -1;
			int						noImprovementEpoch = 0;
			int						noImprovementEpochLimit = 0;
			int						k;

			//std::cout << "Training, batch size = " << batchSize << ", nbIteration = " << nbIteration << std::endl;
			if (parameters.trainingCsv)
			{
				*(parameters.trainingCsv) << parameters.trainingSetInputs.size() << std::endl;
				*(parameters.trainingCsv) << batchSize << std::endl;
			}
			if (parameters.validationCsv)
			{
				*(parameters.validationCsv) << parameters.validationSetInputs.size() << std::endl;
				*(parameters.validationCsv) << parameters.validationSetInputs.size() << std::endl;
			}
			for (int i = 0; i < nbIteration; ++i)
			{
				totalCost = 0;
				k = 0;
				for (int j = 0; j < parameters.trainingSetInputs.size(); j += batchSize)
				{
					value_t		cost;
					cost = TrainBatch(this, parameters.trainingSetInputs, parameters.trainingSetOutputs, batchSize, j);
					totalCost += cost;
					++k;
					if (parameters.trainingCsv != nullptr)
						*(parameters.trainingCsv) << cost << std::endl;
					DEBUG_CHECK_VALUE(cost, "Cost");
				}
				totalCost = totalCost / k;
				//std::cout << "[" << i << "] Cost: " << totalCost << "    (learning rate: " << GetLearningRate() << ")" << std::endl;
				if (parameters.validationCsv != nullptr)
				{
					validationCost = ValidationSet(this, parameters);
					*(parameters.validationCsv) << validationCost << std::endl;
				}
				// early stopping
				if (earlyStoppingEnabled && validationCost != -1)
				{
					++noImprovementEpoch;
					if (lastValidationCost == -1 || validationCost < lastValidationCost)
						noImprovementEpoch = 0;
					if (noImprovementEpoch > noImprovementEpochLimit)
					{
						std::cout << "Training finished (early stopping)" << std::endl;
						return ;
					}
					lastValidationCost = validationCost;
				}
				
			}
			//std::cout << "Training finished" << std::endl;
		}
	}
}