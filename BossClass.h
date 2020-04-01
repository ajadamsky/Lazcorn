//
// Created by BearMace on 27/11/2017.
//

#ifndef LAZCORN_BOSSCLASS_H
#define LAZCORN_BOSSCLASS_H

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Object.h"
#include "gameConfig.h"
#include <list>




class BossClass : public Object {
public:
    BossClass();
    BossClass(int x, int y, int health,sf::Texture* BossPic,sf::Texture* Bullet,float Boss_Fire_Rate);

    sf::Texture Boss_texture;
    sf::Texture* Project_Texture;
    sf::Texture Explotion;

    equipment* weapons[3];
    void shoot(equipment* weapon, sf::Vector2f velocity);
    std::vector<Object*> projectiles;
    void moveOverride() override;

    sf::RectangleShape* HealthBarBackground = new sf::RectangleShape();
    sf::RectangleShape* HealthBar = new sf::RectangleShape();

    sf::Texture HealthBarBackgroundTexture;
    sf::Texture HealthBarTexture;

    float fireRate;
    bool can_fire = false;
    sf::SoundBuffer buffer;
    sf::Sound sound;

    int range = 100;

    bool BossEntering = true;
    bool BossFire = false;


    void Boss_fire(float time);
    void Bossmovment(float time,sf::Vector2f Player,int PlayerWidth,std::vector<Object*> *Bullet_list);
    bool BossExplotion(Object*,sf::SoundBuffer &buffer,sf::Sound &Explotion_Enemy,int x, int y);
    int offset = 125;
    bool directionRight = true;
};



#endif //LAZCORN_BOSSCLASS_H
