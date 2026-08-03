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

Move::Move(Move& old)
{
	m_name = old.m_name;
	m_power = old.m_power;
	m_accuracy = old.m_accuracy;
	m_category = old.m_category;


	m_type = old.m_type;
	m_powerPoints = old.m_powerPoints;
	m_extraNotes = old.m_extraNotes;
	m_target = old.m_target;
	m_priority = old.m_priority;
	m_effect = old.m_effect;
	m_property = old.m_property;
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
