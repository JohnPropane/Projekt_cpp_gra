#include <iostream>
#include <random>
using namespace std;
#pragma once
class Dragon
{
public:
	std::string name;
	int type;
	int health;
	int minDmg;
	int maxDmg;
	int dodgeRate;

	/*
		index 0 = how many turns of dot left
		index 1 = how many damage dragon takes
	*/
	int dotInfo[2] = { 0, 0 };

	/*
		DRAGON TYPES:
		1 -> RedFire
		2 -> BlackFire
		3 -> BlueFire
		4 -> GreenFire
		5 -> WhiteFire
	*/

	Dragon(){}

	Dragon(std::string name, int type, int health, int min_dmg, int max_dmg) {
		this->name = name;
		this->type = type;
		this->health = health;
		this->minDmg = min_dmg;
		this->maxDmg = max_dmg;
		dodgeRate = 100;
	}

	void showHealth() {
		std::cout << "Health: " << health << " HP" << std::endl;
	}

	bool isAlive() {
		if (health <= 0) {
			health = 0;
			return false;
		}
		else {
			return true;
		}
	}

	int dealDamage() {
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(minDmg, maxDmg); // define the range
		return distr(gen);
	}

	void takeDamage(int dmg) {
		health -= dmg;
	}

	void checkDot() {
		if (dotInfo[0] > 0) {
			dotInfo[0] -= 1;
			health -= dotInfo[1];
			cout << "Dragon took " << dotInfo[1] << " DMG from damage over time" << endl;
		}
	}

	Dragon currentEnemy() {
		Dragon d(name, type, health, minDmg, maxDmg);
		return d;
	}
};

