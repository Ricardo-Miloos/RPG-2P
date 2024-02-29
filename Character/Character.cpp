//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
Character::Character(string _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    name = _name;
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}
void Character::defend() {
    // Incrementar la defensa en un 20% solo por el turno actual
    defense = static_cast<int>(defense * 1.2);
    isDefending = true;
}

//restablecer la defensa al valor original al inicio de cada turno
void Character::resetDefense() {
    defense = static_cast<int>(defense / 1.2);
    isDefending = false;
}


string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}
int Character::getMaxHealth() {
    return maxHealth;
}
int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}


string Character::toString() {
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}