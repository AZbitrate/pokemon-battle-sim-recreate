#pragma once
#include <string>
using std::string;

//forward declaration: tell the compiler the class exists before handling the logic
class Pokemon;

class Ability
{
	string m_name;
	void (*m_effect)(Pokemon&, Pokemon&) = nullptr;


public:
	Ability(string name, void (*effect)(Pokemon&, Pokemon&) = nullptr);
	~Ability() = default;

	string getName();

	void useAbility(Pokemon& user, Pokemon& target);
	//global array of abilites that pokemon class gets info from

};

extern Ability abilityList[];
extern const size_t abilityListSize;
