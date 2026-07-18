#include "moveInfo.h"
#include <iostream>



Move::Move(string name, int power, int accuracy, string moveCat, string moveType, int pp, string extraNotes, string target, int priority, void (*effect)(Pokemon&, Pokemon&))
{

	m_name = name;
	m_power = power;
	m_accuracy = accuracy;
	m_category = moveCat;

	
	m_type = stringToType(moveType);
	m_powerPoints = pp;
	m_extraNotes = extraNotes;
	m_target = target;
	m_priority = priority;
	m_effect = effect;
}

void Move::use(Pokemon& user, Pokemon& target) const {
	std::cout << user.getName() << " used " << m_name << "!\n";

	// Calling a function pointer looks exactly like calling a regular function
	if (m_effect != nullptr) {
		m_effect(user, target);
	}
}

string Move::getName() const
{
	return m_name;
}

int Move::getPower() const
{
	return m_power;
}

int Move::getAccuracy() const
{
	return m_accuracy;
}

string Move::getCategory() const
{
	return m_category;
}

string Move::getTarget() const
{
	return m_target;
}

int Move::getPriority() const
{
	return m_priority;
}

Type Move::getType() const
{
	return m_type;
}

Move moveList[] = {
	Move("d", 5, 100, "a", "b", 10, "", "self", 0),
	Move("b", 5, 100, "a", "b", 10, "", "everyone", 0),
	Move("Gigaton Hammer", 160, 100, "Physical", "Steel",8,"Can't be used twice in a row", "1 oppoenent", 0),
	Move("Dragon Dance", 0, 100, "Status", "Dragon", 32, "", "self", 0 , 
		[](Pokemon& user, Pokemon& target) {
		user.modifyStat("atk", 1);
		std::cout << user.getName() << "Attack was raised" << "!\n";
		user.modifyStat("speed", 1);
		std::cout << user.getName() << "Speed was raised" << "!\n";
		
		}),
	Move("Coaching", 0, 100, "Status" , "Fighting", 16, "", "partner", 0,
		[](Pokemon& user, Pokemon& target) {
		target.modifyStat("atk", 1);
		std::cout << target.getName() << "Attack was raised" << "!\n";
		user.modifyStat("def", 1);
		std::cout << target.getName() << "Defense was raised" << "!\n";

		})
};

// Automatically calculates the number of elements: (Total bytes / Size of one element)
const size_t moveListSize = sizeof(moveList) / sizeof(moveList[0]);