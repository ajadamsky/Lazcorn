#ifndef LAZCORN_STATEEXIT_H
#define LAZCORN_STATEEXIT_H

#include "../state.h"

class StateExit : public State{
 void GoNext(Machine &machine, sf::RenderWindow* window);
};


#endif //LAZCORN_STATEEXIT_H
