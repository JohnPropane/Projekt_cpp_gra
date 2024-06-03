#include <iostream>
#include "Item.h"
#include "Dragon.h"
#include "Skill.h"
#include <vector>
#include <cmath>
using namespace std;
#pragma once
class Player
{
public:
	string name;
	int health = 100;
	int level = 0;
	int mana = 10;
	int exp = 0;
	int hints[2];

	/*
		index 0 = how many turns of dot left
		index 1 = how many damage player takes
	*/
	int dotInfo[2] = {0, 0};

	vector <Weapon> weapons;
	Weapon activeWeapon;

	vector <Armor> armors;
	Armor activeArmor;

	vector <Potion> potions;

	vector <Skill> skills;

	//Constructor
	Player(string name) {
		this->name = name;
	}


	//Player info and basic actions
	void showHealth() {
		cout << "Health: " << health << " HP" << endl;
	}

	void showMana() {
		cout << "Mana: " << mana << " Mana" << endl;
	}

	void takeDamage(int dmg, int damageType) {
		if (damageType == activeArmor.resistanceType) {
			double damageReduction = activeArmor.value / 100.0;
			int reducedDamage = ceil(dmg * damageReduction);
			health -= dmg - reducedDamage;
			cout << "Dragon dealt you " << dmg - reducedDamage << " DMG" << endl;
		}
		else {
			health -= dmg;
			cout << "Dragon dealt you " << dmg << " DMG" << endl;
		}
		
	}

	void checkDot() {
		if (dotInfo[0] > 0) {
			dotInfo[0] -= 1;
			health -= dotInfo[1];
		}
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
		return 1 + activeWeapon.generateDamage();
	}


	//Waepons section
	void takeWeapon(Weapon weapon) {
		weapons.push_back(weapon);
	}

	void showWeapons() {
		for (int i = 0; i < weapons.size(); i++) {
			cout << endl;
			cout << i+1 << ". " + weapons[i].name << endl;
			cout << "--> Description: " << weapons[i].description << endl;
			cout << "--> Rarity: " << weapons[i].rarity << endl;
			cout << "--> Damage: " << weapons[i].minDamage << " - " << weapons[i].maxDamage << " DMG" << endl;
			cout << "---------------------------------------------" << endl;
		}
	}

	void setActiveWeapon(Weapon weapon) {
		activeWeapon = weapon;
	}


	//Potions
	void takePotion(Potion potion) {
		potions.push_back(potion);
	}

	void usePotion(Potion potion, Dragon &dragon) {
		if (potion.effect == 1) {
			health += potion.effectValue;
			if (health > 100) {
				health = 100;
			}
		}
		else if (potion.effect == 2) {
			dragon.takeDamage(potion.effectValue);
		}
	}

	void removePotion(int i) {
		potions.erase(potions.begin() + (i - 1));
	}

	void showPotions() {
		for (int i = 0; i < potions.size(); i++) {
			cout << i + 1 << ". " + potions[i].name << endl;
			cout << potions[i].effectStr << endl;
			cout << potions[i].description << endl;
			cout << "---------------------------------------------" << endl;
		}
	}


	//Armor
	void takeArmor(Armor armor) {
		armors.push_back(armor);
	}

	void showArmors() {
		for (int i = 0; i < armors.size(); i++) {
			cout << i + 1 << ". " + armors[i].name << endl;
			cout << armors[i].description << endl;
			cout << armors[i].rarity << endl;
			cout << armors[i].resistanceTypeStr << endl;
			cout << "---------------------------------------------" << endl;
		}
	}

	void setActiveArmor(Armor armor) {
		activeArmor = armor;
	}

	//Skill
	void takeSkill(Skill skill) {
		skills.push_back(skill);
	}

	void showSkills() {
		for (int i = 0; i < skills.size(); i++) {
			cout << "---------------------------------------------" << endl;
			cout << i + 1 << ". " + skills[i].name << endl;
			cout << skills[i].description << endl;
			cout << "Skill level: " << skills[i].level << endl;
			cout << "Skill mana cost: " << skills[i].manaCost << endl;
			cout << "Skill value:" << skills[i].value << endl;
			
		}
	}

	void upgradeSkill(int i) {
		skills[i].level++;
		skills[i].value += ceil(skills[i].value * 1.5);
	}

	void useSkill(Skill skill, Dragon &dragon) {
		mana -= skill.manaCost;
		int type = skill.type;
		if (type == 1) {
			dragon.takeDamage(skill.value);
			cout << "You dealt " << skill.value << " DMG to Dragon" << endl;
		}
		else if (type == 2) {
			health += skill.value;
			cout << "You healed " << skill.value << " HP" << endl;
		}
		else if (type == 3) {
			dragon.dotInfo[0] = 3;
			dragon.dotInfo[1] = skill.value;
			cout << "You set a dot effect on a dragon " << endl;
			cout << "It will take " << dragon.dotInfo[1] << " DMG every " << dragon.dotInfo[0] << " turns" << endl;
		}
	}

	//EXP
	void checkExp() {
		if (exp >= 100) {
			level++;
			exp -= 100;
			cout << "\nLEVEL UP!\n" << endl;
			cout << "What skill do you wanna upgrade?" << endl;
			showSkills();
			int choice;
			while (true) {
				cin >> choice;
				if (choice > skills.size() || choice < 1) {
					cout << "Wrong choice! Try again." << endl;
				}
				else {
					upgradeSkill(choice - 1);
					break;
				}
			}

		}
	}
};

