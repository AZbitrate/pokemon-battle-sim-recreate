#include "item.h"

Item::Item(string name, bool oneTime, void(*effect)(Pokemon&, Pokemon&))
{
	m_name = name;
	m_effect = effect;
	oneTimeUse = oneTime;
}

void Item::useItem(Pokemon& user, Pokemon& target)
{
	if (m_effect != nullptr) {
		m_effect(user, target);
	}
}

string Item::getName() const
{
	return m_name;
}

