#include "item.h"

Item::Item(string name, void(*effect)(Pokemon&, Pokemon&))
{
	m_name = name;
	m_effect = effect;
}

void Item::useItem(Pokemon& user, Pokemon& target)
{
	if (m_effect != nullptr) {
		m_effect(user, target);
	}
}
