//
// Created by Sondre on 07.12.2017.
//

#include "MessageBox.h"

sf::Font Labelfont;
MessageBox::MessageBox(int x, int y)
{
    Labelfont.loadFromFile("Fonts/neuropol.ttf");
    this->rect.setPosition(x, y);
    this->bgtx.loadFromFile("Assets/message_box.png");
    this->rect.setTexture(&bgtx);
    this->rect.setSize(sf::Vector2f(487,118));
}



void MessageBox::show(int Duration_ms) {
    ms_stayAlive = Duration_ms;
    clock.restart();
}

bool MessageBox::ShouldDraw() {
    if(clock.getElapsedTime().asMilliseconds() > ms_stayAlive)
        return false;
    else
        return true;
}

void MessageBox::addLabel(int x, int y, std::string text) {
    sf::Text* t = new sf::Text();
    t->setPosition(this->getShape().getPosition().x + x + 31, this->getShape().getPosition().y + y + 48);
    t->setString(text);
    t->setCharacterSize(12);
    t->setFillColor(sf::Color::White);
    t->setFont(Labelfont);
    labels.push_back(t);

}

void MessageBox::addHeading(std::string text) {
    sf::Text *t = new sf::Text();
    t->setPosition(this->getShape().getPosition().x + 30, this->getShape().getPosition().y + 12);
    t->setString(text);
    t->setCharacterSize(20);
    t->setFillColor(sf::Color::White);
    t->setFont(Labelfont);
    labels.push_back(t);
}