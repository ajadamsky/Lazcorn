//
// Created by Sondre on 28.11.2017.
//

#include <iostream>
#include "shop.h"
#include "../Object.h"
#include "../machine.h"
#include "../gameConfig.h"


Object* Shopselected;
bool ShopoptionSelected;

void StateShop::GoNext(Machine &machine, sf::RenderWindow *window) {
    sf::Event event;

    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        machine.SetState(Machine::StateId::MENU);
                        break;
                    case sf::Keyboard::W:
                        MoveUp();
                        //option.MoveUp();
                        break;
                    case sf::Keyboard::J:
                        PlayerEquipment[0] = new equipment(*AvailableEquipment[selectedItemIndex]);
                        break;
                    case sf::Keyboard::K:
                        PlayerEquipment[1] = new equipment(*AvailableEquipment[selectedItemIndex]);
                        break;
                    case sf::Keyboard::L:
                        PlayerEquipment[2] = new equipment(*AvailableEquipment[selectedItemIndex]);
                        break;
                    case sf::Keyboard::S:
                        MoveDown();
                        //option.MoveDown();
                        break;

                    case sf::Keyboard::Return: {
                        if (!ShopoptionSelected) {
                            if (money > (AvailableEquipment[GetPressedItem()]->Level *
                                         AvailableEquipment[GetPressedItem()]->UpgradeCost)) {
                                money -= (AvailableEquipment[GetPressedItem()]->Level *
                                          AvailableEquipment[GetPressedItem()]->UpgradeCost);
                                AvailableEquipment[GetPressedItem()]->Level++;
                                for(int i = 0; i < 3; i++)
                                {
                                    if(PlayerEquipment[i]->Name == AvailableEquipment[selectedItemIndex]->Name) {
                                        PlayerEquipment[i] = new equipment(*AvailableEquipment[GetPressedItem()]);
                                        std::cout << "Players Equpment level: " << PlayerEquipment[i]->Level << std::endl;
                                    }
                                }
                                purchaseSound.play();

                            } else {
                                //Player can't afford weapon upgrade
                            }
                        }
                        break;
                    }
                }

                break;
            case sf::Event::Closed:
                window->close();

                break;

        }
    }

    lblPlayerMoney.setString("Your money: $" + std::to_string((int)money));

    window->clear();

    for(Object* o:EquipedWeaponIndicators)
    {
        o->rect.setRotation(o->rect.getRotation() + 1);
    }

    window->draw(background);
    window->draw(StaticAssets);
    window->draw(lblPlayerMoney);
    for(sf::Sprite* o:tabs)
    {
        window->draw(*o);
    }

    for (int i = 0; i < shopItems.size(); i++)
    {
        shopItemLevelLabels[i]->setString("Level: " + std::to_string(AvailableEquipment[i]->Level));
        shopItemPriceLabels[i]->setString("Upgrade: $" + std::to_string((int)(AvailableEquipment[i]->UpgradeCost * AvailableEquipment[i]->Level)));
        shopItemDmgUpLabels[i]->setString("Stat increase: Damage " + std::to_string((int)(AvailableEquipment[i]->BaseDamage + (AvailableEquipment[i]->UpgradeScale * (AvailableEquipment[i]->Level)))) + "->" + std::to_string((int)(AvailableEquipment[i]->BaseDamage + (AvailableEquipment[i]->UpgradeScale * (AvailableEquipment[i]->Level + 1)))));
        window->draw(shopItems[i]->getShape());

        if(selectedItemIndex == i)
        {
            Shopselected->rect.setPosition(200, 120+(203*i));
            window->draw(Shopselected->getShape());
        }
        window->draw(*shopItemLabels[i]);
        window->draw(*shopItemLevelLabels[i]);
        window->draw(*shopItemPriceLabels[i]);
        window->draw(*shopItemDmgUpLabels[i]);
        if(AvailableEquipment[i]->Name == PlayerEquipment[0]->Name)
        {
            EquipedWeaponIndicators[0]->rect.setPosition(875, 190 + (206 * i));
            window->draw(EquipedWeaponIndicators[0]->getShape());
        }
        if(AvailableEquipment[i]->Name == PlayerEquipment[1]->Name)
        {
            EquipedWeaponIndicators[1]->rect.setPosition(963, 190 + (206 * i));
            window->draw(EquipedWeaponIndicators[1]->getShape());
        }
        if(AvailableEquipment[i]->Name == PlayerEquipment[2]->Name)
        {
            EquipedWeaponIndicators[2]->rect.setPosition(1049, 190 + (206 * i));
            window->draw(EquipedWeaponIndicators[2]->getShape());
        }
        window->draw(*EquipedLabels[i]);
    }

    window->display();
}

