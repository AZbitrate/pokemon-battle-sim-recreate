#pragma once
#include <string>
#include "moveInfo.h"
using std::string;

//forward declaration: tell the compiler the class exists before handling the logic
class Move;

class Pokemon
{

	string m_type1;
	string m_type2;
	string m_name;
	string m_species;

	string m_ability;

	int maxHp;
	int m_hp;
	int m_attack;
	int m_defense;
	int m_specialAttack;
	int m_specialDefense;
	int m_speed;

	//string move1, move2, move3, move4;
	Move* moveset[4] = { nullptr, nullptr, nullptr, nullptr };

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
		string ability, int hp, int atk,
		int def, int spAtk, int spDef, int speed);
	~Pokemon() = default;

	// Helper to trigger a move from their moveset
	void performMove(int slot, Pokemon& target);

	int getHp();
	//int setHP();

	//setters only change stage values not the direct stat
	int getStat(string stat);
	int checkStage(int stat, int stage);

	int modifyStat(string stat, int statVal);

	

	string getName() const;
};

