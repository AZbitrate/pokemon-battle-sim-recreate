#pragma once
#include <string>
#include "pokemon.h"
#include "typeInfo.h"
using std::string;

//forward declaration: tell the compiler the class exists before handling the logic
class Pokemon;
enum class Status;

class Move
{

	string m_name;
	int m_power;
	int m_accuracy;
	string m_category; //physical, ranged or status
	Type m_type; // grass, fire, etc
	int m_powerPoints;
	string m_target; // self, partner, 1 opponent, both oppoents or everyone (like earthquake so not really everyone)
	int m_priority; // most moves are 0 but some are higher or slower
	string m_property; // contact, slicing etc. some moves don't have this

public:
	void (*m_effect)(Pokemon&, Pokemon&, int& damage, int moveSlot) = nullptr;
	Move(string name, int power, int accuracy, string moveCat, string moveType, int pp, string target = "1 opponent", int priority = 0, string property = "", void (*effect)(Pokemon&, Pokemon&, int& damage, int moveSlot) = nullptr);
	Move(Move& old);
	void use(Pokemon& user, Pokemon& target, int& damage, int moveSlot = 0) const;
	~Move() = default;

	string getName() const;
	int getPower() const;
	int getAccuracy() const;
	string getCategory() const;
	string getTarget() const;
	int getPriority() const;
	Type getType() const;
	string getProperty() const;
};

extern Move moveList[];
extern const size_t moveListSize; // Tells other files how many moves there are
