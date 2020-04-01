#include <iostream>

#include "stateExit.h"
#include "../machine.h"

void StateExit::GoNext(Machine &machine, sf::RenderWindow* window){
    std::cout << "Exit" << std::endl;
    machine.SetRunning(false);
}