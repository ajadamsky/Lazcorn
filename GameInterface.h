//
// Created by Sondre on 19.10.2017.
//

#pragma once

#ifndef LAZCORN_GAMEINTERFACE_H
#define LAZCORN_GAMEINTERFACE_H

#include "machine.h"
#include "Object.h"
#include <list>


class GameInterface{
public:
    GameInterface();
    void update();
    std::list<Object*> UI_Objects;
    std::list<sf::Text*> texts;
    std::list<Object*> GetObjects();
    std::list<sf::Text*> GetLabels();
    sf::Texture hud_main;
    sf::Text moneyLabel;
    sf::Text scoreLabel;
    sf::Texture hp_bar;
    sf::Texture energy_bar;
    sf::Texture frames;

    sf::Texture priWeapon;
    sf::Texture secWeapon_1;
    sf::Texture secWeapon_2;

    sf::Texture* priWeapon_tx_ptr;
    sf::Texture* secWeapon_1_tx_ptr;
    sf::Texture* secWeapon_2_tx_ptr;

    Object* primary_weapon_ptr;
    Object* secondary_weapon_1_ptr;
    Object* secondary_weapon_2_ptr;

    void setHealthPercentage(float percentage);
    void setEnergyPercentage(float percentage);

    void setMoney(int money);

    void setScore(int score);
};


#endif //LAZCORN_GAMEINTERFACE_H
