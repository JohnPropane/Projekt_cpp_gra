#include <iostream>


#pragma once

using namespace std;
class Game
{
public:
	Game(){}

    int menu() {
        cout << "The story of a legendary firefighter" << endl;
        cout << "Welcome to the game" << endl;
        cout << "Press 1 to play a new game" << endl;
        cout << "Press 2 to leave the game" << endl;
        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Wrong input! Try again." << endl;
            }
            else if (choice == 1 || choice == 2) {
                return choice;
            }
            else {
                cout << "Wrong input! Try again." << endl;
            }
        }
    }

    void gameStart(string name) {
        cout << "Welcome to a world where modern cities and towns exist in the shadow of ancient beasts.\nA world where dragons are not just a legend but a real threat.\nThey are mischievous and malevolent, loving fireand destruction, spreading chaos wherever they appear.\nIt is here, in the bustling city of Pyroklas, that your story begins." << endl;
        system("PAUSE");
        system("CLS");

        cout << "Your name is " << name << " and you are part of an elite group of firefighters known as the 'Wing of Fire Brigade',\nspecializing in combating fires caused by dragons and protecting the population." << endl;
    }

    int dialiogWihtBoss(string name) {
        string boss = "Edward";
        cout << boss << endl;
        cout << "Hi my name is " << boss << " and I am a leader of 'Wing of Fire Brigade'" << endl;
        cout << "Before we star our journey you can train fighing with dragon in our training camp" << endl;
        cout << "Do you wanna try?" << endl;

        cout << name << endl;
        cout << "Choose option: " << endl;
        cout << "1 -> Yes sure, show we where to go (start tutorial)" << endl;
        cout << "2 -> Nah, I'm good. I'm confident in my skills (skip tutorial)" << endl;
        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Wrong input! Try again." << endl;
            }
            else if (choice == 1) {
                cout << boss << endl;
                cout << "Come with me." << endl;
                return choice;
            }
            else if (choice == 2) {
                cout << boss << endl;
                cout << "Oh, so you are brave. This can get you into trouble in the future\nAnyway, tomorrow at 6am we are going to Hydropolis to help people fighting with real dragons.\nDon't be late" << endl;
                return choice;
            }
            else {
                cout << "Wrong input! Try again." << endl;
            }
        }
    }






};

