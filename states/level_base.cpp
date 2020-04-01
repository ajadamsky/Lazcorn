//
// Created by Sondre on 19.10.2017.
//

#include <SFML/Graphics.hpp>
#include "level_base.h"

level_base::level_base() {

    bgSpeed = 0.5;

    bg1Tex.loadFromFile("BackGrounds/background2.jpg");
    bg1Tex.setSmooth(false);
    bg1Tex.setRepeated(true);

    bg1Shape.setSize(sf::Vector2f(1200, 810));
    bg1Shape.setPosition(0.0f, 0.0f);
    bg1Shape.setTexture(&bg1Tex);
    bg2Shape.setSize(sf::Vector2f(1200, 810));
    bg2Shape.setPosition(0.0f, -800.0f);
    bg2Shape.setTexture(&bg1Tex);

    bg1Y = bg1Shape.getPosition().y;
    bg2Y = bg2Shape.getPosition().y;

}
    void level_base::Update(float elapsedTime) {

        if (bg1Y < 800)
        {
            bg1Y += bgSpeed * elapsedTime;
        }
        else
        {
            bg1Y = -800;
        }
        if (bg2Y < 800)
        {
            bg2Y += bgSpeed * elapsedTime;
        }
        else
        {
            bg2Y = -800;
        }
        bg1Shape.setPosition(0, bg1Y);
        bg2Shape.setPosition(0, bg2Y);

}
