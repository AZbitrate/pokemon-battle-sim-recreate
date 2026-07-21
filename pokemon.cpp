#include "pokemon.h"
//#include "typeInfo.h"
#include <iostream>
#include <random>
#include <chrono>
Pokemon::Pokemon(string type1, string type2, string name,
	string species, string abilityName, int hp,
	int atk, int def, int spAtk,
	int spDef, int speed)
	: m_name(name), m_species(species)
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

	m_type1 = stringToType(type1);
	m_type2 = stringToType(type2);

	for (size_t i = 0; i < abilityListSize; i++)
	{
		if (abilityList[i].getName() == abilityName) {
			m_ability = &abilityList[i];
			break;
		}
	}
}

Ability* Pokemon::getAbility() const
{
	return m_ability;
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

		int roll = randomGenerator(1, 100);

		if (roll > moveset[slot]->getAccuracy()) // move missed, not miss is under accuracy number
		{
			std::cout << m_name << "'s attack missed!\n";
			lastMoveUsed = moveset[slot]; // It counts as the last used move even if it misses!
			return; // Stop execution here so no damage or status effects happen
		}
	}
	lastMoveUsed = moveset[slot];

	if (activeMove->getTarget() == "self") {
		if (moveset[slot] != nullptr) {
			moveset[slot]->use(*this, target); // 'this' passes a reference to the user
		}
	}
	else
	{
		// for partner or anyone else
		int critChance = 0;
		if (critStage == 0)
		{
			critChance = randomGenerator(1, 24);
			if (critChance == 24)
			{
				crit = true;
			}
		}

		int damage = target.takeDmg(*this, activeMove);
		if (moveset[slot] != nullptr) {
			moveset[slot]->use(*this, target, damage); // for extra effects after damage is calcuated
		}

		crit = false; // reset for next move
	}

}

int Pokemon::takeDmg(Pokemon& attacker, Move* moveUsed)
{
	int damage = 1;

	if (this->lastMoveUsed != nullptr)
	{
		if (this->lastMoveUsed->getName() == "Protect" && (moveUsed->getTarget() != "partner" && moveUsed->getCategory() != "Status"))
		{
			cout << this->m_name << " protected itself!" << endl;
			return 0;
		}
	}

	m_ability->useAbility(*this, attacker, moveUsed, &damage); // for armor tail

	if (damage == 0)
	{
		return damage; // no damage calc run
	}

	if (moveUsed->getCategory() == "Status")
	{
		return 0;
	}

	float typeMult = getEffectiveness(moveUsed->getType(), this->m_type1);

	typeMult *= getEffectiveness(moveUsed->getType(), this->m_type2); // factor in 2 types

	float random = randomGenerator(85, 100);

	random = random / 100; // to turn it into a range of 0.85 - 1 cause 100 mutiplying it all is crazy
	// roll is for random damage, sometimes damage gets nerfed

	// lvl is 50 because doubles vgc format
	// damage = (((2 * lvl / 5) + 2) * PowerOfMove * (attackers attack / defenders defense)) / 50 + 2
	// then * targets (ig if it recives the spread nerf of 0.75) * stab * crit * random (85 - 100 / 100 aka 0.85 - 1.0) (moves sometimes do strong or weak hits)
	// then * burn (0.5 debuff if physical)
	damage = 0; // incase ability above changed it
	int power = moveUsed->getPower();
	int attack = 0;
	int defense = 0;
	double target = 1;
	double stab = 1;
	double type = 1;
	int burnReduce = 1; // 1 is no reduce


	if (moveUsed->getTarget() == "everyone" || moveUsed->getTarget() == "both opponents")
	{
		target = 0.75; //spread nerf, no single target (self, partner or 1 target) no nerf
	}

	if (moveUsed->getType() == attacker.m_type1 || moveUsed->getType() == attacker.m_type2)
	{
		stab = 1.5;
	}

	if (moveUsed->getCategory() == "Physical")
	{
		attack = attacker.getStat("atk");
		defense = attacker.getStat("def");
		if (isBurned)
		{
			burnReduce = 0.5;
		}
	}
	else if (moveUsed->getCategory() == "Special")
	{
		attack = attacker.getStat("spAtk");
		defense = attacker.getStat("spDef");
	}

	m_ability->useAbility(attacker, *this, moveUsed, &power); // for any ability that buffs power

	damage = ((22.0 * power * (static_cast<double>(attack) / defense)) / 50 + 2.0) * target * stab * burnReduce * random * typeMult;

	if (crit)
	{
		damage *= 1.5;
	}

	m_ability->useAbility(attacker, *this, moveUsed, &power, &damage); // for any ability that nerfs damage

	this->m_hp -= damage;

	return damage;

}

string Pokemon::getName() const
{
	return m_name;
}

int Pokemon::getHp() const
{
	return m_hp;
}

int Pokemon::getMaxHp() const
{
	return maxHp;
}

int Pokemon::updateHP(int value)
{
	m_hp += value; // Add the value exactly ONCE

	if (m_hp > maxHp)
	{
		m_hp = maxHp;
	}
	else if (m_hp < 0)
	{
		m_hp = 0;
	}

	return m_hp;
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

int Pokemon::checkStage(int stat, int stage) const
{

	if (stage >= 0) { // also applies to crit
		return stat * (2 + stage) / 2;
	}
	else if (stage < 0 && !crit) {
		return stat * 2 / (2 - stage);
	}
	else
	{
		return stat; // if crit and below 0 stage
	}

	// if no ifs entered
	return stat;
}

void Pokemon::modifyStat(string stat, int amount)
{
	int statVal;
	int index{};

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

	return;
}

int Pokemon::getStatStage(int index) const
{
	return m_statStages[index];
}

int Pokemon::getLastStatStage(int index) const
{
	return lastStatStage[index];
}

void Pokemon::setLastStatStage(int index)
{
	lastStatStage[index] = m_statStages[index];
}

int Pokemon::randomGenerator(int lowRange, int highRange)
{
	// 1. Get the system time in nanoseconds (one billionth of a second!)
	auto nanoSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	// 2. Feed that massive, hyper-precise number into a modern random engine
	static std::mt19937 generator(static_cast<unsigned int>(nanoSeed));

	std::uniform_int_distribution<int> distribution(lowRange, highRange);

	int random = distribution(generator);

	return random;
}

