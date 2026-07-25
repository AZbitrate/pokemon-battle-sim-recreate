#include "item.h"
Item itemList[]{
	Item("Sitrus Berry", true ,
		[](Pokemon& user, Pokemon& target) {

			if (static_cast<double>(user.getHp()) / user.getMaxHp() <= 0.5) // when hp lower than 50%
			{

				user.updateHP(user.getMaxHp() * 0.25); // quarter of max hp heal back

			}

		}),
	Item("Leftovers", false ,
		[](Pokemon& user, Pokemon& target) {
				user.updateHP(user.getMaxHp() * 0.0625); // heal back 1/16 of hp per turn

		}),
	Item("Venusaurite", false ,
		[](Pokemon& user, Pokemon& target) {
				user.setStat("atk", user.getStat(ATK) + 18);
				user.setStat("def", user.getStat(DEF) + 40);
				user.setStat("spAtk", user.getStat(spATK) + 22);
				user.setStat("spDef", user.getStat(spDEF) + 20);
				user.setAbility("Thick Fat");

		}),
	Item("Charizardite X", false ,
		[](Pokemon& user, Pokemon& target) {
				user.setStat("atk", user.getStat(ATK) + 46);
				user.setStat("def", user.getStat(DEF) + 33);
				user.setStat("spAtk", user.getStat(spATK) + 21);
				user.setAbility("Tough Claws");

		}),

};

// Automatically calculates the number of elements: (Total bytes / Size of one element)
const size_t itemListSize = sizeof(itemList) / sizeof(itemList[0]);