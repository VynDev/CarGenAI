/*
* @Author: Vyn
* @Date:   2019-03-04 14:44:05
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-05 14:19:01
*/

#include <cmath>
#include <string>
#include <iostream>
#include <float.h>

#include "Network.h"
#include "types.h"
#include "Neuron.h"
#include "Connection.h"

using namespace vyn::neuralnetwork;

value_t	SquaredError(std::vector<Neuron *> outputNeurons, std::vector<value_t> expectedOutput)
{
	value_t		total;

	total = 0;
	for (std::vector<value_t>::size_type i = 0; i < outputNeurons.size(); ++i)
	{
		total += std::pow(outputNeurons[i]->GetValue() - expectedOutput[i], 2) / 2;
	}
	return (total);
}

value_t	SquaredErrorDerivative(std::vector<Neuron *> outputNeurons, std::vector<value_t> expectedOutput, Neuron *outputNeuron)
{
	for (std::vector<value_t>::size_type i = 0; i < outputNeurons.size(); ++i)
	{
		if (outputNeuron->GetId() == outputNeurons[i]->GetId())
			return (outputNeurons[i]->GetValue() - expectedOutput[i]);
	}
	throw std::string("Can't derivate cost function with respect to neuron");
}
/*
value_t	CrossEntropy(std::vector<Neuron *> outputNeurons, std::vector<value_t> expectedOutput)
{
	value_t		total;

	total = 0;
	for (std::vector<value_t>::size_type i = 0; i < outputNeurons.size(); ++i)
	{
		DEBUG_CHECK_VALUE(outputNeurons[i]->GetValue(), "Neuron ouputs");
		if ((expectedOutput[i] == 0 && outputNeurons[i]->GetValue() < DBL_MIN) || (expectedOutput[i] == 1 && 1 - outputNeurons[i]->GetValue() < DBL_MIN))
			total += 0;
		else if ((expectedOutput[i] == 0 && 1 - outputNeurons[i]->GetValue() < DBL_MIN) || (expectedOutput[i] == 1 && outputNeurons[i]->GetValue() < DBL_MIN))
			total += -log(DBL_MIN);
		else
		{
			value_t	currentValue;

			currentValue = -(expectedOutput[i] * log(outputNeurons[i]->GetValue()) + (1 - expectedOutput[i]) * log(1 - outputNeurons[i]->GetValue()));
			DEBUG_CHECK_VALUE(currentValue, "Current value (loop)");
			total += currentValue;
			DEBUG_CHECK_VALUE(total, "Total error (loop)");
		}
	}
	DEBUG_CHECK_VALUE(total, "Total error");
	return (total);
}

value_t	CrossEntropyDerivative(std::vector<Neuron *> outputNeurons, std::vector<value_t> expectedOutput, Neuron *outputNeuron)
{
	value_t		result;
	value_t		leftResult;
	value_t		rightResult;

	for (std::vector<value_t>::size_type i = 0; i < outputNeurons.size(); ++i)
	{
		if (outputNeuron->GetId() == outputNeurons[i]->GetId())
		{
			DEBUG_CHECK_VALUE(expectedOutput[i], "Expected output");
			DEBUG_CHECK_VALUE(outputNeuron->GetValue(), "Neuron output");
			if ((expectedOutput[i] == 0 && outputNeuron->GetValue() < DBL_MIN) || (expectedOutput[i] == 1 && 1 - outputNeuron->GetValue() < DBL_MIN))
				return (0);
	
			leftResult = (outputNeuron->GetValue() < DBL_MIN ? expectedOutput[i] / DBL_MIN : expectedOutput[i] / outputNeuron->GetValue());
			rightResult = (1 - outputNeuron->GetValue() < DBL_MIN ? (1 - expectedOutput[i]) / DBL_MIN : (1 - expectedOutput[i]) / (1 - outputNeuron->GetValue()));
			DEBUG_CHECK_VALUE(leftResult, "leftResult");
			DEBUG_CHECK_VALUE(rightResult, "rightResult");
			result = -leftResult + rightResult;
			//result = result < 0 ? result + 1 : result - 1;
			//DEBUG_CHECK_VALUE(result, "Derivative of cost function result error. Expected neuron output: " + std::to_string(expectedOutput[i]) + ", neuron ouput: " + std::to_string(outputNeuron->GetValue()));
			DEBUG_CHECK_VALUE(result, "Derivative of cost function result error");
			//std::cout << "cost derivative: " << result << std::endl;
			if (result > 10)
				return (10);
			if (result < -10)
				return (-10);
			return (result);
		}
	}
	throw std::string("Can't derivate cost function with respect to neuron");
}*/

value_t	CrossEntropy(std::vector<Neuron *> outputNeurons, std::vector<value_t> expectedOutput)
{
	value_t		total;

	total = 0;
	for (std::vector<value_t>::size_type i = 0; i < outputNeurons.size(); ++i)
	{
		DEBUG_CHECK_VALUE(outputNeurons[i]->GetValue(), "Neuron ouputs");

		if (expectedOutput[i] == 1)
		{
			if (outputNeurons[i]->GetValue() != 0)
				total += -log(outputNeurons[i]->GetValue());
			else
				total += -log(DBL_MIN);
		}
		else if (expectedOutput[i] == 0)
		{
			if (outputNeurons[i]->GetValue() != 1)
				total += -log(1 - outputNeurons[i]->GetValue());
			else
				total += -log(DBL_MIN);
		}
	}
	DEBUG_CHECK_VALUE(total, "Total error");
	return (total);
}

value_t	CrossEntropyDerivative(std::vector<Neuron *> outputNeurons, std::vector<value_t> expectedOutput, Neuron *outputNeuron)
{
	value_t		result;
	value_t		leftResult;
	value_t		rightResult;

	for (std::vector<value_t>::size_type i = 0; i < outputNeurons.size(); ++i)
	{
		if (outputNeuron->GetId() == outputNeurons[i]->GetId())
		{
			DEBUG_CHECK_VALUE(expectedOutput[i], "Expected output");
			DEBUG_CHECK_VALUE(outputNeuron->GetValue(), "Neuron output");
			if (expectedOutput[i] == 1)
			{
				result = -(1 / outputNeuron->GetValue() - 1);
				//if (result < -10)
					//return (-10);
				return (result);
			}
			else if (expectedOutput[i] == 0)
			{
				result = -(-1 / (1 - outputNeuron->GetValue()) + 1);
				//if (result > 10)
					//return (10);
				return (result);
			}
		}
	}
	throw std::string("Can't derivate cost function with respect to neuron");
}