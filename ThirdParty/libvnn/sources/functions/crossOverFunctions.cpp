/*
* @Author: Vyn
* @Date:   2019-04-05 11:47:29
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-07 14:20:30
*/

/*
* @Author: Vyn
* @Date:   2019-03-03 14:49:12
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-05 11:29:48
*/

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Network.h"
#include "Neuron.h"
#include "Population.h"
#include "types.h"
#include "utils.h"

namespace vyn
{
	namespace neuralnetwork
	{
		Person		*GenerateChild(Population *population, Person *person1, Person *person2)
		{
			Person					*child;
			std::vector<Connection *>	childConnections;
			std::vector<Connection *>	person1Connections;
			std::vector<Connection *>	person2Connections;

			child = population->GenerateNewPerson();
			childConnections = child->GetNetwork()->GetConnections();
			person1Connections = person1->GetNetwork()->GetConnections();
			person2Connections = person2->GetNetwork()->GetConnections();
			for (int i = 0; i < childConnections.size(); ++i)
			{
				//if (i < childConnections.size() / 2)
				if (rand() % 2 == 0)
					childConnections[i]->SetWeight(person1Connections[i]->GetWeight());
				else
					childConnections[i]->SetWeight(person2Connections[i]->GetWeight());
				if ((value_t)rand() / (value_t)RAND_MAX < population->GetMutationChance())
					childConnections[i]->SetWeight(childConnections[i]->GetInput()->GetParentLayer()->NewWeightValue());
			}
			return (child);
		}

		void		DefaultCrossOverFunction(Population *population)
		{
			int	populationSize = population->GetSize();
			for (int i = 0; i < populationSize; ++i)
			{
				for (int j = 0; j < populationSize; ++j)
				{
					Person	*child;

					if (i != j)
					{
						child = GenerateChild(population, population->GetPersons()[i], population->GetPersons()[j]);
						population->AddPerson(child);
					}
				}
			}
		}
	}
}