void StateShop::draw(sf::RenderWindow *window) {
    State::draw(window);
}

void StateShop::MoveUp() {
    if(selectedItemIndex > 0) {
        boop.play();
        selectedItemIndex--;
    }
}

void StateShop::MoveDown() {
    if(selectedItemIndex < shopItems.size()-1) {
        boop.play();
        selectedItemIndex++;
    }
}

StateShop::StateShop() {
    StaticAssetsTexture.loadFromFile("Assets/Store/static-assets.png");
    StaticAssets.setTexture(StaticAssetsTexture);

    font.loadFromFile("Fonts/neuropol.ttf");

    if(!boopBuffer.loadFromFile("Sounds/menu_boop.wav"))
    {
        std::cout<< "Sound Error: "<<std::endl;
    }
    boop.setBuffer(boopBuffer);

    BackgroundTexture.loadFromFile("Assets/Store/wallpaper.png");
    background.setTexture(BackgroundTexture);

    SelectedItemTexture.loadFromFile("Assets/Store/itemBackground-Highlight.png");
    Shopselected = new Object(200,120,1,1,&SelectedItemTexture, 940, 200);

    EquipedWeaponIndicatorsTexture.loadFromFile("Assets/equiped.png");

    ItemTexture.loadFromFile("Assets/Store/itemBackground.png");

    for(equipment* e:AvailableEquipment) {
        shopItems.push_back(new Object(200, 120, 1, 1, &ItemTexture, 940, 200));
    }

    selectedItemIndex = 0;


    purchaseSoundBuffer.loadFromFile("Sounds/purchase.wav");
    purchaseSound.setBuffer(purchaseSoundBuffer);


    PowerUpsTabTexture.loadFromFile("Assets/Store/powerups-tab.png");
    tabs.push_back(new sf::Sprite(PowerUpsTabTexture, sf::IntRect(0,0,1200,800)));

    lblPlayerMoney = sf::Text("", font, 30);
    lblPlayerMoney.setPosition(800, 80);

    EquipedWeaponIndicators.push_back(new Object(0,0,1,1,&EquipedWeaponIndicatorsTexture, 100,100));
    EquipedWeaponIndicators[0]->rect.setOrigin(EquipedWeaponIndicators[0]->rect.getSize().x/2, EquipedWeaponIndicators[0]->rect.getSize().y/2);
    EquipedWeaponIndicators.push_back(new Object(0,0,1,1,&EquipedWeaponIndicatorsTexture, 100,100));
    EquipedWeaponIndicators[1]->rect.setOrigin(EquipedWeaponIndicators[1]->rect.getSize().x/2, EquipedWeaponIndicators[1]->rect.getSize().y/2);
    EquipedWeaponIndicators.push_back(new Object(0,0,1,1,&EquipedWeaponIndicatorsTexture, 100,100));
    EquipedWeaponIndicators[2]->rect.setOrigin(EquipedWeaponIndicators[2]->rect.getSize().x/2, EquipedWeaponIndicators[2]->rect.getSize().y/2);

    int index = 0;
    for(Object* o:shopItems)
    {
        o->rect.setPosition(200, 120 + (203*index));

        sf::Text* t = new sf::Text(AvailableEquipment[index]->Name, font, 30);
        t->setPosition(215, 140 + (206 * index));
        shopItemLabels.push_back(t);

        sf::Text* t2 = new sf::Text("Level: " + std::to_string(AvailableEquipment[index]->Level), font, 15);
        t2->setPosition(215, 180 + (206 * index));
        shopItemLevelLabels.push_back(t2);

        sf::Text* t3 = new sf::Text("J       K      L", font, 30);
        t3->setPosition(865, 170 + (206 * index));
        EquipedLabels.push_back(t3);

        sf::Text* t4 = new sf::Text("", font, 15);
        t4->setPosition(215, 200 + (206 * index));
        shopItemPriceLabels.push_back(t4);

        sf::Text* t5 = new sf::Text("", font, 15);
        t5->setPosition(215, 220 + (206 * index));
        shopItemDmgUpLabels.push_back(t5);

        index++;
    }
}