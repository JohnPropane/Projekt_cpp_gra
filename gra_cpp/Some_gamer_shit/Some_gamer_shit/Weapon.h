#include <iostream>
#include <random>
using namespace std;
#pragma once

#pragma once
class Weapon : public Item
{
public:
	int minDamage;
	int maxDamage;

	Weapon(string name, string description, string rarity, string type, int minDamage, int maxDamage)
		:Item(name, description, rarity, type) {
		this->minDamage = minDamage;
		this->maxDamage = maxDamage;
	}

	int generateDamage() {
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(minDamage, maxDamage); // define the range
		return distr(gen);
	}
};

