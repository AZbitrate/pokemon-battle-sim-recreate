#include "pokemon.h"
#include <iostream>
#include <random>
#include <chrono>
Pokemon::Pokemon(string type1, string type2, string name,
	string species, string abilityName, int hp,
	int atk, int def, int spAtk,
	int spDef, int speed)
	: m_type1(type1), m_type2(type2),
	m_name(name), m_species(species)
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
	if (moveset[slot] == nullptr) return; // Basic safety filter for turn 1

	Move* activeMove = moveset[slot];

	if (lastMoveUsed != nullptr && activeMove->getName() == lastMoveUsed->getName() && activeMove->getName() == "Gigaton Hammer")
	{
		std::cout << "Gigaton Hammer can't be used twice in a row!";
		return;
	}

	std::cout << m_name << " used " << activeMove->getName() << "!\n";

	// roll range of numbers for accuracy

	if (activeMove->getAccuracy() < 100)
	{
		// 1. Get the system time in nanoseconds (one billionth of a second!)
		auto nanoSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

		// 2. Feed that massive, hyper-precise number into a modern random engine
		std::mt19937 generator(static_cast<unsigned int>(nanoSeed));

		// 3. Define your range (0 to 99 for your accuracy check)
		std::uniform_int_distribution<int> distribution(1, 100);

		int roll = distribution(generator);

		if (roll > moveset[slot]->getAccuracy()) // move missed, not miss is under accuracy number
		{
			std::cout << m_name << "'s attack missed!\n";
			lastMoveUsed = moveset[slot]; // It counts as the last used move even if it misses!
			return; // Stop execution here so no damage or status effects happen
		}
	}

	if (activeMove->getTarget() == "self") {
		if (moveset[slot] != nullptr) {
			moveset[slot]->use(*this, target); // 'this' passes a reference to the user
		}
	}
	else
	{
		// call get hit function (not created)
		// for partner or anyone else
		target.takeDmg(*this, activeMove);
	}

	lastMoveUsed = moveset[slot];

	//
}

void Pokemon::takeDmg(Pokemon& attacker, Move* moveUsed)
{
	if (this->lastMoveUsed->getName() == "Protect")
	{
		cout << this->m_name << " protected itself!" << endl;
		return;
	}

	if (this->m_ability->getName() == "Armor Tail" || this->m_ability->getName() == "Queenly Majesty" &&
		(moveUsed->getPriority() > 0 || (attacker.m_ability->getName() == "Pranster" && moveUsed->getCategory() == "Status")))
	{
		cout << "Armor Tail blocked " << moveUsed->getName() << " from working!" << endl;
		return; // no damage calc run
	}

	// lvl is 50 because doubles vgc format
	// damage = (((2 * lvl / 5) + 2) * PowerOfMove * (attackers attack / defenders defense)) / 50 + 2
	// then * targets (ig if it recives the spread nerf of 0.75) * stab * crit * random (85 - 100 / 100 aka 0.85 - 1.0) (moves sometimes do strong or weak hits)
	// then * burn (0.5 debuff if physical)
	int damage = 0;
	int attack = 0;
	int defense = 0;
	int target = 1;
	double stab = 1;
	double type = 1;
	if (moveUsed->getTarget() == "everyone" || moveUsed->getTarget() == "both opponents")
	{
		target = 0.75;
	}

	if (moveUsed->getType() == attacker.m_type1 || moveUsed->getType() == attacker.m_type2)
	{
		stab = 1.5;
	}

	if (moveUsed->getCategory() == "Physical")
	{
		attack = attacker.getStat("atk");
		defense = attacker.getStat("def");
	}
	else if (moveUsed->getCategory() == "Specail")
	{
		attack = attacker.getStat("spAtk");
		defense = attacker.getStat("spDef");
	}

	damage = ((22.0 * moveUsed->getPower() * (static_cast<double>(attack) / defense)) / 50 + 2.0) * target * stab;

	this->m_hp -= damage;

}

int Pokemon::getHp() const
{
	return m_hp;
}

int Pokemon::getMaxHp() const
{
	return maxHp;
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
