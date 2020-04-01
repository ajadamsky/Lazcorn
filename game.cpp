//
// Created by XONCRY on 12.10.2017.
//

//states[state].draw();

#include "game.h"
#include "machine.h"
#include <SFML/Window.hpp>
#include "State.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "gameConfig.h"

Machine Machine;

void Game::run(){
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Laser and Unicorns");
    window.setFramerateLimit(60);


    while(Machine.GetRunning())
    {
        Machine.GoNext(&window);
    }
}
