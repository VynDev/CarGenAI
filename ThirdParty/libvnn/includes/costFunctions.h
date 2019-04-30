#ifndef COSTFUNCTIONS_H
#define COSTFUNCTIONS_H

#define COST_FUNCTION_MSE 1
#define COST_FUNCTION_CE 2

#include <vector>
#include "types.h"

vyn::neuralnetwork::value_t	SquaredError(std::vector<vyn::neuralnetwork::Neuron *> outputNeurons, std::vector<vyn::neuralnetwork::value_t> expectedOutput);
vyn::neuralnetwork::value_t	SquaredErrorDerivative(std::vector<vyn::neuralnetwork::Neuron *> outputNeurons, std::vector<vyn::neuralnetwork::value_t> expectedOutput, vyn::neuralnetwork::Neuron *outputNeuron);

vyn::neuralnetwork::value_t	CrossEntropy(std::vector<vyn::neuralnetwork::Neuron *> outputNeurons, std::vector<vyn::neuralnetwork::value_t> expectedOutput);
vyn::neuralnetwork::value_t	CrossEntropyDerivative(std::vector<vyn::neuralnetwork::Neuron *> outputNeurons, std::vector<vyn::neuralnetwork::value_t> expectedOutput, vyn::neuralnetwork::Neuron *outputNeuron);

#endif