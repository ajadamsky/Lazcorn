//
// Created by BearMace on 13/10/2017.
//

#include "gameMenu.h"
#include <iostream>


gameMenu::gameMenu(float width, float height)
{
    if (!font.loadFromFile("Fonts/waltographUI.ttf"))
    {
        // handle error
    }


    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setCharacterSize(fontsize);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width/3, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setCharacterSize(fontsize);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setCharacterSize(fontsize);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    selectedItemIndex = 0;


}


gameMenu::~gameMenu()
{
}

void gameMenu::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window->draw(menu[i]);

    }
}

void gameMenu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void gameMenu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}


void gameMenu::Music() {



 }
