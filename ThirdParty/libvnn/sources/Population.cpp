/*
* @Author: Vyn
* @Date:   2019-04-02 16:44:28
* @Last Modified by:   Vyn
* @Last Modified time: 2019-04-07 14:23:55
*/

#include "Population.h"
#include "Neuron.h"
#include "Network.h"

namespace vyn
{
	namespace neuralnetwork
	{
		Population::Population(Network *(*f)() , int numberOfPerson)
		{
			networkCreationFunction = f;
			for (int i = 0; i < numberOfPerson; ++i)
			{
				AddPerson(GenerateNewPerson());
			}
		}

		void		Population::SetCrossOverFunction(int functionId)
		{
			if (functionId == CROSSOVER_FUNCTION_DEFAULT)
				SetCrossOverFunction(&DefaultCrossOverFunction);
		}

		void		Population::AddPerson(Person *person)
		{
			population.push_back(person);
		}

		Person		*Population::GenerateNewPerson()
		{
			Person *person;

			person = new Person;
			person->SetNetwork((*networkCreationFunction)());
			person->SetScore(0);
			person->SetId(nextId);
			person->SetPopulation(this);
			++nextId;
			return (person);
		}	

		void		Population::CrossOver()
		{
			DeleteUnselectedPersons();
			(*crossOverFunction)(this);
			++currentGenerationId;
		}

		void		Population::DeleteUnselectedPersons()
		{
			for (int i = 0; i < population.size(); ++i)
			{
				if (population[i]->IsSelected()  == false)
				{
					delete population[i];
					population.erase(population.begin() + i);
					--i;
				}
				else
					population[i]->Unselect();
			}
		}
	}
}