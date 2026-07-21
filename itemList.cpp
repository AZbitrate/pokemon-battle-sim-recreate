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

		})
};

// Automatically calculates the number of elements: (Total bytes / Size of one element)
const size_t itemListSize = sizeof(itemList) / sizeof(itemList[0]);