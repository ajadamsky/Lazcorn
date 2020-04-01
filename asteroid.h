//
// Created by Xoncry on 26.11.2017.
//

#ifndef LAZCORN_ASTEROID_H
#define LAZCORN_ASTEROID_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Object.h"
#include "randomGen.h"

class asteroid : public Object{
public:
    randomGen rand;

    asteroid();
    asteroid(int health, float xpos, float ypos);
    void ProcessEvents(sf::RenderWindow* window);

    sf::Texture asteroid_texture;

    float xpos;
    float ypos;

    int i = 0;


};


#endif //LAZCORN_ASTEROID_H
