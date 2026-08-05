#include "helper.h"
void handleStatus(Pokemon& user, Pokemon& target, int chance, Type immune1, Type immune2, Status type)
{
	int statusChance = target.randomGenerator(1, 100);
	string statusType;
	if (statusChance <= chance)
	{
		if ((target.getType(1) != immune1 && target.getType(2) != immune1) &&
			(target.getType(1) != immune2 && target.getType(2) != immune2))
		{
			target.setStatus(type);
			if (type == Status::poison)
			{
				statusType = "poisoned";
			}
			if (type == Status::burned)
			{
				statusType = "burned";
			}
			if (type == Status::paralysis)
			{
				statusType = "paralyzed";
			}
			if (type == Status::frozen)
			{
				statusType = "frozen";
			}

			if (type == Status::sleep)
			{
				cout << target.getName() << " fell asleep!" << endl;
				return;
			}
			cout << target.getName() << " got " << statusType << "!" << endl;
		}
		else
		{
			cout << "it doesn't seem to affect " << target.getName() << "..." << endl;
		}
	}
}