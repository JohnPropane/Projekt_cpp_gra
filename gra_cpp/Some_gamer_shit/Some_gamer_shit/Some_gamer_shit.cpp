#include <iostream>
#include "Dragon.h"
#include "Player.h"
#include "Item.h"
#include "Game.h"
#include <vector>
#include <cctype>

struct Node {
	vector<string> texts;
	Dragon dragon;
	vector<string> choices;
	vector<Node*> nextNodes;
	Node(const vector<string>& t) : texts(t) {}
};

//Function to generate random loot from 
void generateLoot(Player &player, vector<Weapon> weapon, vector<Armor>armor, vector<Potion>potion) {
	Weapon choosenWeapon;
	Armor choosenArmor;
	Potion choosenPotion;
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			std::random_device rd; // obtain a random number from hardware
			std::mt19937 gen(rd()); // seed the generator
			std::uniform_int_distribution<> distr(0, weapon.size() - 1); // define the range
			int rand_num = distr(gen);
			choosenWeapon = weapon[rand_num];
			cout << "-----------------------------------------" << endl;
			cout << i + 1 << ". " << weapon[rand_num].name << endl;
			cout << weapon[rand_num].description << endl;
			cout << weapon[rand_num].type << endl;
			cout << weapon[rand_num].rarity << endl;
			cout << weapon[rand_num].minDamage << " - " << weapon[rand_num].maxDamage << " DMG" << endl;
		}
		else if (i == 1) {
			std::random_device rd; // obtain a random number from hardware
			std::mt19937 gen(rd()); // seed the generator
			std::uniform_int_distribution<> distr(0, armor.size() - 1); // define the range
			int randomNum = distr(gen);
			choosenArmor = armor[randomNum];
			cout << "-----------------------------------------" << endl;
			cout << i + 1 << ". " << armor[randomNum].name << endl;
			cout << armor[randomNum].description << endl;
			cout << armor[randomNum].type << endl;
			cout << armor[randomNum].rarity << endl;
			cout << armor[randomNum].resistanceTypeStr << ": " << armor[randomNum].value << endl;
		}
		else {
			std::random_device rd; // obtain a random number from hardware
			std::mt19937 gen(rd()); // seed the generator
			std::uniform_int_distribution<> distr(0, potion.size() - 1); // define the range
			int randomNum = distr(gen);
			choosenPotion = potion[randomNum];
			cout << "-----------------------------------------" << endl;
			cout << i + 1 << ". " << potion[randomNum].name << endl;
			cout << potion[randomNum].description << endl;
			cout << potion[randomNum].type << endl;
			cout << potion[randomNum].rarity << endl;
			cout << potion[randomNum].effectStr << ": " << potion[randomNum].effectValue << endl;
		}

	}
	int choice;
	while (true) {
		cout << "Choose option" << endl;
		cin >> choice;
		//Wrong input
		if (cin.fail()) {
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Wrong input! Try again." << endl;
		}
		else if (choice == 1) {
			player.takeWeapon(choosenWeapon);
			break;
		}
		else if(choice == 2) {
			player.takeArmor(choosenArmor);
			break;
		}
		else if (choice == 3) {
			player.takePotion(choosenPotion);
			break;
		}
		else {
			cout << "Wrong input! Try again." << endl;
		}
	}
}

