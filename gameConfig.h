//
// Created by Sondre on 19.10.2017.
//
#pragma once

#ifndef LAZCORN_GAMECONFIG_H
#define LAZCORN_GAMECONFIG_H

#include "equipment.h"
#include "SFML/Graphics.hpp"

#endif //LAZCORN_GAMECONFIG_H

// 0 = Primary
// 1 = Secondary
// 2 = Secondary
extern equipment* PlayerEquipment[3];
extern equipment* AvailableEquipment[3];


//Projectiles
extern Object laser;
extern Object rocket;
extern Object oblivirator;

extern int screenHeight;
extern int screenWidth;
extern float money;
extern float GameDifficulty;
extern float EnergyRegeneratonRatio;

extern sf::Texture ammo1;
extern sf::Texture rocket1;
extern sf::Texture oblivirator1;

class gameConfig {
public:

};
