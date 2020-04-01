//
// Created by BearMace on 27/11/2017.
//

#include <iostream>
#include "BossClass.h"


sf::Texture* Boss_texture_ptr;

BossClass::BossClass(int x, int y, int health,sf::Texture* BossPic,sf::Texture* Bullet,float Boss_Fire_Rate)
{
    //Boss_texture_ptr = &Boss_texture;
    //Boss_texture.loadFromFile("")
    Explotion.loadFromFile("Assets/Explosion-FX-royalty-free-game-art-.png");
    this->rect.setTexture(BossPic);
    Project_Texture = Bullet;
    fireRate = Boss_Fire_Rate;
    //rect.setFillColor(sf::Color::Red);
    rect.setPosition(x,y);
    this->health = health;
    this->maxHealth = health;
    this->CollitionDamage = 10;
    rect.setSize(sf::Vector2f(300,100));
    this->weapons[0] = new equipment(*AvailableEquipment[0]);
    this->weapons[1] = new equipment(*AvailableEquipment[0]);
    this->weapons[2] = new equipment(*AvailableEquipment[0]);
    this->HealthBarBackground->setPosition(500,500);
    this->HealthBar->setPosition(500,500);
    this->HealthBarBackground->setSize(sf::Vector2f(this->getShape().getSize().x, 10));
    this->HealthBar->setOrigin(0,0);
    this->HealthBar->setSize(sf::Vector2f(this->getShape().getSize().x-4, 10));
    this->HealthBarBackgroundTexture.loadFromFile("Assets/energy-bar.png");
    this->HealthBarTexture.loadFromFile("Assets/health-bar.png");
    this->HealthBar->setTexture(&HealthBarTexture);
    this->HealthBarBackground->setTexture(&HealthBarBackgroundTexture);
}

BossClass::BossClass()
{
    rect.setPosition(0,0);
    this->health = this->maxHealth;
}


void BossClass::shoot(equipment* weapon, sf::Vector2f velocity)
{
    if(weapon->clock.getElapsedTime().asSeconds() > weapon->FireRate) {
        Object *p = new Object(0, 0, 1.0f, 1.0f, weapon->projectile->ObjectTexture(), weapon->projectile->rect.getSize().x, weapon->projectile->rect.getSize().y);
        p->CollitionDamage = 5.0f + 2.0f * GameDifficulty;
        p->rect.setPosition(weapon->getShape().getPosition().x + 10, weapon->getShape().getPosition().y);
        p->velocity = sf::Vector2f(0, 3);
        p->parent = this;
        //std::cout<<"fire"<<std::endl;
        projectiles.push_back(p);
        buffer.loadFromFile("Sounds/fighter_laser.wav");
        sound.setBuffer(buffer);
        sound.play();

        if(weapon->exploding_projetile){
            p->exploding_projetile = true;
        }
        weapon->clock.restart();
    }
}

void BossClass::Bossmovment(float time,sf::Vector2f Player,int PlayerWidth, std::vector<Object*> *Bulllet_list)
{
    if(BossEntering)
    {

        velocity.y = speed/4*time;
        std::cout<<"Bossentering:"<<std::endl;
        if (rect.getPosition().y>100)
        {
            velocity.y = 0;
            BossEntering=false;
            BossFire = true;
        }
    }
    else{
    if(directionRight)
    {
        velocity.x = speed*time;
        if(rect.getPosition().x>1200-rect.getSize().x)
        {
            directionRight = false;
        }
    }
    else
    {
        velocity.x = -speed*time;
        if(rect.getPosition().x<0)
        {
            directionRight = true;
        }
    }
    }

    if(BossFire){
    Boss_fire(time);
    for(int i = 0; i < 3; i++) {
        if (Player.x < weapons[i]->rect.getPosition().x + rect.getSize().x + range &&
            Player.x > weapons[i]->rect.getPosition().x - range && can_fire) {

            shoot(weapons[i], sf::Vector2f(0.0f, 10.0f));
            weapons[i]->can_fire = false;
        }

    }
    }

}

void BossClass::Boss_fire(float time)
{
    //std::cout<<"fireRate: "<<FireClock.getElapsedTime().asSeconds()<<std::endl;
    if(FireClock.getElapsedTime().asSeconds()>fireRate)
    {
        //std::cout<<"Boss shooting"<<std::endl;
        can_fire = true;
        FireClock.restart();
    }
}

bool BossClass::BossExplotion(Object* EX,sf::SoundBuffer &buffer,sf::Sound &Explotion_Enemy,int x, int y)
{
    //rect.setTexture(&Explotion);
    EX->rect.setSize(sf::Vector2f(x,y));
    EX->rect.setPosition(rect.getPosition().x,rect.getPosition().y-offset);

    //rect.setOrigin(rect.getPosition().x,rect.getPosition().y);
    //rect.setFillColor(sf::Color::Red);
    if(!ExplotionClock_On)
    {
        EX->rect.setPosition(rect.getPosition().x,rect.getPosition().y-offset);
        Explotion_clock.restart();
        ExplotionClock_On=true;
        buffer.loadFromFile("Sounds/Explosion_1.wav");
        sound.setBuffer(buffer);
        sound.play();
        //

    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.1 -offset)
    {
        EX->rect.setFillColor(sf::Color::Red);
        EX->rect.setPosition(rect.getPosition().x+10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.2)
    {
        EX->rect.setFillColor(sf::Color::Yellow);
        EX->rect.setPosition(rect.getPosition().x-10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.3)
    {
        EX->rect.setFillColor(sf::Color::Red);
        EX->rect.setPosition(rect.getPosition().x-10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.4)
    {
        EX->rect.setFillColor(sf::Color::Yellow);
        EX->rect.setPosition(rect.getPosition().x+10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.5)
    {
        EX->rect.setFillColor(sf::Color::Red);
        EX->rect.setPosition(rect.getPosition().x+10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.6)
    {
        EX->rect.setFillColor(sf::Color::Yellow);
        EX->rect.setPosition(rect.getPosition().x-10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.7)
    {
        EX->rect.setFillColor(sf::Color::Red);
        EX->rect.setPosition(rect.getPosition().x-10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.8)
    {
        EX->rect.setFillColor(sf::Color::Yellow);
        EX->rect.setPosition(rect.getPosition().x+10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>0.9)
    {
        EX->rect.setFillColor(sf::Color::Red);
        EX->rect.setPosition(rect.getPosition().x+10,rect.getPosition().y-offset);
    }
    if(Explotion_clock.getElapsedTime().asSeconds()>1)
    {

        return true;
    }



}

void BossClass::moveOverride() {
    weapons[0]->rect.setPosition(this->rect.getPosition().x, this->rect.getPosition().y + 50);
    weapons[1]->rect.setPosition(this->rect.getPosition().x + 150, this->rect.getPosition().y + 50);
    weapons[2]->rect.setPosition(this->rect.getPosition().x + 300, this->rect.getPosition().y + 50);
    HealthBarBackground->setPosition(this->rect.getPosition().x, this->rect.getPosition().y);
    HealthBar->setPosition(this->rect.getPosition().x+2, this->rect.getPosition().y+1);
    HealthBar->setScale(health/maxHealth, 1);
}