void startFight(Player &player, Dragon &dragon) {
	while (player.isAlive() == true && dragon.isAlive() == true) {
		std::system("CLS");
		//Fight info
		cout << "Player: " << player.name << endl;
		player.showHealth();
		player.showMana();
		cout << endl;
		cout << dragon.name << endl;
		dragon.showHealth();
		cout << endl;

		//Show player options
		cout << "Choose option" << endl;
		cout << "1 -> Attack dragon" << endl;
		cout << "2 -> Show inventory" << endl;
		cout << "3 -> Use potion" << endl;
		int choice;
		bool isAttack = false;
		while (!isAttack) {
			cin >> choice;
			//Check input
			if (cin.fail()) {
				cin.clear(); // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "Wrong input! Try again." << endl;
			}
			//Deal damage
			else if (choice == 1) {
				std::system("CLS");
				while (true) {
					cout << "Choose option" << endl;
					cout << "1 -> Basic attack" << endl;
					cout << "2 -> Use spell" << endl;
					cout << "0 -> Leave" << endl;
					cin >> choice;
					//Wrong input
					if (cin.fail()) {
						cin.clear(); // Clear the error flag
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
						cout << "Wrong input! Try again." << endl;
					}
					//Basic attack
					else if (choice == 1) {
						int playerDamage = player.dealDamage();
						dragon.takeDamage(playerDamage);
						cout << "You dealt " << playerDamage << "DMG to " << dragon.name << endl;
						std::system("PAUSE");

						int dragonDamage = dragon.dealDamage();
						player.takeDamage(dragonDamage, dragon.type);
						std::system("PAUSE");

						//Checking dot effect
						if (dragon.dotInfo[0] > 0) {
							dragon.checkDot();
							std::system("PAUSE");
							std::system("CLS");
						}

						//Add mana
						if (player.mana < 10) {
							player.mana += 2;
						}

						isAttack = true;
						break;
					}
					//Spells
					else if (choice == 2) {
						cout << "Current mana: " << player.mana << endl;
						player.showSkills();
						while (true) {
							cout << "----------------------------" << endl;
							cout << "Choose option: " << endl;
							cin >> choice;
							//Wrong input
							if (cin.fail()) {
								cin.clear(); // Clear the error flag
								cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
								cout << "Wrong input! Try again." << endl;
							}
							else if (0 <= choice - 1 && choice - 1 < player.skills.size()) {
								//Checking players mana
								if (player.mana >= player.skills[choice - 1].manaCost) {
									player.useSkill(player.skills[choice - 1], dragon);
									std::system("PAUSE");

									int dragonDamage = dragon.dealDamage();
									player.takeDamage(dragonDamage, dragon.type);
									std::system("PAUSE");

									//Checking dot effect
									if (dragon.dotInfo[0] > 0) {
										dragon.checkDot();
										std::system("PAUSE");
										std::system("CLS");
									}

									isAttack = true;
									break;
								}
								else {
									cout << "You don't have enough mana for this spell! Try again" << endl;
								}
							}
							else if (choice == 0) {
								isAttack = true;
								break;
							}
						}
						break;
					}
					else if (choice == 0) {
						isAttack = true;
						break;
					}
					else {
						cout << "Wrong imput! Try again." << endl;
					}
				}
			}
			//Show inventory
			else if (choice == 2) {
				std::system("CLS");
				while (true) {
					cout << "Choose option" << endl;
					cout << "1 -> Weapons" << endl;
					cout << "2 -> Armors" << endl;
					cout << "3 -> Potions" << endl;
					cout << "0 -> Leave" << endl;
					cin >> choice;
					//Wrong input
					if (cin.fail()) {
						cin.clear(); // Clear the error flag
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
						cout << "Wrong input! Try again." << endl;
					}
					//Show weapons
					else if (choice == 1) {
						cout << "Active weapon: " << player.activeWeapon.name << endl << endl;
						cout << "Players weapons: " << endl;
						cout << "0 -> Leave" << endl;
						player.showWeapons();
						cout << "Choose option" << endl;
						while (true) {
							cin >> choice;
							//Wrong input
							if (cin.fail()) {
								cin.clear(); // Clear the error flag
								cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
								cout << "Wrong input! Try again." << endl;
							}
							else if (0 <= choice - 1 && choice - 1 < player.weapons.size()) {
								player.setActiveWeapon(player.weapons[choice-1]);
								cout << "You set " << player.weapons[choice - 1].name << " as your main weapon." << endl;
								std::system("PAUSE");
								std::system("CLS");
								break;
							}
							else if (choice == 0) {
								std::system("CLS");
								break;
							}
							else {
								cout << "Wrong input! Try again." << endl;
							}
						}
					}
					//Show armors
					else if (choice == 2) {
						cout << "Active armor: " << player.activeArmor.name << endl << endl;
						cout << "Players armors: " << endl;
						cout << "0 -> Leave" << endl;
						player.showArmors();
						cout << "Choose option" << endl;
						while (true) {
							cin >> choice;
							//Wrong input
							if (cin.fail()) {
								cin.clear(); // Clear the error flag
								cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
								cout << "Wrong input! Try again." << endl;
							}
							else if (0 <= choice - 1 && choice - 1 < player.armors.size()) {
								player.setActiveArmor(player.armors[choice - 1]);
								cout << "You set " << player.armors[choice - 1].name << " as your main armor." << endl;
								std::system("PAUSE");
								std::system("CLS");
								break;
							}
							else if (choice == 0) {
								std::system("CLS");
								break;
							}
							else {
								cout << "Wrong input! Try again." << endl;
							}
						}
					}
					//Show potions
					else if (choice == 3) {
						if (player.potions.size() > 0) {
							cout << "Players potions: " << endl;
							player.showPotions();
							std::system("PAUSE");
							std::system("CLS");
						}
						else {
							cout << "You don't have any potions." << endl;
							std::system("PAUSE");
							std::system("CLS");
						}
					}
					else if (choice == 0) {
						break;
					}
				}
				break;
			}
			//Use potion
			else if (choice == 3) {
				if (player.potions.size() > 0) {
					cout << "Players potions: " << endl;
					cout << "0 -> Leave" << endl;
					player.showPotions();
					cout << "Choose option " << endl;
					while (true) {
						cin >> choice;
						//Wrong input
						if (cin.fail()) {
							cin.clear(); // Clear the error flag
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
							cout << "Wrong input! Try again." << endl;
						}
						else if (0 <= choice - 1 && choice - 1 < player.potions.size()) {
							player.usePotion(player.potions[choice - 1], dragon);
							if ((player.potions[choice - 1].effect == 1)) {
								cout << "You have restored " << player.potions[choice - 1].effectValue << " health" << endl;
							}
							else {
								cout << "You dealt " << player.potions[choice - 1].effectValue << " DMG" << endl;
							}
							player.removePotion(choice);
							std::system("PAUSE");
							break;
						}
						else if (choice == 0) {
							break;
						}
						else {
							cout << "Wrong input! Try again." << endl;
						}
					}
					break;
				}
				else {
					cout << "You don't have any potions." << endl;
					std::system("PAUSE");
					break;
				}
			}
			else {
				cout << "Wrong input! Try again." << endl;
			}
		}
	}
	if (player.isAlive()) {
		cout << "Congratulations you defeated " << dragon.name << endl;
		cout << "You earned 100 xp" << endl;
		player.exp += 100;
		player.checkExp();
		system("PAUSE");
		system("CLS");
		cout << "Choose one new item" << endl;
	}
	else {
		cout << "You died!" << endl;
	}
}

