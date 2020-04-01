//
// Created by Xoncry on 26.11.2017.
//

#include <iostream>
#include "asteroid.h"


sf::Texture* asteroid_texture_ptr;

asteroid::asteroid(int health, float xpos, float ypos) {
    asteroid_texture_ptr = &asteroid_texture;
    asteroid_texture.loadFromFile("Assets/asteroid-big-0000.png");
    this->rect.setTexture(asteroid_texture_ptr);
    this->rect.setPosition(xpos,ypos);
    this->health = health;
    this->CollitionDamage = 50;
    this->rect.setSize(sf::Vector2f(100,100));
    this->rect.setOrigin(45,45);
    //this->rect.setSize(sf::Vector2f(player_texture_ptr->getSize().x, player_texture_ptr->getSize().y));
}

asteroid::asteroid() {
    this->rect.setPosition(0,0);
    this->health = this->maxHealth;
}

void asteroid::ProcessEvents(sf::RenderWindow* window) {
    if(i==180){
        this->velocity.y += 1;
        i = 0;
    }
    i++;
}