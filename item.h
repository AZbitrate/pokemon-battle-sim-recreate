#pragma once
#include <string>
#include "pokemon.h"
using std::string;

//forward declaration: tell the compiler the class exists before handling the logic
class Pokemon;

class Item
{
	string m_name;
	void (*m_effect)(Pokemon&, Pokemon&) = nullptr;



public:
	Item();
	~Item();

};