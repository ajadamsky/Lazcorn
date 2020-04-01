//
// Created by Sondre on 19.10.2017.
//

#include <iostream>
#include <SFML/Audio/Sound.hpp>
#include "Object.h"
#include "gameConfig.h"

Object::Object(){

};

Object::Object(int x, int y, float health, float maxHealth, sf::Texture* texture, int height, int width){
    this->maxHealth = maxHealth;
    this->health = health;
    this->rect.setPosition(x,y);
    this->rect.setTexture(texture);
    this->rect.setSize(sf::Vector2f(height, width));
    this->tx = texture;

}

sf::RectangleShape Object::getShape(){
    return Object::rect;
}

sf::Texture* Object::ObjectTexture(){
        return this->tx;
}

void Object::move(){
    this->rect.setPosition(rect.getPosition().x + velocity.x, rect.getPosition().y + velocity.y);
    if(this->rect.getPosition().x > screenWidth + 200 || this->rect.getPosition().x < -200)
        destroy();
    else if (this->rect.getPosition().y > screenHeight + 200 || this->rect.getPosition().y < -200)
        destroy();
    moveOverride();
}

void Object::moveOverride(){
}

void Object::takeDamage(int damage){
    if(this->health < damage){
        this->health = 0;
    }
    else
        this->health -= damage;

    if(this->health == 0){
        this->destroy();
    }
}

void Object::Heal(int amount){
    this->health += amount;
}

void Object::destroy(){
    shouldDelete = true;
}

Object::~Object() {

}

bool Object::Explotion_animation(Object *EX,sf::SoundBuffer &buffer,sf::Sound &Explotion_Enemy,int x, int y)
{
    EX->rect.setSize(sf::Vector2f(x,y));
    if(!ExplotionClock_On)
    {
        EX->rect.setPosition(rect.getPosition().x,rect.getPosition().y);
        Explotion_clock.restart();
        ExplotionClock_On=true;

        buffer.loadFromFile("Sounds/Explosion_1.wav");

        Explotion_Enemy.setBuffer(buffer);
        Explotion_Enemy.setVolume(25);
        Explotion_Enemy.play();
        //

    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.1)
    {
        EX->rect.setFillColor(sf::Color::Red);
        EX->rect.setPosition(rect.getPosition().x,rect.getPosition().y);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.2)
    {
        EX->rect.setFillColor(sf::Color::Yellow);
        EX->rect.setPosition(rect.getPosition().x,rect.getPosition().y);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.3)
    {
        EX->rect.setFillColor(sf::Color::Red);
        EX->rect.setPosition(rect.getPosition().x,rect.getPosition().y);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.4)
    {
        EX->rect.setFillColor(sf::Color::Yellow);
        EX->rect.setPosition(rect.getPosition().x,rect.getPosition().y);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.5) {
        EX->rect.setFillColor(sf::Color::Red);
        EX->rect.setPosition(rect.getPosition().x , rect.getPosition().y);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.6)
    {
        std::cout<<" 4sek"<<std::endl;
        return true;
    }
}
