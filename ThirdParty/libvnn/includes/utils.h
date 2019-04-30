#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

#include "Network.h"
#include "Layer.h"
#include "Connection.h"
#include "types.h"

namespace vyn
{
	namespace neuralnetwork
	{
		Network		*Load(std::string fileName);

		namespace scale
		{
			typedef struct				ScaleData_s
			{
				value_t		min;
				value_t		max;
				value_t		mean;
			} 							ScaleData_t;
			std::vector<ScaleData_t>	MinMax(std::vector<std::vector<value_t>> &inputs);
			std::vector<ScaleData_t>	MinMax(std::vector<std::vector<value_t>> &inputs, std::vector<ScaleData_t> &scaleDatas);
			std::vector<ScaleData_t>	MeanNormalisation(std::vector<std::vector<value_t>> &inputs);
			std::vector<ScaleData_t>	MeanNormalisation(std::vector<std::vector<value_t>> &inputs, std::vector<ScaleData_t> &scaleDatas);
		}

		namespace debug
		{
			void	CheckValue(value_t value, std::string msg);
		}
	}
}

#endif