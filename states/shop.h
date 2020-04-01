//
// Created by Sondre on 28.11.2017.
//

#ifndef LAZCORN_SHOP_H
#define LAZCORN_SHOP_H
#include "../state.h"
#include "../gameConfig.h"
#include "stdio.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>


class StateShop : public State{
public:
    void GoNext(Machine &machine, sf::RenderWindow* window);
    void draw(sf::RenderWindow* window) override ;
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    StateShop();

private:
    int selectedItemIndex;
    sf::Font font;
    float fontsize = 51;
    sf::Sprite background;


    sf::Sound purchaseSound;
    sf::SoundBuffer purchaseSoundBuffer;

    sf::Text lblPlayerMoney;

    sf::Sound boop;
    sf::SoundBuffer boopBuffer;

    std::vector<Object*> shopItems;
    std::vector<sf::Text*> shopItemLabels;
    std::vector<sf::Text*> shopItemLevelLabels;
    std::vector<sf::Text*> shopItemPriceLabels;
    std::vector<sf::Text*> shopItemDmgUpLabels;
    std::vector<sf::Text*> EquipedLabels;

    sf::Texture SelectedWeaponTexture;
    std::vector<Object*> EquipedWeaponIndicators;
    sf::Texture EquipedWeaponIndicatorsTexture;

    std::vector<sf::Sprite*> tabs;

    sf::Texture SelectedItemTexture;
    sf::Texture ItemTexture;

    sf::Texture PowerUpsTabTexture;

    sf::Texture BackgroundTexture;

    sf::Texture StaticAssetsTexture;
    sf::Sprite StaticAssets;


};


#endif //LAZCORN_SHOP_H
