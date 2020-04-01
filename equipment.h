//
// Created by Sondre on 13.11.2017.
//

#ifndef LAZCORN_EQUIPMENT_H
#define LAZCORN_EQUIPMENT_H

#include "Object.h"
#include "SFML/Graphics.hpp"

class equipment : public Object{
public:
    std::string Name;
    float BaseDamage = 0;
    int Level = 1;
    float UpgradeCost = 0;
    float UpgradeScale = 0;
    float FireRate = 0.0f;
    Object* projectile;
    equipment(float fire_rate, Object* Projectile, sf::Texture* equipmentTexture);
    void shoot(equipment* weapon, sf::Vector2f velocity);

    sf::Clock clock;
    float lastFired = 0;
};


#endif //LAZCORN_EQUIPMENT_H
