/*
* @Author: Vyn
* @Date:   2019-04-18 15:01:42
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-19 14:34:00
*/

#include <iostream>

#include "vtest/vtest.hpp"
#include "../includes/NeuralNetwork.h"

using vyn::neuralnetwork::value_t;

TEST(NETWORK)
{
	CASE("Training XOR")
	{
		vyn::neuralnetwork::Network network;

		network.AddLayer(2, NEURON_FUNCTION_NONE, WEIGHT_INIT_0, 1);
		network.AddLayer(2, NEURON_FUNCTION_SIGMOID, WEIGHT_INIT_0, 1);
		network.AddLayer(1, NEURON_FUNCTION_SIGMOID, WEIGHT_INIT_0, 0);
		network.SetLearningRate(0.1);
		network.SetCostFunction(COST_FUNCTION_MSE);

		vyn::neuralnetwork::TrainingParameters_t	parameters;

		std::vector<std::vector<value_t>>			inputs;
		std::vector<std::vector<value_t>>			outputs;

		std::vector<value_t> empty;
		inputs.push_back(empty);
		outputs.push_back(empty);
		inputs.push_back(empty);
		outputs.push_back(empty);
		inputs.push_back(empty);
		outputs.push_back(empty);
		inputs.push_back(empty);
		outputs.push_back(empty);

		inputs[0].push_back(0);
		inputs[0].push_back(0);
		outputs[0].push_back(0);

		inputs[1].push_back(0);
		inputs[1].push_back(1);
		outputs[1].push_back(1);

		inputs[2].push_back(1);
		inputs[2].push_back(0);
		outputs[2].push_back(1);

		inputs[3].push_back(1);
		inputs[3].push_back(1);
		outputs[3].push_back(0);

		parameters.trainingSetInputs = inputs;
		parameters.trainingSetOutputs = outputs;

		network.Fit(parameters, 1, 20000);

		network.Predict(inputs[0]);
		//std::cout << network.GetOutputLayer()->GetNeurons()[0]->GetValue() << std::endl;
		WARN(network.GetOutputLayer()->GetNeurons()[0]->GetValue() < 0.1);
		network.Predict(inputs[1]);
		//std::cout << network.GetOutputLayer()->GetNeurons()[0]->GetValue() << std::endl;
		WARN(network.GetOutputLayer()->GetNeurons()[0]->GetValue() > 0.9);
		network.Predict(inputs[2]);
		//std::cout << network.GetOutputLayer()->GetNeurons()[0]->GetValue() << std::endl;
		WARN(network.GetOutputLayer()->GetNeurons()[0]->GetValue() > 0.9);
		network.Predict(inputs[3]);
		//std::cout << network.GetOutputLayer()->GetNeurons()[0]->GetValue() << std::endl;
		WARN(network.GetOutputLayer()->GetNeurons()[0]->GetValue() < 0.1);
	}
	
	TEST_EXIT(TEST_SUCCESS);
}