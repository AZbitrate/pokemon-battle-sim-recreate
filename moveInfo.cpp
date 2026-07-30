#include "moveInfo.h"
#include <iostream>



Move::Move(string name, int power, int accuracy, string moveCat, string moveType, int pp, string extraNotes, string target, int priority, string property, void (*effect)(Pokemon&, Pokemon&, int& damage, int moveSlot))
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
	m_property = property;
}

void Move::use(Pokemon& user, Pokemon& target, int& damage, int moveSlot) const {
	std::cout << user.getName() << " used " << m_name << "!\n";

	// Calling a function pointer looks exactly like calling a regular function
	if (m_effect != nullptr) {
		m_effect(user, target, damage, moveSlot);
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

string Move::getProperty() const
{
	return m_property;
}
