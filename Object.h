//
// Created by Sondre on 19.10.2017.
//

#ifndef LAZCORN_OBJECT_H
#define LAZCORN_OBJECT_H

#include <SFML/Audio/SoundBuffer.hpp>
#include "SFML/Graphics.hpp"

class Object{
public:
    Object();
    ~Object();

    sf::Vector2f velocity = sf::Vector2f(0, 0);
    sf::Vector2f Direction = sf::Vector2f(0,0);
    float speed =200;
    float health;
    float maxHealth;
    sf::RectangleShape rect;
    Object(int x, int y, float health, float maxHealth, sf::Texture* texture, int height, int width);

    Object* parent;

    sf::Texture* tx;
    sf::RectangleShape getShape();
    sf::Texture* ObjectTexture();


    void move();
    virtual void moveOverride();

    sf::Clock FireClock;
    sf::Clock Explotion_clock;

    bool can_fire = false;
    bool ExplotionClock_On = false;

    bool exploding_projetile = false;

    bool Explotion_animation(Object* EX,sf::SoundBuffer &buffer,sf::Sound &Explotion_Enemy,int x,int y);

    bool fireWeapon = false;
    float CollitionDamage = 0;


    void takeDamage(int damage);

    void Heal(int amount);

    void destroy();

    bool shouldDelete = false;
};


#endif //LAZCORN_OBJECT_H
