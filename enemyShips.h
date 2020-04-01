//
// Created by BearMace on 06/11/2017.
//

#ifndef LAZCORN_ENEMYSHIPS_H
#define LAZCORN_ENEMYSHIPS_H


#include "Object.h"
#include "pathPoints.h"
#include "equipment.h"
#include <cmath>
#include <iostream>
#include <random>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


class enemyShips    :   public Object
{
public:
    enemyShips();
    enemyShips(int x, int y, int health,int target,int number);

    std::default_random_engine el{std::random_device{}()};
    std::uniform_int_distribution<int>spawn{0,4};
    std::uniform_int_distribution<int>targetPoint{4,10};

    int PathNumber;
    int PathCount=0;
    int target;
    int range = 50;
    int targetRange = 5;
    void ProcessEvents(sf::RenderWindow* window);
    std::vector<Object*> projectiles;
    sf::Texture enemy_texture;

    sf::RectangleShape* HealthBarBackground = new sf::RectangleShape();
    sf::RectangleShape* HealthBar = new sf::RectangleShape();

    sf::Texture HealthBarBackgroundTexture;
    sf::Texture HealthBarTexture;

    int bound = 0;
    bool exit = false;


    sf::Texture* Project_Texture;
    float fireRate;

    sf::SoundBuffer buffer;
    sf::Sound sound;

    equipment* weapons[1];

    bool EnemyFire = true;
    bool can_fire = false;

    void Enemy_fire(float time);

    void shoot(equipment* weapon, sf::Vector2f velocity);
    //enemy movement
    int enemymovement(enemyShips* enemy,float time,pathPoints* PP,sf::Vector2f Player,int PlayerWidth, std::vector<Object*> *Bulllet_list);

    void setpos(int x, int y){
        this->rect.setPosition(x, y);
    }

    bool Out_bound = false;

    void moveOverride() override;

};


#endif //LAZCORN_ENEMYSHIPS_H
