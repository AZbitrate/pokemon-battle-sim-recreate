#pragma once
#include <string>
#include "moveInfo.h"
using std::string;

//forward declaration: tell the compiler the class exists before handling the logic
class Pokemon;
class Move;

class Ability
{
	string m_name;
	void (*m_effect)(Pokemon&, Pokemon&, Move* move, int* power, int* dmg) = nullptr;


public:
	Ability() = default;
	Ability(string name, void (*effect)(Pokemon&, Pokemon&, Move* move, int* power, int* dmg) = nullptr);
	~Ability() = default;

	string getName();

	void useAbility(Pokemon& user, Pokemon& target, Move* moveUsed = nullptr, int* power = 0, int* dmg = 0);
	//global array of abilites that pokemon class gets info from

};

extern Ability abilityList[];
extern const size_t abilityListSize;
