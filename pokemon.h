#pragma once
#include <string>
#include "moveInfo.h"
#include "ability.h"
#include <iostream>
using std::string;
using std::cout;
using std::endl;

//forward declaration: tell the compiler the class exists before handling the logic
class Move;

class Pokemon
{

	string m_type1;
	string m_type2;
	string m_name;
	string m_species;

	Ability* m_ability;

	int maxHp;
	int m_hp;
	int m_attack;
	int m_defense;
	int m_specialAttack;
	int m_specialDefense;
	int m_speed;

	//string move1, move2, move3, move4;
	Move* moveset[4] = { nullptr, nullptr, nullptr, nullptr }; //handle getting moves,items and abilites later

	bool isPoison, isBurned, isParaysis, isFrozen;

	Move* lastMoveUsed = nullptr;

	int m_statStages[5]{ 0 };
public:

	int atkStage = 0;
	int defStage = 0;
	int spAtkStage = 0;
	int spDefStage = 0;
	int speedStage = 0;
	// for moves that boost stats

	Pokemon(string type1, string type2,
		string name, string species,
		string abilityName,  int hp, int atk,
		int def, int spAtk, int spDef, int speed); // effect is with ability name to form ability
	~Pokemon() = default;

	// Helper to trigger a move from their moveset
	void performMove(int slot, Pokemon& target);

	void takeDmg(Pokemon& attacker, Move* moveUsed);

	string getName() const;
	int getHp() const;
	int getMaxHp() const;
	//int setHP();

	int getStat(string stat);
	//setters only change stage values not the direct stat
	int checkStage(int stat, int stage);

	int modifyStat(string stat, int statVal);

};

