#pragma once // only contains the array of abilities
#include "ability.h"
#include "pokemon.h"
#include <iostream>
using std::cout;

Ability abilityList[] = {
	Ability("Thick Fat", // cuts fire and ice damage in half after dmg calculation
		[](Pokemon& user, Pokemon& target, Move* moveUsed, int* power, int* dmg) {
		if (*dmg > 0)
		{
			if (moveUsed->getType() == Type::Fire || moveUsed->getType() == Type::Ice)
			{
				*dmg = *dmg / 2; 
				// need to always do * with pointer to dereference and get the actual value
				// & reference don't need that since it's the actual value itself
			}
		}

		}),
		Ability("Tough Claws", // boosts contact move's power by 1.3
		[](Pokemon& user, Pokemon& target, Move* moveUsed, int* power, int* dmg) {
		if (moveUsed->getProperty().find("contact") != string::npos)
		{
			*power = static_cast<int>(*power * 1.3);
		}

		}),
		Ability("Armor Tail",
		[](Pokemon& user, Pokemon& target, Move* moveUsed, int* power, int* dmg) {
		if (moveUsed->getPriority() > 0 || (target.getAbility()->getName() == "Prankster" && moveUsed->getCategory() == "Status"))
		{
			cout << "Armor Tail blocked " << moveUsed->getName() << " from working!" << endl;

			// power in this case is used as a bool
			*power = 0;
		}

		}),
	Ability("Defiant", // boost attack when any stat is lowered
		[](Pokemon& user, Pokemon& target, Move* moveUsed, int* power, int* dmg) {
		for (size_t i = 0; i < 5; i++)
		{
			//if same do nothing
			if (user.getStatStage(i) != user.getLastStatStage(i))
			{
				user.modifyStatStage("atk", 2);
				cout << user.getName() << "'s attack sharply raised!" << endl;
				user.setLastStatStage(i);

			}

		}

		}),
	Ability("Competitive", // boost sp attack when any stat is lowered
		[](Pokemon& user, Pokemon& target, Move* moveUsed, int* power, int* dmg) {
		for (size_t i = 0; i < 5; i++)
		{
			//if same do nothing
			if (user.getStatStage(i) != user.getLastStatStage(i)) // only desync when lowering stat
			{
				user.modifyStatStage("spAtk", 2);
				cout << user.getName() << "'s speacial attack sharply raised!" << endl;
				user.setLastStatStage(i); // then resync

			}

		}

		})
};

// Automatically calculates the number of elements: (Total bytes / Size of one element)
const size_t abilityListSize = sizeof(abilityList) / sizeof(abilityList[0]);
