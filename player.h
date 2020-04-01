//
// Created by Sondre on 23.10.2017.
//

#ifndef LAZCORN_PLAYER_H
#define LAZCORN_PLAYER_H


#include "Object.h"
#include "vector"
#include "equipment.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class player : public Object{
public:
    player();
    player(int x, int y, int health);
    void ProcessEvents(sf::RenderWindow* window,float deltatime);
    float playerSpeed = 400;
    sf::Texture player_texture;
    void moveOverride() override;
    equipment* weapons[3];
    std::vector<Object*> projectiles;
    void shoot(equipment* weapon, sf::Vector2f velocity);
    sf::SoundBuffer buffer;
    sf::Sound sound;
    float Energy = 100;
    float MaxEnergy = 100;

    bool Player_can_fire = true;
};


#endif //LAZCORN_PLAYER_H
