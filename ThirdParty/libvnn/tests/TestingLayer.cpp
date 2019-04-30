/*
* @Author: Vyn
* @Date:   2019-04-18 15:01:42
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-19 12:13:30
*/

#include <iostream>

#include "vtest/vtest.hpp"
#include "../includes/NeuralNetwork.h"

TEST(LAYER)
{
	CASE("Add neuron & bias")
	{
		vyn::neuralnetwork::Layer	layer;

		REQUIRE(layer.GetNeurons().size() == 0);
		REQUIRE(layer.GetBiasCount() == 0);
		layer.AddNeuron(NEURON_FUNCTION_SIGMOID);
		REQUIRE(layer.GetNeurons().size() == 1);
		REQUIRE(layer.GetBiasCount() == 0);
		layer.AddNeuron(NEURON_FUNCTION_SIGMOID);
		REQUIRE(layer.GetNeurons().size() == 2);
		REQUIRE(layer.GetBiasCount() == 0);
		layer.AddBias();
		REQUIRE(layer.GetNeurons().size() == 3);
		REQUIRE(layer.GetBiasCount() == 1);
	}

	CASE("Basic (testing connections)")
	{
		vyn::neuralnetwork::Layer	inputLayer(1, NEURON_FUNCTION_NONE, WEIGHT_INIT_0, 0);
		vyn::neuralnetwork::Layer	outputLayer(1, NEURON_FUNCTION_SIGMOID, WEIGHT_INIT_0, 0);

		REQUIRE(inputLayer.GetNeurons().size() == 1);
		REQUIRE(outputLayer.GetNeurons().size() == 1);
		REQUIRE(inputLayer.GetBiasCount() == 0);
		REQUIRE(outputLayer.GetBiasCount() == 0);

		inputLayer.ConnectTo(&outputLayer);
		std::vector<vyn::neuralnetwork::Neuron *>	inputNeurons;
		std::vector<vyn::neuralnetwork::Neuron *>	outputNeurons;
		
		inputNeurons = inputLayer.GetNeurons();
		outputNeurons = outputLayer.GetNeurons();
		for (int i = 0; i < inputNeurons.size(); ++i)
		{
			for (int j = 0; j < outputNeurons.size(); ++j)
			{
				REQUIRE(inputNeurons[i]->GetOutputConnections()[j]->GetOutput() == outputNeurons[j]);
			}
		}
	}

	CASE("Basic with bias (testing connections)")
	{
		vyn::neuralnetwork::Layer	inputLayer(1, NEURON_FUNCTION_NONE, WEIGHT_INIT_0, 1);
		vyn::neuralnetwork::Layer	outputLayer(1, NEURON_FUNCTION_SIGMOID, WEIGHT_INIT_0, 0);

		REQUIRE(inputLayer.GetNeurons().size() == 2);
		REQUIRE(outputLayer.GetNeurons().size() == 1);
		REQUIRE(inputLayer.GetBiasCount() == 1);
		REQUIRE(outputLayer.GetBiasCount() == 0);

		inputLayer.ConnectTo(&outputLayer);
		std::vector<vyn::neuralnetwork::Neuron *>	inputNeurons;
		std::vector<vyn::neuralnetwork::Neuron *>	outputNeurons;
		
		inputNeurons = inputLayer.GetNeurons();
		outputNeurons = outputLayer.GetNeurons();
		for (int i = 0; i < inputNeurons.size(); ++i)
		{
			for (int j = 0; j < outputNeurons.size(); ++j)
			{
				REQUIRE(inputNeurons[i]->GetOutputConnections()[j]->GetOutput() == outputNeurons[j]);
			}
		}
	}

	CASE("Less basic (testing connections)")
	{
		vyn::neuralnetwork::Layer	inputLayer(42, NEURON_FUNCTION_NONE, WEIGHT_INIT_0, 1);
		vyn::neuralnetwork::Layer	outputLayer(21, NEURON_FUNCTION_SIGMOID, WEIGHT_INIT_0, 0);

		REQUIRE(inputLayer.GetNeurons().size() == 43);
		REQUIRE(outputLayer.GetNeurons().size() == 21);
		REQUIRE(inputLayer.GetBiasCount() == 1);
		REQUIRE(outputLayer.GetBiasCount() == 0);

		inputLayer.ConnectTo(&outputLayer);
		std::vector<vyn::neuralnetwork::Neuron *>	inputNeurons;
		std::vector<vyn::neuralnetwork::Neuron *>	outputNeurons;
		
		inputNeurons = inputLayer.GetNeurons();
		outputNeurons = outputLayer.GetNeurons();
		for (int i = 0; i < inputNeurons.size(); ++i)
		{
			for (int j = 0; j < outputNeurons.size(); ++j)
			{
				REQUIRE(inputNeurons[i]->GetOutputConnections()[j]->GetOutput() == outputNeurons[j]);
			}
		}
	}

	CASE("Compute values & get values")
	{
		vyn::neuralnetwork::Layer	inputLayer(2, NEURON_FUNCTION_NONE, WEIGHT_INIT_0, 1);
		vyn::neuralnetwork::Layer	outputLayer(2, NEURON_FUNCTION_SIGMOID, WEIGHT_INIT_0, 0);

		inputLayer.ConnectTo(&outputLayer);
		std::vector<vyn::neuralnetwork::Neuron *>	inputNeurons;
		std::vector<vyn::neuralnetwork::Neuron *>	outputNeurons;
		
		inputNeurons = inputLayer.GetNeurons();
		outputNeurons = outputLayer.GetNeurons();
		for (int i = 0; i < inputNeurons.size(); ++i)
		{
			inputNeurons[i]->SetValue(0.5);
			for (int j = 0; j < inputNeurons[i]->GetOutputConnections().size(); ++j)
			{
				inputNeurons[i]->GetOutputConnections()[j]->SetWeight(0.5);
			}
		}
		outputLayer.ComputeValues();
		for (int i = 0; i < outputNeurons.size(); ++i)
		{
			REQUIRE(outputNeurons[i]->GetRawValue() == 0.5 * 0.5 + 0.5 * 0.5 + 0.5 * 0.5);
			REQUIRE(outputNeurons[i]->GetValue() == vyn::neuralnetwork::Sigmoid(outputNeurons[i], outputNeurons[i]->GetRawValue()));
		}
		vyn::neuralnetwork::values_t	outputValues = outputLayer.GetValues();
		for (int i = 0; i < outputNeurons.size(); ++i)
		{
			REQUIRE(outputValues[i] == (1 / (1 + exp(-(0.5 * 0.5 + 0.5 * 0.5 + 0.5 * 0.5))))); // <- Sigmoid
		}
	}
	
	TEST_EXIT(TEST_SUCCESS);
}