int main()
{
	//Creating oponents
	Dragon northGateDragon("Ignis", 1, 100, 3, 6);
	Dragon southGateDragon("Blazara", 2, 75, 4, 5);
	Dragon humanDragon("Ashenwing", 3, 100, 6, 9);
	Dragon legendaryDragon("the Lord of Ember", 1, 150, 6, 9);

	//Creating items
	vector<Weapon> weaponsList = {	Weapon("Aqua Blade", "Test sword description", "Rare", "Weapon", 10, 15),
								Weapon("Hydro Cannon", "Test sword description", "Rare", "Weapon", 5, 20),
								Weapon("Tsunami Hammer", "Test sword description", "Rare", "Weapon", 7, 18),
								Weapon("Wave Pike", "Test sword description", "Rare", "Weapon", 9, 16),
								Weapon("Mist Bow", "Test sword description", "Epic", "Weapon", 10, 30),
								Weapon("Geyser Spear", "Test sword description", "Epic", "Weapon", 19, 21),
								Weapon("Abyssal Trident", "Test sword description", "Legendary", "Weapon", 15, 40),
								};
	vector<Armor> armorsList = { Armor("Aqua Guard Armor", "Test armor description", "Rare", "Armor", 5, 1),
								Armor("Hydro Cloak", "Test armor description", "Rare", "Armor", 5, 1),
								Armor("Abyss Mantle", "Test armor description", "Rare", "Armor", 5, 2),
								Armor("Cascade Plate Armor", "Test armor description", "Rare", "Armor", 5, 3),
								Armor("Wave Scale Armor", "Test armor description", "Epic", "Armor", 7, 4),
								Armor("Tidal Retardant Suit", "Test armor description", "Epic", "Armor", 7, 2),
								Armor("Tidebreaker Suit", "Test armor description", "Legnedary", "Armor", 10, 1) 
								};
	vector<Potion> potionsList = { Potion("Health potion", "test description", "Rare", "Potion", 1, 10),
									Potion("Damage potion", "test potion", "Rare", "Potion", 2, 15),
									Potion("Lesser healing potion", "test description", "Basic","Potion", 1, 5),
									Potion("Lesser damage potion", "test description", "Basic", "Potion", 2, 10),
									Potion("Big healing potion", "test description", "Epic", "Potion", 1, 15), 
									Potion("Big damage potion", "test description", "Epic", "Potion", 2, 20), 
									Potion("Huge damage potion", "test description", "Legendary", "Potion", 1, 20), 
									Potion("Huge damage potion", "test description", "Legendary", "Potion", 2, 25), };
	

	//Creating nodes
	Node* talkWithEdward = new Node({ "Edward:\nHi my name is Edward and I am a leader of 'Wing of Fire Brigade'\nTomorrow we are going to Pyrofield. It's a small village. People from there need our help!\nDon't be late" });
	talkWithEdward->choices = { "1. Don't worry, I'm never late", "2. Ok" };


	Node* attackOnCity = new Node({ "Edward:\nWake up! Dragons are attacking the City!",
									"You:\nWhat? How is it possible?",
									"Edward:\nI don't know. We have to hurry. We have to protect the North and South Gates\nChoose which one you want to protect and I will go to the other one." });
	attackOnCity->choices = { "1 -> Go to the North Gate", "2 -> Go to the South Gate" };


	Node* northGate = new Node({ "You have arrived to North Gate and you see injured soldier", 
								"You:\nHey, is everything ok?",
								"Soldier:\nDon't worry about me. You have to be careful, there is still one dragon left\nAfter you defete him I will tell you what happend here",
								"You:\nFine..." });
	northGate->dragon = northGateDragon;
	northGate->choices = { "\nAfter the fight, the soldier told you that he saw dragons being summoned by some of the city's inhabitants\n1 -> Go back and meet with Edward" };

	Node* southGate = new Node({ "You have arrived to North Gate and you see a piece of paper",
								"You:\nGuess I will take a look, it looks suspicious...",
								"You wanted to take a look but suddenly arrived",
								"You:\nWhat a pain. I guess I will check it after killing you" });
	southGate->dragon = southGateDragon;
	southGate->choices = { "\nAfter the fight, he decided to check the piece of paper he had found earlier. It was a map with a nearby mountain peak marked on it\n1 -> Go back and meet with Edward" };

	Node* meetWithEdward = new Node({ "Edward:\nHey kid I see you are still alive. Good job.\n",
									"You:\nThanks boss. I found out new information about this dragon attack\n",
									"You told edward what you know\n",
									"Edward: \nThats interesting... \n",
									"You:\nSo, what should we do now?\n",
									"Edward:\nWe have to do two thing. Investigate the city and explore the mountains.\nBecause of how well you did, I'll let you choose what you want to do\n"});
	meetWithEdward->choices = { "1. Investigate the city", "2. Explore the mountains" };

	Node* invesitgateCity = new Node({ "You started exploring the city and noticed a suspicious man. It turned out that this man was responsible for the dragon attack.\nYou decided to defeat him to save the city, but he suddenly turned into a dragon\n" });
	invesitgateCity->dragon = humanDragon;
	invesitgateCity->choices = { "Press 1 to continue" };

	Node* exploreMountains = new Node({ "You went to the mountains to explore. At first you didn't know what to look for, \nbut suddenly you noticed a strange dark power emerging from the peak. When you reached the top,\nyou saw that the source of energy was the Lord of Ember, considered a legendary dragon\n",
										"You decided to save the city and defeat the source of evil energy"});
	exploreMountains->dragon = legendaryDragon;
	exploreMountains->choices = { "1. Come back to Pyroklas" };

	Node* betrayInCity = new Node({ "After you defeat the suspicious man, it turns out that he was a citizen of Pyroklas.\nHe was dissatisfied with the current government and decided to change it by teaming up the Lord of Ember.",
									"Two months have passed since the great battle with the dragons,\nand the city still feels the effects of the fighting.The dragons still attack the city,\nbut very rarely,and you continue to protect it" });

	Node* defeteOfLegendaryDragon = new Node({"You defeated the legendary dragon and the energy coming from the mountains disappeared.\nIt turned out that it was this energy that controlled the dragons.\nThe city is at peace, the dragons are not attacking,\nbut you still sense a threat in the city"});

	Node* secretEnding = new Node({ "You defeated both the legendary dragon and the city traitor. Thanks to your actions, \nthe city is safe and was quickly rebuilt. Additionally, dragons stopped attacking people" });

	talkWithEdward->nextNodes = { attackOnCity, attackOnCity };
	attackOnCity->nextNodes = { northGate, southGate };
	northGate->nextNodes = { meetWithEdward};
	southGate->nextNodes = { meetWithEdward};
	meetWithEdward->nextNodes = { invesitgateCity, exploreMountains };
	invesitgateCity->nextNodes = { betrayInCity };
	exploreMountains->nextNodes = { defeteOfLegendaryDragon };
	betrayInCity->nextNodes = {};
	/*
	Node* starTutorial = new Node({ "You started a tutorial" });
	starTutorial->dragon = tutorialDragon;

	Node* skipTutorial = new Node({ "You skipped a tutorial" });
	

	//Defining choices
	talkWithEdward->choices = { "1 -> Yes sure, you can count on me", "2 -> Don't worry boss, I'm never late" };
	talkWithEdward->nextNodes = { starTutorial, skipTutorial };
	*/



	Game game;
	int gameOn;

	//Game menu
	gameOn = game.menu();

	// Variables to track the player's path
	bool northGateChosen = false;
	bool southGateChosen = false;


	//Game start
	if (gameOn == 1) {
		std::system("CLS");

		//Creating character with basic items
		cout << "Type your character name: " << endl;
		string name;
		cin >> name;

		Player player(name);
		Weapon startingWeaopn("Hand", "Use your bare hands to fight dragons", "None", "Weapon", 1, 5);
		player.activeWeapon = startingWeaopn;
		player.takeWeapon(startingWeaopn);

		Armor startingArmor("Noraml shirt", "Just a normal shirt", "None", "Armor", 1, 1);
		player.activeArmor = startingArmor;
		player.takeArmor(startingArmor);

		Potion basicHealingPotion("Basic Healing Potion", "Basic healing potion which heals you", "Basic", "Potion", 1, 10);
		player.takePotion(basicHealingPotion);
		Potion basicDamagePotion("Basic Damage Potion", "Basic damage potion which deals damage to dragons", "Basic", "Potion", 2, 10);
		player.takePotion(basicDamagePotion);

		Skill waterBolt("Water Bolt", 5, "Throw a Water Bolt to deal magic damage", 15, 1);
		player.takeSkill(waterBolt);
		Skill waterBlessing("Water Blessing", 7, "Create a blessed water to heal yourself", 5, 2);
		player.takeSkill(waterBlessing);
		Skill waterCurse("Water Curse", 8, "Curse dragon to deal damage over time", 10, 3);
		player.takeSkill(waterCurse);

		std::system("CLS");
		game.gameStart(name);
		std::system("CLS");

		//Staring node
		Node* currentNode = talkWithEdward;

		while (currentNode != nullptr) {
			std::system("CLS");

			for (int i = 0; i < currentNode->texts.size(); i++) {
				cout << currentNode->texts[i] << endl;
			}
			

			if (currentNode->dragon.name.empty()) {
				//No fight
			}
			else {
				std::system("PAUSE");
				startFight(player, currentNode->dragon);
				if (!player.isAlive()) {
					break;
				}
				else {
					generateLoot(player, weaponsList, armorsList, potionsList);
				}
			}

			// Check if we need to add extra choices
			if (currentNode == invesitgateCity) {
				if (southGateChosen) {
					currentNode->choices.push_back("2. Go check the mountains (information from piece of paper)");
					currentNode->nextNodes.push_back(exploreMountains);
					exploreMountains->nextNodes[0] = secretEnding;
				}
			}
			else if (currentNode == exploreMountains) {
				if (northGateChosen) {
					currentNode->choices.push_back("2. Investigate city (information from soldier)");
					currentNode->nextNodes.push_back(invesitgateCity);
					invesitgateCity->nextNodes[0] = secretEnding;
				}
			}

			if (currentNode->choices.empty()) {
				break; // Game end, no more choises
			}

			//Show choices
			for (size_t i = 0; i < currentNode->choices.size(); i++) {
				cout << i + 1 << ". " << currentNode->choices[i] << endl;
			}

			//User choice
			int choice;

			//Checking if user input in an integer and in good range
			while (true) {
				cin >> choice;
				if (cin.fail()) {
					cin.clear(); // Clear the error flag
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
					cout << "Wrong input! Try again." << endl;
					std::system("PAUSE");
				}
				else {
					if (choice > 0 && choice <= currentNode->choices.size()) {
						if (currentNode == attackOnCity) {
							if (choice == 1) {
								northGateChosen = true;
							}
							else if (choice == 2) {
								southGateChosen = true;
							}
						}
						currentNode = currentNode->nextNodes[choice - 1];
						break;
					}
					else {
						cout << "Wrong input, try again." << endl;
						std::system("PAUSE");
					}
				}
			}
		}

		cout << "Game Over" << endl;

	}







}

