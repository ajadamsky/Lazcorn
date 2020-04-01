#ifndef LAZCORN_MENU_H
#define LAZCORN_MENU_H

#include "../state.h"
#include "../gameMenu.h"
#include <SFML/Audio.hpp>


class StateMenu : public State{
public:
    void GoNext(Machine &machine, sf::RenderWindow* window);
    StateMenu();
    void draw(sf::RenderWindow* window) override ;
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    float fontsize = 51;
    sf::Text menu[6];
    sf::Sprite background;
    sf::Texture BackgroundTexture;
    sf::Texture ActiveTexture;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //
    sf::Music music;
    sf::Sound boop;
    sf::SoundBuffer boopBuffer;
};

#endif //LAZCORN_MENU_H
