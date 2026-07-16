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
