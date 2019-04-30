/*
* @Author: Vyn
* @Date:   2019-03-13 12:53:26
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-07 14:21:00
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include "utils.h"

namespace vyn
{
	namespace neuralnetwork
	{
		Network		*Load(std::string fileName)
		{
			Network							*network;
			Layer							*layer;
			std::vector<Connection *>	connections;

			std::ifstream 					file;
			std::string						line;
			std::stringstream				lineStream;
			std::string						elem;
			int								nbLayers;

			network = new Network;
			file.open(fileName);
			getline(file, line);
			std::cout << "Checking string: " << line << std::endl;
			if (line != VYN_NEURALNETWORK_STRING)
				throw std::string("String does not match");
			getline(file, line);
			std::cout << "Checking version: " << line << std::endl;
			if (line != VYN_NEURALNETWORK_VERSION)
				throw std::string("Version does not match");
			getline(file, line);
			std::cout << "Getting number of layers: " << line << std::endl;
			nbLayers = std::stoi(line);
			for (int i = 0; i < nbLayers; ++i)
			{
				getline(file, line);
				lineStream = std::stringstream(line);
				std::cout << "Creating new layer" << std::endl;
				layer = new Layer(0, 0, 0);
				while (getline(lineStream, elem, ' '))
				{
					std::cout << "Adding neuron with function ID: " << elem << std::endl;
					layer->AddNeuron(std::stoi(elem));
				}
				network->AddLayer(layer);
			}
			std::cout << "Loading cost function" << std::endl;
			getline(file, line);
			network->SetCostFunction(std::stoi(line));
			getline(file, line);
			lineStream = std::stringstream(line);
			connections = network->GetConnections();
			int	i = 0;
			std::cout << "Loading weights" << std::endl;
			while (getline(lineStream, elem, ' '))
			{
				connections[i]->SetWeight(std::stod(elem));
				++i;
			}
			if (i != connections.size())
				throw std::string("The model is corrupted ?");
			std::cout << "Network fully loaded" << std::endl;
			return (network);
		}

		namespace scale
	{

		value_t GetMean(std::vector<std::vector<value_t>> &inputs, int i)
		{
			value_t	total;

			total = 0;
			for (int j = 0; j < inputs.size(); ++j)
			{
				total += inputs[j][i];
			}
			return (total / inputs.size());
		}

		value_t GetMin(std::vector<std::vector<value_t>> &inputs, int i)
		{
			value_t	min;

			min = inputs[0][i];
			for (int j = 0; j < inputs.size(); ++j)
			{
				if (inputs[j][i] < min)
					min = inputs[j][i];
			}
			return (min);
		}

		value_t	GetMax(std::vector<std::vector<value_t>> &inputs, int i)
		{
			value_t	max;

			max = inputs[0][i];
			for (int j = 0; j < inputs.size(); ++j)
			{
				if (inputs[j][i] > max)
					max = inputs[j][i];
			}
			return (max);
		}

		std::vector<ScaleData_t> MinMax(std::vector<std::vector<value_t>> &inputs)
		{
			std::vector<ScaleData_t>	scaleDatas;
			std::vector<value_t>		firstLine;

			firstLine = inputs[0];
			for (int i = 0; i < firstLine.size(); ++i)
			{
				ScaleData_t		scaleData;
				scaleData.min = GetMin(inputs, i);
				scaleData.max = GetMax(inputs, i);
				for (int j = 0; j < inputs.size(); ++j)
				{
					inputs[j][i] = (inputs[j][i] - scaleData.min) / (scaleData.max - scaleData.min);
				}
				scaleDatas.push_back(scaleData);
			}
			return (scaleDatas);
		}

		std::vector<ScaleData_t> MinMax(std::vector<std::vector<value_t>> &inputs, std::vector<ScaleData_t> &scaleDatas)
		{
			std::vector<value_t>		firstLine;

			firstLine = inputs[0];
			for (int i = 0; i < firstLine.size(); ++i)
			{
				for (int j = 0; j < inputs.size(); ++j)
				{
					inputs[j][i] = (inputs[j][i] - scaleDatas[i].min) / (scaleDatas[i].max - scaleDatas[i].min);
				}
			}
			return (scaleDatas);
		}

		std::vector<ScaleData_t> MeanNormalisation(std::vector<std::vector<value_t>> &inputs)
		{
			std::vector<ScaleData_t>	scaleDatas;
			std::vector<value_t>		firstLine;

			firstLine = inputs[0];
			for (int i = 0; i < firstLine.size(); ++i)
			{
				ScaleData_t		scaleData;
				scaleData.mean = GetMean(inputs, i);
				scaleData.min = GetMin(inputs, i);
				scaleData.max = GetMax(inputs, i);
				for (int j = 0; j < inputs.size(); ++j)
				{
					inputs[j][i] = (inputs[j][i] - scaleData.mean) / (scaleData.max - scaleData.min);
				}
				scaleDatas.push_back(scaleData);
			}
			return (scaleDatas);
		}

		std::vector<ScaleData_t> MeanNormalisation(std::vector<std::vector<value_t>> &inputs, std::vector<ScaleData_t> &scaleDatas)
		{
			std::vector<value_t>		firstLine;

			firstLine = inputs[0];
			for (int i = 0; i < firstLine.size(); ++i)
			{
				for (int j = 0; j < inputs.size(); ++j)
				{
					inputs[j][i] = (inputs[j][i] - scaleDatas[i].mean) / (scaleDatas[i].max - scaleDatas[i].min);
				}
			}
			return (scaleDatas);
		}
	}
	}
}