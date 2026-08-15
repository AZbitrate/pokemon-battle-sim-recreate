#pragma once
#include <string>
#include "moveInfo.h"
#include "ability.h"
#include "typeInfo.h"
#include <iostream>
#include "item.h"
#include "statIndex.h"
#include "status.h"
using std::string;
using std::cout;
using std::endl;

//forward declaration: tell the compiler the class exists before handling the logic
class Move;
//enum class Type;
class Ability;
class Item;
//enum StatIndex;

class Pokemon
{

	Type m_type1;
	Type m_type2;
	string m_name;
	string m_species;

	Ability* m_ability;

	Item* m_item = nullptr;

	int maxHp;
	int m_hp;
	int m_attack;
	int m_defense;
	int m_specialAttack;
	int m_specialDefense;
	int m_speed;

	//string move1, move2, move3, move4;
	Move* moveset[4] = { nullptr, nullptr, nullptr, nullptr }; //handle getting moves,items and abilites later

	Status m_status = Status::none;
	int statusTurn = 0;


	Move* lastMoveUsed = nullptr;

	int m_statStages[5]{ 0 }; // stages of each stat. assume same order as the list of stats above (does not include hp)
	int lastStatStage[5]{ 0 }; // ment to be a copy of statStages only use is for a desync to trigger defiant or competitve

	int critStage = 0;

	bool crit = false;
	bool isProtect = false;
	bool helpingHand = false;

	bool confused = false;
	int confusedTurn = 0;
	bool flinch = false;
	bool hasMoved = false;

public:

	Pokemon(string type1, string type2,
		string name, string species,
		string abilityName,  int hp, int atk,
		int def, int spAtk, int spDef, int speed); // effect is with ability name to form ability
	~Pokemon();

	void setAbility(const string& abilityName);
	Ability* getAbility() const;
	
	void setStatus(Status stat);
	Status getStatus() const;
	void cureStatus();

	Type getType(int type);

	int performMove(int slot, Pokemon& target);
	int takeDmg(Pokemon& attacker, Move* moveUsed);

	void setProtect();
	void setHelpingHand();

	string getName() const;
	int getHp() const;
	int getMaxHp() const;
	int updateHP(int value);

	int getStat(StatIndex stat) const;
	//checkStage is helper function to getStat
	int checkStage(int stat, int stage) const;
	void modifyStatStage(StatIndex stat, int statVal); //changes stage

	// only used for moves that alter actual stats (speed swap, guard swap) and items (mega stones)
	void setStat(string stat, int statVal); 

	int getStatStage(int index) const; // getting stage only not both stat + stage
	int getLastStatStage(StatIndex stat) const;
	void setLastStatStage(StatIndex stat); // only for defiant and competitve

	//set move and items
	void setMoves(string move1 = "", string move2 = "", string move3 = "", string move4 = "");
	void setItem(string itemName);
	void deleteItem();

	void setFlinch(bool value);
	void setConfusion(bool value);

	int randomGenerator(int lowRange, int highRange);
};

