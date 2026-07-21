#pragma once
#include "ability.h"
#include "pokemon.h"
#include <iostream>
using std::cout;

Ability::Ability(string name, void(*effect)(Pokemon&, Pokemon&, Move* move, int* power, int* dmg))
{
	m_name = name;
	m_effect = effect;
	// armor tail, if priority block move
}

string Ability::getName()
{
	return m_name;
}

void Ability::useAbility(Pokemon& user, Pokemon& target, Move* moveUsed, int* power, int* dmg)
{
	if (m_effect != nullptr) {
		m_effect(user, target, moveUsed, power, dmg);
	}
}

