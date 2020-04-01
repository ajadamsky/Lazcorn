//
// Created by Sondre on 23.10.2017.
//

#include <iostream>
#include "player.h"
#include "gameConfig.h"



sf::Texture* player_texture_ptr;

// load something into the sound buffer...

player::player(int x, int y, int health) {
    player_texture_ptr = &player_texture;
    player_texture.loadFromFile("Assets/player.png");
    this->rect.setTexture(player_texture_ptr);
    this->rect.setPosition(x,y);
    this->health = health;
    this->maxHealth = health;
    this->CollitionDamage = 10000;
    this->rect.setSize(sf::Vector2f(100,100));
    //this->rect.setSize(sf::Vector2f(player_texture_ptr->getSize().x, player_texture_ptr->getSize().y));
    buffer.loadFromFile("Sounds/fighter_laser.wav");
    sound.setBuffer(buffer);
    sound.setVolume(50);
}

player::player() {
    this->rect.setPosition(0,0);
    this->health = this->maxHealth;

}

void player::ProcessEvents(sf::RenderWindow* window,float deltatime){
    sf::Event event;

    float movement_x = 0;
    float movement_y = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movement_y = -deltatime*playerSpeed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movement_y = deltatime*playerSpeed;
    }



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movement_x = -deltatime*playerSpeed;
    }



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movement_x = deltatime*playerSpeed;
    }

    this->velocity.y = movement_y;
    this->velocity.x = movement_x;



    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {

                    case sf::Keyboard::J:

                        if(Player_can_fire)
                        {
                            sound.play();
                            shoot(PlayerEquipment[0], sf::Vector2f(0.0f, -15.0f));
                        }

                        break;

                    case sf::Keyboard::K:
                        if(Player_can_fire)
                        {
                            sound.play();
                            shoot(PlayerEquipment[1], sf::Vector2f(0.0f, -15.0f));
                        }
                        break;

                    case sf::Keyboard::L:
                        if(Player_can_fire)
                        {
                            sound.play();
                            shoot(PlayerEquipment[2], sf::Vector2f(0.0f, -15.0f));
                        }
                        break;


                }



                break;
            case sf::Event::Closed:
                window->close();

                break;

        }
    }
}

void player::moveOverride() {
    PlayerEquipment[0]->rect.setPosition(this->rect.getPosition().x, this->rect.getPosition().y + 50);
    PlayerEquipment[2]->rect.setPosition(this->rect.getPosition().x + 70, this->rect.getPosition().y + 50);
    PlayerEquipment[1]->rect.setPosition(this->rect.getPosition().x + 35, this->rect.getPosition().y + 25);
}

void player::shoot(equipment* weapon, sf::Vector2f velocity)
{
    if(weapon->clock.getElapsedTime().asSeconds() > weapon->FireRate) {
        if(weapon->Name == "The Oblivirator")
        {
            if(this->Energy > 50){
                Object *p = new Object(0, 0, 10000.0f, 10000.0f, weapon->projectile->ObjectTexture(), weapon->projectile->rect.getSize().x, weapon->projectile->rect.getSize().y);
                p->CollitionDamage = weapon->BaseDamage + (weapon->Level * weapon->UpgradeScale);
                p->rect.setPosition(0, weapon->getShape().getPosition().y);
                p->velocity = velocity;
                p->parent = this;
                projectiles.push_back(p);
                weapon->clock.restart();
                this->Energy = this->Energy-50;
            }
        }
        else
        {
            Object *p = new Object(0, 0, 1.0f, 1.0f, weapon->projectile->ObjectTexture(), weapon->projectile->rect.getSize().x, weapon->projectile->rect.getSize().y);
            std::cout << weapon->BaseDamage << "+(" << weapon->Level << "*" << weapon->UpgradeScale << ")=" << weapon->BaseDamage + (weapon->Level * weapon->UpgradeScale) << std::endl;
            p->CollitionDamage = weapon->BaseDamage + (weapon->Level * weapon->UpgradeScale);
            p->rect.setPosition(weapon->getShape().getPosition().x + 10, weapon->getShape().getPosition().y);
            p->velocity = velocity;
            p->parent = this;
            projectiles.push_back(p);
            weapon->clock.restart();
        }
    }
}