//
// Created by Sondre on 20.11.2017.
//

#include "gameConfig.h"

sf::Texture ammo1;
sf::Texture rocket1;
sf::Texture oblivirator1;
equipment* PlayerEquipment[3];
equipment* AvailableEquipment[3];
Object laser(0,0,1.0f,1.0f, &ammo1 , 10,20);
Object rocket(0,0,1.0f,1.0f,&rocket1,30,40);
Object oblivirator(0,0,1.0f,1.0f,&oblivirator1,2200,40);
int screenHeight = 800;
int screenWidth = 1200;
float GameDifficulty = 1;
float money = 0;
extern float EnergyRegeneratonRatio = 1;