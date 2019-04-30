/*
* @Author: Vyn
* @Date:   2019-03-16 18:09:48
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-07 14:19:46
*/

#include "utils.h"

namespace vyn
{
	namespace neuralnetwork
	{
		namespace debug
		{
			void	CheckValue(value_t value, std::string msg)
			{
				if (std::isnan(value) || std::isinf(value))
				{
					std::cout << "[DEBUG] " << msg << ": " << value;
					throw msg + std::string(": ") + std::to_string(value);
				}
			};
		}
	}
}