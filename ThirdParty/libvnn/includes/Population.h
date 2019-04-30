#ifndef POPULATION_H
#define POPULATION_H

#include "Network.h"
#include "crossOverFunctions.h"
#include "types.h"

namespace vyn
{
	namespace neuralnetwork
	{
		class Population;

		class Person
		{

		private:

			Network		*network = nullptr;
			bool		isSelected = false;
			int			score = 0;
			int			previousScore = 0;
			int			generationId;
			int			id;
			Population	*population = nullptr;
			void		*customData = nullptr;

		public:

			void		SetNetwork(Network *newNetwork) {network = newNetwork;};
			Network		*GetNetwork() {return (network);};

			void		SetScore(int newScore) {previousScore = score; score = newScore;};
			int			GetScore() const {return (score);};
			int			GetPreviousScore() const {return (previousScore);};

			void		SetGenerationId(int newId) {generationId = newId;};
			int			GetGenerationId() const {return (generationId);};

			void		SetId(int newId) {id = newId;};
			int			GetId() const {return (id);};

			void		SetPopulation(Population *newPopulation) {population = newPopulation;};
			Population	*GetPopulation() {return (population);};

			void		Select() {isSelected = true;};
			void		Unselect() {isSelected = false;};
			bool		IsSelected() const {return (isSelected);};

			void		SetCustomData(void *ptr) {customData = ptr;};
			void		*GetCustomData() {return (customData);};
		};

		class Population {

		private:

			std::vector<Person *>	population;

			int			nextId = 0;
			int			currentGenerationId = 1;
			value_t		mutationChance = 0.05;

			Network		*(*networkCreationFunction)();
			void		(*crossOverFunction)(Population *) = &DefaultCrossOverFunction;

		public:

			Population(Network *(*f)(), int numberOfPerson);

			std::vector<Person *>	&GetPersons() {return (population);};
			int						GetSize() const {return (population.size());};
			int						GetCurrentGenerationId() const {return (currentGenerationId);};

			void					SetMutationChance(value_t value) {mutationChance = value;};
			value_t					GetMutationChance() const {return (mutationChance);};

			void					AddPerson(Person *person);
			Person					*GenerateNewPerson();

			void					SetCrossOverFunction(int functionId);
			void					SetCrossOverFunction(void (*f)(Population *)) {crossOverFunction = f;};
			void					CrossOver();

			void					DeleteUnselectedPersons();
		};
	}
}
#endif