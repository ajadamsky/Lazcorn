//
// Created by Sondre on 19.10.2017.
//

#ifndef LAZCORN_LEVEL_BASE_H
#define LAZCORN_LEVEL_BASE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics.hpp"
#include "../pathPoints.h"
//#include <experimental/random>
#include <random>
#include <list>
#include "../state.h"


class level_base{
public:
    level_base();

    void Update(float elapsedTime);

    sf::Texture bg1Tex;
    sf::RectangleShape bg1Shape;
    sf::RectangleShape bg2Shape;

    float bgSpeed;
    float bg1Y;
    float bg2Y;

private:

};


#endif //LAZCORN_LEVEL_BASE_H
