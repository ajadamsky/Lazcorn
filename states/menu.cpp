#include <iostream>
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "../machine.h"
#include "../gameMenu.h"
#include "../game.h"
#include "../Object.h"
#include <SFML/Audio.hpp>
#include "../gameConfig.h"


gameMenu menu(100,100);
Object* selected;
bool optionSelected;

void StateMenu::GoNext(Machine &machine, sf::RenderWindow* window){
    sf::Event event;

    if(music.getStatus() != sf::SoundSource::Status::Playing) {
        music.setVolume(20);
        music.setLoop(true);
        music.play();
    }

    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        MoveUp();
                        //option.MoveUp();
                        break;

                    case sf::Keyboard::S:
                        MoveDown();
                        //option.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        if (!optionSelected)
                            switch (GetPressedItem()) {
                                case 0:
                                    std::cout << "Play button has been pressed" << std::endl;
                                    music.stop();
                                    machine.RestartLevel();
                                    machine.SetState(Machine::StateId::level_1);
                                    break;
                                case 1:
                                    std::cout << "Loadout button has been pressed" << std::endl;
                                    machine.SetState(Machine::StateId::SHOP);
                                    break;
                                case 2:
                                    std::cout << "Options button has been pressed" << std::endl;
                                    break;
                                case 3:
                                    std::cout << "Quests button has been pressed" << std::endl;
                                    break;
                                case 4:
                                    std::cout << "Credits button has been pressed" << std::endl;
                                    break;
                                case 5:
                                    window->close();
                                    break;
                            }
                        break;
                }

                break;
            case sf::Event::Closed:
                window->close();

                break;

        }
    }

    window->clear();

    window->draw(background);
    window->draw(selected->getShape());

    for (int i = 0; i < 6; i++)
    {
        window->draw(menu[i]);
    }



    window->display();
}

StateMenu::StateMenu() {
    sf::Texture* texture = &ActiveTexture;
    ActiveTexture.loadFromFile("Assets/active1.png");

    if(!boopBuffer.loadFromFile("Sounds/menu_boop.wav"))
    {
        std::cout<< "Sound Error: "<<std::endl;
    }
    boop.setBuffer(boopBuffer);

    if(!music.openFromFile("Music/menu_music.wav"))
    {
        std::cout<< "Music Error: "<<std::endl;
    }

    selected = new Object(346, 255, 0, 0, texture, 508, 75);
    std::cout << "Menu" << std::endl;

    if (!font.loadFromFile("Fonts/neuropol.ttf"))
    {
        // handle error
    }


    sf::Color fontColor(167u,221u,223u,255u);

    menu[0].setFont(font);
    menu[0].setColor(fontColor);
    menu[0].setCharacterSize(fontsize);
    menu[0].setString("Play");
    menu[0].setPosition(523,260);

    menu[1].setFont(font);
    menu[1].setColor(fontColor);
    menu[1].setCharacterSize(fontsize);
    menu[1].setString("Loadout");
    menu[1].setPosition(450,340);

    menu[2].setFont(font);
    menu[2].setColor(fontColor);
    menu[2].setCharacterSize(fontsize);
    menu[2].setString("Options");
    menu[2].setPosition(474,420);

    menu[3].setFont(font);
    menu[3].setColor(fontColor);
    menu[3].setCharacterSize(fontsize);
    menu[3].setString("Quests");
    menu[3].setPosition(488,500);

    menu[4].setFont(font);
    menu[4].setColor(fontColor);
    menu[4].setCharacterSize(fontsize);
    menu[4].setString("Credits");
    menu[4].setPosition(476,585);

    menu[5].setFont(font);
    menu[5].setColor(fontColor);
    menu[5].setCharacterSize(fontsize);
    menu[5].setString("Quit");
    menu[5].setPosition(536,663);

    selectedItemIndex = 0;

    optionSelected = false;
    //OptionMenu option(window_ptr.getSize().x, window_ptr.getSize().y);





    if(!BackgroundTexture.loadFromFile("BackGrounds/MainBackground.png"))
    {
        std::cout<<"ERROR Failed to load background\n";
    }
    else
    {
        TextureSize = BackgroundTexture.getSize(); //Get size of texture.
        WindowSize.x = screenWidth;             //Get size of window_ptr.
        WindowSize.y = screenHeight;

        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

        background.setTexture(BackgroundTexture);
        background.setScale(ScaleX, ScaleY);      //Set scale.
    }
}

void StateMenu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        selectedItemIndex--;
        std::cout << selectedItemIndex << std::endl;
        selected->rect.setPosition(selected->getShape().getPosition().x, 255 + selectedItemIndex*81);
        boop.play();
    }
}

void StateMenu::MoveDown()
{
    if (selectedItemIndex + 1 < 6)
    {
        selectedItemIndex++;
        std::cout << selectedItemIndex << std::endl;
        selected->rect.setPosition(selected->getShape().getPosition().x, 255 + selectedItemIndex*81);
        boop.play();
    }
}

void StateMenu::draw(sf::RenderWindow* window) {

}

