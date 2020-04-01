//
// Created by Sondre on 19.10.2017.
//

#include "GameInterface.h"
#include <iostream>
#include "gameConfig.h"
#include "equipment.h"

// Declare and load a font
sf::Font font;
sf::Text* moneyLabel_ptr;
sf::Text* scoreLabel_ptr;
Object* healthBar_ptr;
Object* energyBar_ptr;


GameInterface::GameInterface(){


    ammo1.loadFromFile("Assets/player.png");

    moneyLabel_ptr = &moneyLabel;
    scoreLabel_ptr = &scoreLabel;

    moneyLabel = sf::Text();
    scoreLabel = sf::Text();

    sf::Texture* hud_main_ptr = &hud_main;
    sf::Texture* hp_bar_ptr = &hp_bar;
    sf::Texture* energy_bar_ptr = &energy_bar;
    sf::Texture* frames_ptr = &frames;


    priWeapon_tx_ptr = PlayerEquipment[0]->ObjectTexture();
    secWeapon_1_tx_ptr = PlayerEquipment[1]->ObjectTexture();
    secWeapon_2_tx_ptr = PlayerEquipment[2]->ObjectTexture();


    hud_main.loadFromFile("Assets/HUD-Main.png");
    hp_bar.loadFromFile("Assets/health-bar.png");
    energy_bar.loadFromFile("Assets/energy-bar.png");
    frames.loadFromFile("Assets/bar-frames.png");

    //781
    moneyLabel.setPosition(20,8);
    scoreLabel.setPosition(940, 8);
    primary_weapon_ptr = new Object(1108,713, 1, 1, priWeapon_tx_ptr, 68, 68); //68x68
    secondary_weapon_1_ptr = new Object(1048,738, 1, 1, secWeapon_1_tx_ptr, 42, 42);
    secondary_weapon_2_ptr = new Object(987,738, 1, 1, secWeapon_2_tx_ptr, 42, 42);
    Object* e1 = new Object(0,0, 1, 1, hud_main_ptr, 1200, 800);
    healthBar_ptr = new Object(10,731, 1, 1, hp_bar_ptr, 191, 16);
    energyBar_ptr = new Object(10,777, 1, 1, energy_bar_ptr, 191, 16);
    Object* e4 = new Object(8,729, 1, 1,  frames_ptr, 195, 66);

    font.loadFromFile("Fonts/neuropol.ttf");

    moneyLabel.setFont(font);
    scoreLabel.setFont(font);

    UI_Objects.push_back(e1);
    UI_Objects.push_back(healthBar_ptr);
    UI_Objects.push_back(energyBar_ptr);
    UI_Objects.push_back(e4);
    UI_Objects.push_back(primary_weapon_ptr);
    UI_Objects.push_back(secondary_weapon_1_ptr);
    UI_Objects.push_back(secondary_weapon_2_ptr);
    texts.push_back(moneyLabel_ptr);
    texts.push_back(scoreLabel_ptr);
}

std::list<Object*> GameInterface::GetObjects(){
    return UI_Objects;
}

std::list<sf::Text*> GameInterface::GetLabels(){
    return texts;
}

void GameInterface::update(){
    priWeapon_tx_ptr = PlayerEquipment[0]->ObjectTexture();
    secWeapon_1_tx_ptr = PlayerEquipment[1]->ObjectTexture();
    secWeapon_2_tx_ptr = PlayerEquipment[2]->ObjectTexture();
}

void GameInterface::setHealthPercentage(float percentage){
    healthBar_ptr->rect.setScale(percentage/100, 1.0);
}


void GameInterface::setMoney(int money){
    moneyLabel_ptr->setString(std::to_string(money) + "$");
}

void GameInterface::setScore(int score){
    scoreLabel_ptr->setString("Score: " + std::to_string(score));
}

void GameInterface::setEnergyPercentage(float percentage) {
    energyBar_ptr->rect.setScale(percentage/100, 1.0);
}

void setWeapon(int index, Object* newWeapon){
    if(index == 0)
    {
        //primary_weapon_ptr = newWeapon;
    }
    else if(index > 0)
    {
        //secondary_weapons_ptr[index-1] = newWeapon;
    }
}