#include <iostream>
#include <random>
#pragma once
using namespace std;

class Item
{
public:
	string name;
	string description;
	string type;
	string rarity;

	Item() {};

	Item(string name, string description, string rarity, string type) {
		this->name = name;
		this->description = description;
		this->rarity = rarity;
		this->type = type;
	}

};

class Weapon : public Item
{
public:
	int minDamage;
	int maxDamage;

	Weapon() {};

	Weapon(string name, string description, string rarity, string type, int minDamage, int maxDamage)
		:Item(name, description, rarity, type) {
		this->minDamage = minDamage;
		this->maxDamage = maxDamage;
	}

	int generateDamage(){
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(minDamage, maxDamage); // define the range
		return distr(gen);
	}
};

class Potion : public Item
{
public:
	/*
		POTIONS EFFECTS:
		1 = HEALING POTION
		2 = DAMAGE POTION
	*/
	int effect;
	int effectValue;
	string effectStr;

	Potion() {};

	Potion(string name, string description, string rarity, string type, int effect, int effectValue)
		:Item(name, description, rarity, type) {
		this->effect = effect;
		this->effectValue = effectValue;
		if (effect == 1) {
			effectStr = "Healing Potion";
		}
		else {
			effectStr = "Damage Potion";
		}
	}

};

class Armor : public Item
{
public:
	int value;
	int resistanceType;
	string resistanceTypeStr = "";

	/*
		RESISTANCE TYPE:
		1 -> RedFire Resistance
		2 -> BlackFire Resistance
		3 -> BlueFire Resistance
		4 -> GreenFire Resistance
		5 -> WhiteFire Resistance
	*/

	Armor() {};

	Armor(string name, string description, string rarity, string type, int value, int resistanceType)
		:Item(name, description, rarity, type) {
		this->value = value;
		this->resistanceType = resistanceType;
		if (resistanceType == 1) {
			resistanceTypeStr = "RedFire Resistance";
		}
		else if (resistanceType == 2) {
			resistanceTypeStr = "BlackFire Resistance";
		}
		else if (resistanceType == 3) {
			resistanceTypeStr = "BlueFire Resistance";
		}
		else if (resistanceType == 4) {
			resistanceTypeStr = "GreenFire Resistance";
		}
		else {
			resistanceTypeStr = "WhiteFire Resistance";
		}
	}
};

