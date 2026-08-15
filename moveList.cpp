#include "moveInfo.h"
#include "helper.h"
#include <iostream>
Move moveList[] = { //status moves on top and attack moves below
	Move("Coaching", 0, 100, "Status" , "Fighting", 16,  "partner", 0, "no property",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {
		target.modifyStatStage(ATK, 1);
		user.modifyStatStage(DEF, 1);

		std::cout << target.getName() << " Attack and Defense was raised" << "!\n";
		target.setLastStatStage(ATK);
		target.setLastStatStage(DEF);

		}),
	Move("Dragon Dance", 0, 100, "Status", "Dragon", 32,  "self", 0 , "no property",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {
		user.modifyStatStage(ATK, 1);
		user.modifyStatStage(SPEED, 1);

		std::cout << user.getName() << " Attack and Speed was raised" << "!\n";
		user.setLastStatStage(ATK);
		user.setLastStatStage(SPEED);

		}),
	Move("Helping Hand", 0, 100, "Status", "Normal", 32,  "partner", 5, "no property",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {
			target.setHelpingHand();
			//boosts partner move
		}),
	Move("Protect", 0, 100, "Status", "Normal", 16,  "self", 4, "protect",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {
			user.setProtect();
			// do no dmg, take no dmg
		}),


	Move("Twin Beam", 40, 100, "Special", "Psychic", 16, "1 opponent", 0, "muti hit",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {
			if (mutiHit == 0)
			{
				user.performMove(moveSlot, target); // move hits twice so the function is called again
				mutiHit = 1; // to prevent endless loop
			}
			else
			{

				mutiHit = 0; // reset for next muti move
			}
		}),
	Move("Sludge Bomb", 90, 100, "Special" , "Poison", 16, "1 opponent", 0, "poison",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {

			handleStatus(user,target, 30, Type::Poison,Type::Steel, Status::poison);

		}),
	Move("Dire Claw", 80, 100, "Physical" , "Poison", 24, "1 opponent", 0, "contact",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {
			if (user.randomGenerator(1,3) == 3) // 1 in 3 chance of a status
			{
				int statusRoll = user.randomGenerator(1, 3);
				if (statusRoll == 1) // rolls another 1 in 3 since there is 3 status
				{
					handleStatus(user,target, 100, Type::Poison,Type::Steel, Status::poison);
				}
				else if (statusRoll == 2)
				{
					handleStatus(user, target, 100, Type::Electric, Type::None, Status::paralysis);
				}
				else
				{
					handleStatus(user, target, 100, Type::None, Type::None, Status::sleep);
				}
			}


		}),
	
	Move("Gigaton Hammer", 160, 100, "Physical", "Steel",8),
	
	Move("Drain Punch", 75, 100, "Physical" , "Fighting", 16,  "1 opponent", 0, "contact",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {

			user.updateHP(damage * 0.5); // heals 50% of dmg done

		}),
	Move("Close Combat", 120, 100, "Physical" , "Fighting", 8,  "1 opponent", 0, "contact",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {

			user.modifyStatStage(DEF, -1);
			user.modifyStatStage(spDEF, -1);

			std::cout << user.getName() << " Defense and special defense was lowered" << "!\n";

			user.setLastStatStage(DEF);
			user.setLastStatStage(spDEF);

		}),
	Move("Fake Out", 40, 100, "Physical" , "Normal", 16, "1 opponent", 3, "contact",
		[](Pokemon& user, Pokemon& target, int& damage, int mutiHit, int moveSlot) {

			target.setFlinch(true); // always flinch but only can use first turn

		}),
	Move("ConfusedHit", 40, 100, "Physical" , "Typeless", 16, "self", 3, ""),
	

};

// Automatically calculates the number of elements: (Total bytes / Size of one element)
const size_t moveListSize = sizeof(moveList) / sizeof(moveList[0]);