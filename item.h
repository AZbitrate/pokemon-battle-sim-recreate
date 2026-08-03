#pragma once
#include <string>
#include "pokemon.h"
using std::string;

//forward declaration: tell the compiler the class exists before handling the logic
class Pokemon;

class Item
{
	string m_name;
	void (*m_effect)(Pokemon&, Pokemon&, int& dmg, int preHitHp, Type moveType) = nullptr;
	bool oneTimeUse;


public:
	Item(string name, bool oneTime, void (*effect)(Pokemon&, Pokemon&, int& dmg, int preHitHp, Type moveType) = nullptr);
	Item(Item& old); //copy constructor
	~Item() = default;

	void useItem(Pokemon& user, Pokemon& target, int& dmg, int preHitHp = 0, Type moveType = Type::None);
	string getName() const;
	bool is1TimeUse() const;
	//assign item function later
};

extern Item itemList[];
extern const size_t itemListSize;