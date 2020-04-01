#ifndef LAZCORN_STATE_H
#define LAZCORN_STATE_H
#include <SFML/Graphics/RenderWindow.hpp>

class Machine;

class State{
public:
    State() {}
    virtual ~State() {};
    virtual void GoNext(Machine &context, sf::RenderWindow* window) = 0;
    virtual void draw(sf::RenderWindow* window) {}
};

#endif //LAZCORN_STATE_H
