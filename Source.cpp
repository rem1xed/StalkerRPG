#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

class Character {
private:

public:
    string name;
    int health;
    int lvl;
    vector<string> inventory; 

    Character(string n, int h) : name(n), health(h) {
        srand(time(NULL));
        lvl = rand() % 10 + 1;

        string items[] = { "Vodka", "Bandage", "Medkit", "Bread", "Ammo" };
        int numIt = sizeof(items) / sizeof(items[0]);

        for (int i = 0; i < 3; i++) {
            int randIndex = rand() % numIt;
            inventory.push_back(items[randIndex]);
        }
    }

    void removeItem(const string& item) {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (*it == item) {
                inventory.erase(it);
                break;
            }
        }
    }

};

class Location {
private:
    string name;
    string description;
    bool hasQuest;
    bool hasEnemies;
    friend class Map;

public:
    Location(string n, string d, bool hq, bool he) : name(n), description(d), hasQuest(hq), hasEnemies(he) {}
};

class Map {
private:
    vector<Location> locations;

public:
    void addLocation(const Location& location) {
        locations.push_back(location);
    }

    void displayMap() const {
        for (const auto& loc : locations) {
            cout << "Location: " << loc.name << "\nDescription: " << loc.description << "\n";
        }
    }
};

class Enemy {
private:

public:
    string name;
    int health;
    int attack;
    friend class Character;
    friend void fightEnemy(Enemy& enemy, Character& character);

    Enemy(string n, int h, int a) : name(n), health(h), attack(a) {}
    static vector<Enemy> enemies;
};

vector<Enemy> Enemy::enemies = { Enemy("Mutant", 35, 15) };

void fightEnemy(Enemy& enemy, Character& player);

void fightEnemy(Enemy& enemy, Character& player) {
    cout << "You encounter a " << enemy.name << ". Prepare for battle!\n";
    cout << "Your health: " << player.health << "\tEnemy health: " << enemy.health << endl;

    while (player.health > 0 && enemy.health > 0) {
        cout << "Choose your action:\n";
        cout << "1. Attack\n";
        cout << "2. Use medkit\n";
        cout << "Your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            int damage = rand() % 10 + 1;
            cout << "You attack the " << enemy.name << " for " << damage << " damage.\n";
            enemy.health -= damage;

            if (enemy.health <= 0) {
                cout << "You defeated the " << enemy.name << "!\n";
                break;
            }

            damage = enemy.attack - (rand() % 5 + 1);
            cout << "The " << enemy.name << " attacks you for " << damage << " damage.\n";
            player.health -= damage;

            if (player.health <= 0) {
                cout << "You have been defeated.\n";
                break;
            }
        }
        break;

        case 2:
            if (!player.inventory.empty()) { 
                cout << "You used a " << player.inventory[0] << ".\n";
                if (player.health <= 70)
                {
                    player.removeItem(player.inventory[0]);
                    player.health += 30;
                }
                if (player.health > 70 && player.health < 100)
                {
                    player.removeItem(player.inventory[0]);
                    player.health += (100 - player.health);
                }
                else
                {
                    cout << "You're not injured yet";
                }

                 
            }
            else {
                cout << "Your inventory is empty.\n";
            }
            break;

        default:
            cout << "Invalid choice. Please choose again.\n";
            break;
        }

        cout << "Your health: " << player.health << "\tEnemy health: " << enemy.health << endl;
    }
}

void main() {
    cout << "Welcome to the Zone, Stalker.\n";
    Sleep(4000);
    cout << "Your mission is to survive and find out the secrets hidden within Chernobyl's Exclusion Zone.\n";
    Sleep(4000);
    cout << "Be wary of mutants and anomalies lurking in the darkness.\n"; 
    Sleep(4000);
    system("CLS");
    Character player("Strelok", 100);
    Map locations;
    vector<Location> locsList = {
        Location("Rookie Village", "A small village where rookies gather before their first expedition into the Zone.", true, true),
        Location("Dead City", "A city once filled with life, now overrun by mutants and bandits.", false, true),
        Location("Yantar", "A research outpost studying the Zone's anomalies.", true, false)
    };

    for (const auto& loc : locsList) {
        locations.addLocation(loc);
    }

    cout << "You find yourself in the " << Enemy::enemies[0].name << " lair. Prepare for battle, Stalker!\n";

    fightEnemy(Enemy::enemies[0], player);

}

