#include "ability.h"
#include "pokemon.h"

Ability::Ability(string name, void(*effect)(Pokemon&, Pokemon&))
{
	m_name = name;
	m_effect = effect;
	// armor tail, if priority block move
}

string Ability::getName()
{
	return m_name;
}

void Ability::useAbility(Pokemon& user, Pokemon& target)
{
	if (m_effect != nullptr) {
		m_effect(user, target);
	}
}

Ability abilityList[] = {
	Ability("Tough Claws"),
	Ability("Defiant",
		[](Pokemon& user, Pokemon& target) {
		for (size_t i = 0; i < 5; i++)
		{
			
		}

		})
};

// Automatically calculates the number of elements: (Total bytes / Size of one element)
const size_t abilityListSize = sizeof(abilityList) / sizeof(abilityList[0]);
