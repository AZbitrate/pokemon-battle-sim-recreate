#include "item.h"

Item::Item(string name, bool oneTime, void(*effect)(Pokemon&, Pokemon&, int& dmg, int preHitHp, Type moveType))
{
	m_name = name;
	m_effect = effect;
	oneTimeUse = oneTime;
}

Item::Item(Item& old)
{
	m_name = old.m_name;
	m_effect = old.m_effect;
	oneTimeUse = old.oneTimeUse;

}

void Item::useItem(Pokemon& user, Pokemon& target, int& dmg, int preHitHp, Type moveType)
{
	if (m_effect != nullptr) {
		m_effect(user, target, dmg, preHitHp, moveType);
	}
}

string Item::getName() const
{
	return m_name;
}

bool Item::is1TimeUse() const
{
	return oneTimeUse;
}

