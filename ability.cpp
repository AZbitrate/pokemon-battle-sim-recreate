#include "ability.h"
#include "pokemon.h"

Ability::Ability(string name, void(*effect)(Pokemon&, Pokemon&))
{
	m_name = name;
	m_effect = effect;
	// armor tail, if priority block move
}
