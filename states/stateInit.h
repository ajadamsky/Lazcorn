#ifndef LAZCORN_STATEINIT_H
#define LAZCORN_STATEINIT_H

#include "../state.h"

class StateInit : public State{
public:
    void GoNext(Machine &machine, sf::RenderWindow* window);

};


#endif //LAZCORN_STATEINIT_H
