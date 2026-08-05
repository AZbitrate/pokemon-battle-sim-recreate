#include "moveInfo.h"
#include "helper.h"
#include <iostream>
Move moveList[] = { //status moves on top and attack moves below
	Move("Coaching", 0, 100, "Status" , "Fighting", 16,  "partner", 0, "no property",
		[](Pokemon& user, Pokemon& target, int& damage, int moveSlot) {
		target.modifyStatStage(ATK, 1);
		std::cout << target.getName() << "Attack was raised" << "!\n";
		user.modifyStatStage(DEF, 1);
		std::cout << target.getName() << "Defense was raised" << "!\n";

		target.setLastStatStage(0);
		target.setLastStatStage(1);

		}),
	Move("Dragon Dance", 0, 100, "Status", "Dragon", 32,  "self", 0 , "no property",
		[](Pokemon& user, Pokemon& target, int& damage, int moveSlot) {
		user.modifyStatStage(ATK, 1);
		std::cout << user.getName() << "Attack was raised" << "!\n";
		user.modifyStatStage(SPEED, 1);
		std::cout << user.getName() << "Speed was raised" << "!\n";

		user.setLastStatStage(0);
		user.setLastStatStage(4);

		}),
	Move("Helping Hand", 0, 100, "Status", "Normal", 32,  "partner", 5, "no property",
		[](Pokemon& user, Pokemon& target, int& damage, int moveSlot) {
			target.setHelpingHand();
			//boosts partner move
		}),
	Move("Protect", 0, 100, "Status", "Normal", 16,  "self", 4, "protect",
		[](Pokemon& user, Pokemon& target, int& damage, int moveSlot) {
			user.setProtect();
			// do no dmg, take no dmg
		}),


	Move("Twin Beam", 40, 100, "Special", "Psychic", 16, "1 opponent", 0, "muti hit",
		[](Pokemon& user, Pokemon& target, int& damage, int moveSlot) {
			if (damage == 0)
			{
				user.performMove(moveSlot, target); // move hits twice so the function is called again
				damage = 1; // to prevent endless loop
			}
			else
			{

				damage = 0; // reset for next muti move
			}
		}),
	Move("Sludge Bomb", 90, 100, "Special" , "Poison", 16, "1 opponent", 0, "poison",
		[](Pokemon& user, Pokemon& target, int& damage, int moveSlot) {

			handleStatus(user,target, 30, Type::Poison,Type::Steel, Status::poison);
			

		}),
	
	Move("Gigaton Hammer", 160, 100, "Physical", "Steel",8),
	
	Move("Drain Punch", 75, 100, "Physical" , "Fighting", 16,  "1 opponent", 0, "contact",
		[](Pokemon& user, Pokemon& target, int& damage, int moveSlot) {

			user.updateHP(damage * 0.5); // heals 50% of dmg done

		}),
	Move("Fake Out", 40, 100, "Physical" , "Normal", 16, "1 opponent", 3, "contact",
		[](Pokemon& user, Pokemon& target, int& damage, int moveSlot) {

			target.setFlinch(true); // always flinch but only can use first turn

		}),
	

};

// Automatically calculates the number of elements: (Total bytes / Size of one element)
const size_t moveListSize = sizeof(moveList) / sizeof(moveList[0]);