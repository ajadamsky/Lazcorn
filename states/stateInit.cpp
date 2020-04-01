#include <iostream>
#include "stateInit.h"
#include "../machine.h"
#include "../game.h"

void StateInit::GoNext(Machine &machine, sf::RenderWindow* window) {
    std::cout << "Init" << std::endl;
    machine.SetState(Machine::StateId::MENU);
}
