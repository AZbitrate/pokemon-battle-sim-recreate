#include "moveInfo.h"
#include <iostream>
Move moveList[] = {
	Move("d", 5, 100, "a", "b", 10, "", "self", 0),
	Move("b", 5, 100, "a", "b", 10, "", "everyone", 0),
	Move("Gigaton Hammer", 160, 100, "Physical", "Steel",8,"Can't be used twice in a row", "1 oppoenent", 0),
	Move("Dragon Dance", 0, 100, "Status", "Dragon", 32, "", "self", 0 , "no property",
		[](Pokemon& user, Pokemon& target, int damage) {
		user.modifyStat("atk", 1);
		std::cout << user.getName() << "Attack was raised" << "!\n";
		user.modifyStat("speed", 1);
		std::cout << user.getName() << "Speed was raised" << "!\n";

		user.setLastStatStage(0);
		user.setLastStatStage(4);

		}),
	Move("Coaching", 0, 100, "Status" , "Fighting", 16, "", "partner", 0, "no property",
		[](Pokemon& user, Pokemon& target, int damage) {
		target.modifyStat("atk", 1);
		std::cout << target.getName() << "Attack was raised" << "!\n";
		user.modifyStat("def", 1);
		std::cout << target.getName() << "Defense was raised" << "!\n";

		target.setLastStatStage(0);
		target.setLastStatStage(1);

		}),
	Move("Drain Punch", 75, 100, "Physical" , "Fighting", 16, "heals 50% of damage done", "1 opponent", 0, "no property",
		[](Pokemon& user, Pokemon& target, int damage) {

			user.updateHP(damage * 0.5);

		})

};

// Automatically calculates the number of elements: (Total bytes / Size of one element)
const size_t moveListSize = sizeof(moveList) / sizeof(moveList[0]);