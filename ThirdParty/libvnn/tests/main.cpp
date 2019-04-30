/*
* @Author: Vyn
* @Date:   2019-04-18 15:01:42
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-19 14:15:50
*/

#include <iostream>

#include "vtest/vtest.hpp"
#include "../includes/NeuralNetwork.h"

TEST_REGISTER(NEURON);
TEST_REGISTER(CONNECTION);
TEST_REGISTER(LAYER);
TEST_REGISTER(NETWORK);

int		main(void)
{
	try
	{
		TEST_EXECUTE(CONNECTION);
		TEST_EXECUTE(NEURON);
		TEST_EXECUTE(LAYER);
		TEST_EXECUTE(NETWORK);
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}
	return (0);
}