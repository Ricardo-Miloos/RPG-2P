//
// Created by Victor Navarro on 19/02/24.
//

#include "Combat.h"
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdlib>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player *) participant);
        } else {
            enemies.push_back((Enemy *) participant);
        }
    }
}

Combat::Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants = vector<Character*>();
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()){
        partyMembers.push_back((Player*) participant);
    } else {
        enemies.push_back((Enemy*) participant);
    }
}

void Combat::combatPrep() {
    // Sort participants by speed
    sort(participants.begin(), participants.end(), compareSpeed);
}
void Combat::displayHealth() {
    cout << "Players stats:" << endl;
    for (Character* character : participants) {
        cout << character->getName() << ": " << character->getHealth() << " HP" << endl;
    }
        cout << "===========================" << endl;
    }

string Combat::toString() {
    string result = "";
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        result += (*it)->toString() + "\n";
    }
    cout<<"===================="<<endl;
    return result;
}

Character* Combat::getTarget(Character* attacker) {
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        if((*it)->getIsPlayer() != attacker->getIsPlayer()){
            return *it;
        }
    }
    //TODO: Handle this exception
    return nullptr;
}

void Combat::doCombat() {
    cout << "The combat begins!" << endl;
    displayHealth();
    combatPrep();

    while (!partyMembers.empty() && !enemies.empty()) {
        for (auto it = participants.begin(); it != participants.end();) {
            Character *target = nullptr;

            if ((*it)->getIsPlayer()) {
                displayHealth();
                // Opción para el jugador: atacar o defenderse
                int choice;
                cout << "Player: " << (*it)->getName() << ". Would you like to use attack (1) or defense (2)? ";
                cin >> choice;
                if (choice == 1) {
                    target = ((Player *)*it)->selectTarget(enemies);
                } else if (choice == 2) {
                    // El jugador decide defenderse
                    (*it)->defend();
                    cout << "You are using defense this turn." << endl;
                } else {
                    cout << "Invalid option, assuming attack." << endl;
                    target = ((Player *)*it)->selectTarget(enemies);
                }
            } else {
                // Enemigo decide si defenderse
                if (((Enemy *)*it)->getHealth() < 0.15 * ((Enemy *)*it)->getMaxHealth() && (rand() % 100) < 80) {
                    ((Enemy *)*it)->defend();
                    cout << "The enemy " << (*it)->getName() << " is using defense." << endl;
                } else {
                    target = ((Enemy *)*it)->selectTarget(partyMembers);
                }
            }
            if (target) {

            (*it)->doAttack(target);




                if (target->getHealth() <= 0) {
                it = participants.erase(remove(participants.begin(), participants.end(), target), participants.end());
                if (target->getIsPlayer()) {
                    partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), target), partyMembers.end());
                    if (partyMembers.size() == 0) {
                        cout << "Game Over" << endl;
                        return;
                    }
                } else {
                    cout << "You killed enemy " << target->getName() << "!" << endl;
                    enemies.erase(remove(enemies.begin(), enemies.end(), target), enemies.end());
                    if (enemies.size() == 0) {
                        cout << "Victory" << endl;
                        return;
                    }
                }
            } else {
                it++;
            }
        }
    }
}}
