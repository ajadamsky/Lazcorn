//
// Created by Sondre on 07.12.2017.
//

#ifndef LAZCORN_MESSAGEBOX_H
#define LAZCORN_MESSAGEBOX_H


#include "Object.h"

class MessageBox : public Object{
public:
    MessageBox(int x, int y);
    void show(int Duration_ms);
    bool ShouldDraw();
    int ms_stayAlive = 0;
    void addLabel(int x, int y, std::string text);
    std::vector<sf::Text*> labels;
    sf::Texture bgtx;

    void addHeading(std:: string text);

private:
    sf::Clock clock;
};


#endif //LAZCORN_MESSAGEBOX_H
