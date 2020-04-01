//
// Created by Sondre on 13.11.2017.
//

#include "equipment.h"

equipment::equipment(float fire_rate, Object* Projectile, sf::Texture* equipmentTexture) {
    this->FireRate = fire_rate;
    this->projectile = Projectile;
    this->tx = equipmentTexture;
    this->rect.setTexture(equipmentTexture);
}
