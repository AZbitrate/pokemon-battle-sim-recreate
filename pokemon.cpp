#include "pokemon.h"
#include <iostream>

Pokemon::Pokemon(string type1, string type2, string name,
				string species, string ability, int hp, 
				int atk, int def, int spAtk, 
				int spDef, int speed)
			: m_type1(type1), m_type2(type2),
			m_name(name), m_species(species),
			m_ability(ability) 
{
	maxHp = hp;
	m_hp = hp;
	m_attack = atk;
	m_defense = def;
	m_specialAttack = spAtk;
	m_specialDefense = spDef;
	m_speed = speed;

	isBurned = false;
	isParaysis = false;
	isPoison = false;
	isFrozen = false;
}

void Pokemon::performMove(int slot, Pokemon& target)
{
	if (moveset[slot]->getName() == lastMoveUsed->getName() && moveset[slot]->getName() == "Gigaton Hammer")
	{
		std::cout << "Gigaton Hammer can't be used twice in a row!";
	}

	if (moveset[slot] != nullptr) {
		moveset[slot]->use(*this, target); // 'this' passes a reference to the user
	}

	lastMoveUsed = moveset[slot];
}

int Pokemon::getStat(string stat)
{

	int statVal = 0;
	int stageVal = 0;
	int index = 0;

	if (stat == "atk")
	{
		statVal = m_attack;
		index = 0;
		//stageVal = atkStage;
	}

	if (stat == "spAtk")
	{
		statVal = m_specialAttack;
		index = 1;
		//stageVal = spAtkStage;
	}

	if (stat == "def")
	{
		statVal = m_defense;
		index = 2;
		//stageVal = defStage;
	}

	if (stat == "spDef")
	{
		statVal = m_specialDefense;
		index = 3;
		//stageVal = spDefStage;
	}

	if (stat == "speed")
	{
		statVal = m_speed;
		index = 4;
		//stageVal = speedStage;
	}

	stageVal = m_statStages[index];

	statVal = checkStage(statVal, stageVal);

	return statVal;
}

int Pokemon::checkStage(int stat, int stage)
{

	if (stage >= 0) {
		return stat * (2 + stage) / 2;
	}
	else {
		return stat * 2 / (2 - stage);
	}

	// if no ifs entered
	return stat;
}

int Pokemon::modifyStat(string stat, int amount)
{
	int statVal;
	int index;

	if (stat == "atk")
	{
		statVal = m_attack;
		index = 0;
		//stageVal = atkStage;
	}

	if (stat == "spAtk")
	{
		statVal = m_specialAttack;
		index = 1;
		//stageVal = spAtkStage;
	}

	if (stat == "def")
	{
		statVal = m_defense;
		index = 2;
		//stageVal = defStage;
	}

	if (stat == "spDef")
	{
		statVal = m_specialDefense;
		index = 3;
		//stageVal = spDefStage;
	}

	if (stat == "speed")
	{
		statVal = m_speed;
		index = 4;
		//stageVal = speedStage;
	}

	m_statStages[index] += amount;
	if (m_statStages[index] > 6)  m_statStages[index] = 6;
	if (m_statStages[index] < -6) m_statStages[index] = -6;

	return 0;
}

string Pokemon::getName() const
{
	return m_name;
}
