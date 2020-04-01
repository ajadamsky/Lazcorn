//
// Created by Sondre on 19.10.2017.
//

#ifndef LAZCORN_LEVEL_1_H
#define LAZCORN_LEVEL_1_H

#include "../state.h"
#include "../Object.h"
#include "../enemyShips.h"
#include "../GameInterface.h"
#include "level_base.h"
#include "../player.h"
#include "../asteroid.h"
#include "../randomGen.h"
#include "../BossClass.h"
#include "../MessageBox.h"
#include <SFML/Audio.hpp>

class level_1 : public State, level_base{
public:
    level_1();
    void GoNext(Machine &machine, sf::RenderWindow* window) override;

    sf::Texture Boss_1;
    sf::Texture Boss_1_bullet_1;
    sf::Texture Explotion;
    sf::Texture GameOver;
    sf::RectangleShape GameOverShape;
    std::list<Object*> Level_Objects;
    std::vector<Object*>Enemy_bullets;
    std::list<BossClass*>Boss_objects;
    std::list<enemyShips*> Enemy_Objects;
    std::vector<MessageBox*> MessageBoxes;
    std::vector<enemyShips*> Enemy_Buffer;
    GameInterface ui;
    float targetScore;
    void RoundEnd(Machine* machine);
    float score;

    sf::Vector2f screensize;

    Object* EX;

    sf::SoundBuffer buffer;
    sf::Sound Explotion_Enemy;


    std::vector<asteroid*> Asteroid_Objects;
    std::vector<asteroid*> Asteroid_Buffer;

    sf::Clock clock;
    sf::Clock RegenerationClock;
    sf::Clock enemySpawnClock;
    sf::Clock asteroidSpawnClock;


    bool bossStage = false;
    bool Spawning_Enemys = true;
    bool Stageover = false;
    bool Spawn_Boss = true;

    std::default_random_engine el{std::random_device{}()};
    std::uniform_int_distribution<int>uniform_dist{0,4};

    int spawnTime = 2;
    int number_of_sqadron_on_level = 0;
    int Enemy_number;
    int number = 0;
    int KillCount = 0;
    int random;

    bool Player_Fire = true;

    void MoveDown();

    void MoveRight();

    void MoveLeft();


    void CreateAsteroids(int health, int amount);
    void CreateEnemySquadron(int spawnPoint, int health, int target, int amount,int Number);

    player* Player;
    enemyShips* Enemy;
    pathPoints* PP;
    asteroid* Asteroid;
    randomGen randomGen;

    BossClass* Boss;

    float deltaTime;
    float xpos;
    float ypos;

    void CreateBoss();
    sf::Music music;
};


#endif //LAZCORN_LEVEL_1_H
