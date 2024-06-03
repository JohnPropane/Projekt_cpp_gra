#include <iostream>
using namespace std;
#pragma once
class Skill
{
public:
	string name;
	int manaCost;
	string description;
	int value;
	int type;
	int level = 0;

	/*
		SKILL TYPES:
		1 -> damage skill
		2 -> defence skill
		3 -> damage over time (dot)
	*/

	Skill(){}

	Skill(string name, int manaCost, string description, int value, int type) {
		this->name = name;
		this->manaCost = manaCost;
		this->description = description;
		this->value = value;
		this->type = type;
	}
};

