#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"

int main() {
    Player *player = new Player("Santi", 69, 15, 3, 10);
    Enemy *enemy = new Enemy("Mike", 69, 15, 8, 10, 10);

    cout << player->toString() << endl;
    cout << enemy->toString() << endl;

    cout << "=====================" << endl;

    bool alive = true;
    while (true) {

        player->doAttack(enemy);
        enemy->doAttack(player);

        // Mostrar estado después de cada turno
        cout << "=====================" << endl;
        cout << "Player's Turn:" << endl;
        cout << player->toString() << endl;

        cout << "=====================" << endl;
        cout << "Enemy's Turn:" << endl;
        cout << enemy->toString() << endl;

        // Verificar si alguno de los personajes tiene vida menor o igual a cero
        if (player->getHealth() <= 0 || enemy->getHealth() <= 0) {
            alive = false;
            break;
        }
    }

    // Resultado después de la batalla
    cout << "*************************" << endl;
    if (player->getHealth() <= 0 ) {
        cout << "Game Over, " << enemy->getName() << " has won the game." << endl;
    } else {
        cout << "Game Over, " << player->getName() << " has won the game." << endl;
    }

    cout << "\nStats after fight: " << endl;
    cout << player->toString() << endl;
    cout << enemy->toString() << endl;

    delete player;
    delete enemy;
    return 0;

};