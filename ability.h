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
	Ability(string name, void (*effect)(Pokemon&, Pokemon&));
	~Ability() = default;

	void useAbility(Pokemon& user, Pokemon& target);

};
