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

	m_type1 = stringToType(type1);
	m_type2 = stringToType(type2);

	for (size_t i = 0; i < abilityListSize; i++)
	{
		if (abilityList[i].getName() == abilityName) {
			m_ability = &abilityList[i];
			break;
		}
		else
		{
			m_ability = nullptr;
		}
	}
}

Pokemon::~Pokemon()
{
	deleteItem();

	for (size_t i = 0; i < 4; i++)
	{
		delete moveset[i];
		moveset[i] = nullptr;
	}
}

void Pokemon::setAbility(const string& abilityName)
{
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

void Pokemon::setStatus(Status stat)
{
	if (m_status != Status::none)
	{
		return;
	}

	m_status = stat;
	statusTurn = 1;
	
}

Status Pokemon::getStatus() const {

	return m_status;
}

void Pokemon::cureStatus()
{
	m_status = Status::none;
}

Type Pokemon::getType(int type)
{
	if (type == 1)
	{
		return m_type1;
	}
	else
	{
		return m_type2;
	}

	return m_type1;
}

int Pokemon::performMove(int slot, Pokemon& target)
{
	//return 2 of move is skipped
	// return 0 when move missed
	//return 1 if move not missed
	//return -1 if move is unable to be used (gigaton hammer turn 2)
	if (moveset[slot] == nullptr) return 0; // Basic safety filter for turn 1

	Move* activeMove = moveset[slot];

	if (lastMoveUsed != nullptr && activeMove->getName() == lastMoveUsed->getName() && activeMove->getName() == "Gigaton Hammer")
	{
		std::cout << "Gigaton Hammer can't be used twice in a row!";
		return -1;
	}

	if (m_status == Status::sleep)
	{
		if (statusTurn == 1) {
			cout << m_name << " is fast asleep" << endl;
			statusTurn = 2;
			return 2;
		}
		else if (statusTurn == 2)
		{
			int wakeUp = randomGenerator(1, 3); // pokemon champions is 1 in 3 chance to wake up turn 2
			if (wakeUp == 3)
			{
				statusTurn = 0;
				m_status = Status::none;
				cout << m_name << " woke up!" << endl;
			}
			else
			{
				cout << m_name << " is fast asleep" << endl;
				statusTurn = 3;
				return 2;
			}
		}
		else // if 2 turns pass it wake up turn 3
		{
			statusTurn = 0;
			m_status = Status::none;
			cout << m_name << " woke up!" << endl;
		}
	}

	if (m_status == Status::paralysis)
	{
		int paralysisRNG = randomGenerator(1, 8); // pokemon champions is 1 in 8 chance to not move
		if (paralysisRNG == 8)
		{
			cout << m_name << " is paralyzed! it's unable to move!" << endl;
			return 2;
		}
	}

	if (m_status == Status::frozen)
	{
		if (statusTurn < 3) {
			int thawChance = randomGenerator(1, 4); // pokemon champions is 1 in 4 chance to wake up every turn
			if (thawChance == 4)
			{
				statusTurn = 0;
				m_status = Status::none;
				cout << m_name << " Thawed out!" << endl;
			}
			else
			{
				cout << m_name << " is Frozen solid!" << endl;
				statusTurn += 1;
				return 2;
			}
		}
		else
		{
			statusTurn = 0;
			m_status = Status::none;
			cout << m_name << " Thawed out!" << endl;
		}
	}

	if (!hasMoved && flinch == true)
	{
		cout << m_name << " flinched and could not move!" << endl;
		return 2;
	}

	hasMoved = true;

	// if exit early due to flinch, sleep, paraysis or frozen everything else is skipped
	// if not and is confused then checks that

	if (confused)
	{
		int wakeUp = 0;
		cout << m_name << " is confused!" << endl;
		if (confusedTurn <= 4) {
			if (confusedTurn == 1)
			{
				cout << m_name << " hit itself in confusion!" << endl;
				confusedTurn++;
				return 2;
			}
			else if (confusedTurn == 2)
			{
				wakeUp = randomGenerator(1, 4);
				if (wakeUp == 4)
				{
					cout << m_name << " snapped out of confusion!" << endl;
					confusedTurn = 0;
				}
				else
				{
					cout << m_name << " hit itself in confusion!" << endl;
					confusedTurn++;
					return 2;
				}
			}
			else if (confusedTurn == 3)
			{
				wakeUp = randomGenerator(1, 3);
				if (wakeUp == 3)
				{
					cout << m_name << " snapped out of confusion!" << endl;
					confusedTurn = 0;
				}
				else
				{
					this->takeDmg(*this, &moveList[11]);
					cout << m_name << " hit itself in confusion!" << endl;
					confusedTurn++;
					return 2;
				}
			}
			else if (confusedTurn == 4)
			{
				wakeUp = randomGenerator(1, 2);
				if (wakeUp == 2)
				{
					cout << m_name << " snapped out of confusion!" << endl;
					confusedTurn = 0;
				}
				else
				{
					this->takeDmg(*this, &moveList[11]);
					cout << m_name << " hit itself in confusion!" << endl;
					confusedTurn++;
					return 2;
				}
			}
			else
			{
				cout << m_name << " snapped out of confusion!" << endl;
				confusedTurn = 0;
			}
			
		}
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
			return 0; // Stop execution here so no damage or status effects happen
		}
	}
	lastMoveUsed = moveset[slot];

	if (activeMove->getTarget() == "self") {
		if (moveset[slot] != nullptr) {
			moveset[slot]->use(*this, target, slot); // 'this' passes a reference to the user
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
		crit = false; // reset for next move
		if (moveset[slot] != nullptr) {
			static int ebool = 0;
			moveset[slot]->use(*this, target, damage, ebool,slot); // for extra effects after damage is calcuated
		}

	}

	return 1;

}

int Pokemon::takeDmg(Pokemon& attacker, Move* moveUsed)
{
	int damage = 1;
	bool confused = false;
	if (moveUsed->getName() == moveList[11].getName())
	{
		confused = true;
	}

	if (this->lastMoveUsed != nullptr)
	{
		if (isProtect && (moveUsed->getTarget() != "partner" && moveUsed->getCategory() != "Status"))
		{
			cout << this->m_name << " protected itself!" << endl;
			isProtect = false;
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

	int PreHitHp = m_hp;

	float typeMult;
	if (confused)
	{
		typeMult = 1;
	}
	else
	{
	typeMult = getEffectiveness(moveUsed->getType(), this->m_type1);
	typeMult *= getEffectiveness(moveUsed->getType(), this->m_type2); // factor in 2 types

	}


	float random = static_cast<float>(randomGenerator(85, 100));

	random = random / 100; // to turn it into a range of 0.85 - 1 cause 100 mutiplying it all is crazy
	// roll is for random damage, sometimes damage gets nerfed

	// lvl is 50 because doubles vgc format
	// damage = (((2 * lvl / 5) + 2) * PowerOfMove * (attackers attack / defenders defense)) / 50 + 2
	// then * targets (ig if it recives the spread nerf of 0.75) * stab * crit * random (85 - 100 / 100 aka 0.85 - 1.0) (moves sometimes do strong or weak hits)
	// then * burn (0.5 debuff if physical)
	damage = 0; // incase ability above changed it

	int power = moveUsed->getPower();
	if (attacker.helpingHand && !confused)
	{
		power *= 1.5;
	}

	int attack = 0;
	int defense = 0;
	double target = 1;
	double stab = 1;
	double type = 1;
	double burnReduce = 1; // 1 is no reduce


	if (moveUsed->getTarget() == "everyone" || moveUsed->getTarget() == "both opponents")
	{
		target = 0.75; //spread nerf, no single target (self, partner or 1 target) no nerf
	}

	if (moveUsed->getType() == attacker.m_type1 || moveUsed->getType() == attacker.m_type2)
	{
		stab = 1.5; // stab means same type attack bonus
	}

	int oldDefStage = this->m_statStages[1];
	int oldSpDefStage = this->m_statStages[3];


	if (moveUsed->getCategory() == "Physical")
	{
		attack = attacker.getStat(ATK);

		if (attacker.crit)
		{
			if (getStatStage(1) > 0)
			{
				modifyStatStage(DEF, -(oldDefStage)); // temp reset to 0 if attacker crits
			}
		}

		defense = this->getStat(DEF); // gets stat + stage mutipler
		if (m_status == Status::burned)
		{
			burnReduce = 0.5;
		}
	}
	else if (moveUsed->getCategory() == "Special")
	{
		attack = attacker.getStat(spATK);

		if (attacker.crit)
		{
			if (getStatStage(3) > 0) {
				modifyStatStage(DEF, -(oldSpDefStage)); // temp reset to 0 if attacker crits
			}
		}

		defense = this->getStat(spDEF);
	}

	m_ability->useAbility(attacker, *this, moveUsed, &power); // for any ability that buffs power

	damage = ((22.0 * power * (static_cast<double>(attack) / defense)) / 50 + 2.0) * target * stab * burnReduce * random * typeMult;

	if (attacker.crit) // attacker crits boost damage not defender
	{
		damage *= 1.5;

		if (oldDefStage > 0)
		{
			modifyStatStage(DEF, oldDefStage); // reset back to normal
		}
		if (oldSpDefStage > 0)
		{
			modifyStatStage(spDEF, oldSpDefStage);
		}

	}

	m_ability->useAbility(*this, attacker, moveUsed, &power, &damage); // for any ability that nerfs damage

	if (m_item != nullptr)
	{
		m_item->useItem(*this, attacker, damage, PreHitHp, moveUsed->getType());
		if (m_item->is1TimeUse())
		{
			deleteItem();
		}
	}


	this->m_hp -= damage;

	if (m_hp < 0)
	{
		m_hp = 0; // incase overkill
	}

	if (typeMult == 2)
	{
		cout << "it was SUPER effective!" << endl;
	}
	else if (typeMult == 4)
	{
		cout << "it was EXTREMELY effective!" << endl;
	}
	else if (typeMult == 0.5)
	{
		cout << "it was not very effective..." << endl;
	}
	else if (typeMult == 0.25)
	{
		cout << "it was extremely ineffective..." << endl;
	}
	else
	{
		cout << "it doesn't seem to affect..." << m_name << endl;
	}

	return damage;

}

void Pokemon::setProtect()
{
	isProtect = true;
}

void Pokemon::setHelpingHand()
{
	helpingHand = true;
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

int Pokemon::getStat(StatIndex stat) const
{

	int statVal = 0;
	int stageVal = 0;

	if (stat == ATK)
	{
		statVal = m_attack;
	}

	if (stat == spATK)
	{
		statVal = m_specialAttack;
	}

	if (stat == DEF)
	{
		statVal = m_defense;
	}

	if (stat == spDEF)
	{
		statVal = m_specialDefense;
	}

	if (stat == SPEED)
	{
		statVal = m_speed;

	}

	stageVal = m_statStages[stat];

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

void Pokemon::modifyStatStage(StatIndex stat, int amount)
{
	m_statStages[stat] += amount;
	if (m_statStages[stat] > 6)  m_statStages[stat] = 6;
	if (m_statStages[stat] < -6) m_statStages[stat] = -6;

	return;
}

void Pokemon::setStat(string stat, int statVal)
{

	if (stat == "atk")
	{
		m_attack = statVal;
	}

	if (stat == "spAtk")
	{
		m_specialAttack = statVal;
	}

	if (stat == "def")
	{
		m_defense = statVal;
	}

	if (stat == "spDef")
	{
		m_specialDefense = statVal;
	}

	if (stat == "speed")
	{
		m_speed = statVal;
	}

	return;
}

int Pokemon::getStatStage(int index) const
{
	return m_statStages[index];
}

int Pokemon::getLastStatStage(StatIndex stat) const
{
	return lastStatStage[stat];
}

void Pokemon::setLastStatStage(StatIndex stat)
{
	lastStatStage[stat] = m_statStages[stat];
}

void Pokemon::setMoves(string move1, string move2, string move3, string move4)
{
	//reason for new is due to abilties like prankster
	//without new it would affect the base move array
	for (size_t i = 0; i < moveListSize; i++)
	{
		if (move1 == moveList[i].getName()) {
			moveset[0] = new Move(moveList[i]);
		}

		if (move2 == moveList[i].getName()) {
			moveset[1] = new Move(moveList[i]);
		}

		if (move3 == moveList[i].getName()) {
			moveset[2] = new Move(moveList[i]);
		}

		if (move4 == moveList[i].getName()) {
			moveset[3] = new Move(moveList[i]);
		}
	}

}

void Pokemon::setItem(string itemName)
{
	for (size_t i = 0; i < itemListSize; i++)
	{
		if (itemName == itemList[i].getName()) {
			if (m_item != nullptr)
			{
				deleteItem();
			}
			m_item = new Item(itemList[i]);
		}
	}
}

void Pokemon::deleteItem()
{
	if (m_item != nullptr)
	{
		delete m_item;
		m_item = nullptr;
	}
}

void Pokemon::setFlinch(bool value)
{
	flinch = value;
}

void Pokemon::setConfusion(bool value)
{
	confused = value;
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

