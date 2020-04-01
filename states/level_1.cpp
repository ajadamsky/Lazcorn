//
// Created by Sondre on 19.10.2017.
//

#include "level_1.h"
#include "../pathPoints.h"
#include "../enemyShips.h"
#include <list>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../gameConfig.h"

//int * ptr_target=&target;


bool ShowOpeningMessages = true;

level_1::level_1() {

    music.openFromFile("Music/game_music.wav");
    music.setVolume(40);
    music.setLoop(true);
    music.play();


    Player = new player(550, 600, 1000);

    Boss_1.loadFromFile("Assets/Nation1_Boss_1.png");
    Boss_1_bullet_1.loadFromFile("Sprites/Ammo/ammo.png");

    GameOver.loadFromFile("BackGrounds/game_over.png");


    CreateAsteroids(10, 3);

    //creating ponits for movement by enemys:
    PP = new pathPoints;
    PP->initTargetPoints();

    Enemy_number = 2 + 3*GameDifficulty;
    number = 0;
    //number_of_sqadron_on_level = Enemy_number;
    //bossStage = true;
    //CreateBoss();
    //Player->Player_can_fire= false;
    score = 0;
    targetScore = ((100 + (200 * GameDifficulty)))*(Enemy_number-(Enemy_number/10.0));

    Explotion.loadFromFile("Assets/Explosion-FX-royalty-free-game-art-.png");
    EX = new Object(0, 0, 1, 1, &Explotion, 300, 300);

    std::stringstream stream;
    stream << std::fixed << std::setprecision(0) << targetScore;
    std::string s = stream.str();

    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(2) << GameDifficulty;
    std::string s2 = stream2.str();

    MessageBoxes.push_back(new MessageBox(300, 300));
    MessageBoxes[0]->addLabel(0, 0, "Target score: " + s);
    MessageBoxes[0]->addHeading("LEVEL DETAILS");
    MessageBoxes[0]->addLabel(0, 15, "Number of squadrones: " + std::to_string(Enemy_number));
    MessageBoxes[0]->addLabel(0, 30, "Game difficulty: " + s2);


    Enemy_Objects.clear();

    ShowOpeningMessages = true;

    std::cout << "Level recreated\n";

}

void level_1::GoNext(Machine &machine, sf::RenderWindow *window) {

    if (ShowOpeningMessages) {
        MessageBoxes[0]->show(5000);
        ShowOpeningMessages = false;
    }

    deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    //try { /* */ } catch (const std::exception&) { /* */ }

    if (!Boss_objects.empty()) {
        //std::cout<<"boss on the field"<<std::endl;
        if (Boss->BossFire || Player_Fire) {
            Player->Player_can_fire = true;
        }
    }

    if(RegenerationClock.getElapsedTime().asMilliseconds() > 100)
    {
        if(Player->Energy < Player->MaxEnergy)
        {
            Player->Energy = Player->Energy + 0.2f;
        }
    }

    if(!bossStage && Spawning_Enemys) {
        if (enemySpawnClock.getElapsedTime().asSeconds() > 5) {
            random = uniform_dist(el);
            //std::cout << "Spawnpoint: " << random << std::endl;
            CreateEnemySquadron(random, 100 + (200 * GameDifficulty), 0, 3, 3);
            number_of_sqadron_on_level++;
            if (number_of_sqadron_on_level == number) {
                Spawning_Enemys = false;
            }
        }
    }


    if (!Enemy_Buffer.empty()) {
        if (enemySpawnClock.getElapsedTime().asSeconds() > 1) {
            enemySpawnClock.restart();
            Enemy_Objects.push_back(Enemy_Buffer[0]);
            //std::cout << Enemy_Objects.size() << std::endl;
            Enemy_Buffer.erase(Enemy_Buffer.begin());
            /*if(Enemy_number>number){
                number += 3;
            }*/
            number++;

        }
    }
    Player->ProcessEvents(window, deltaTime);

    if (Player->rect.getPosition().x >= 1100) {
        Player->velocity.x = -1;
    }
    if (Player->rect.getPosition().x <= 0) {
        Player->velocity.x = 1;
    }
    if (Player->rect.getPosition().y <= 0) {
        Player->velocity.y = 1;
    }
    if (Player->rect.getPosition().y >= 700) {
        Player->velocity.y = -1;
    }

    Player->move();


    //Boss->Bossmovment(deltaTime);
    //Boss->move();

    level_base::Update(1);

    window->clear();


    window->draw(level_base::bg1Shape);
    window->draw(level_base::bg2Shape);
    //window->draw(Boss->getShape());

    for (BossClass *boss:Boss_objects) {

        if (boss->health > 0) {


            boss->Bossmovment(deltaTime, Player->rect.getPosition(), Player->rect.getSize().x, &Enemy_bullets);
            boss->move();

            for (Object *bullet:boss->projectiles) {
                Enemy_bullets.push_back(bullet);
            }
            boss->projectiles.clear();

            window->draw(boss->getShape());

            for (Object *o:Player->projectiles) {
                if (o->rect.getGlobalBounds().intersects(boss->rect.getGlobalBounds())) {
                    o->takeDamage(boss->CollitionDamage);
                    boss->takeDamage(o->CollitionDamage);
                }

            }
        }
        window->draw(boss->getShape());
        window->draw(*boss->HealthBarBackground);
        window->draw(*boss->HealthBar);
    }

    int count = 0;
    for (enemyShips *eneobj:Enemy_Objects) {
        eneobj->enemymovement(eneobj, deltaTime, PP, Player->rect.getPosition(), Player->rect.getSize().x,
                              &Enemy_bullets);
        //eneobj->enemy_move(eneobj->velocity.x,eneobj->velocity.y);

        for (Object *bullet:eneobj->projectiles) {
            Enemy_bullets.push_back(bullet);
        }
        eneobj->projectiles.clear();

        eneobj->move();
        for (Object *o:Player->projectiles) {
            if (o->parent != o) {
                if (o->rect.getGlobalBounds().intersects(eneobj->rect.getGlobalBounds())) {
                    o->takeDamage(eneobj->CollitionDamage);
                    eneobj->takeDamage(o->CollitionDamage);
                    std::cout << "Bullet did " << o->CollitionDamage << " damage, remaining HP is: " << eneobj->health << std::endl;
                }
            }
        }

        window->draw(eneobj->getShape());
        window->draw(*eneobj->HealthBarBackground);
        window->draw(*eneobj->HealthBar);
        count++;
        if (Player->rect.getGlobalBounds().intersects(eneobj->rect.getGlobalBounds())) {
            Player->takeDamage(eneobj->CollitionDamage);
            eneobj->takeDamage(Player->CollitionDamage);
            std::cout << "collition:" << std::endl;
        }

    }

    if (!Asteroid_Buffer.empty()) {
        if (enemySpawnClock.getElapsedTime().asSeconds() > 2) {
            asteroidSpawnClock.restart();
            Asteroid_Objects.push_back(Asteroid_Buffer[0]);
            std::cout << Asteroid_Objects.size() << std::endl;
            Asteroid_Buffer.erase(Asteroid_Buffer.begin());
        }
    }

    for (asteroid *asteroidobj:Asteroid_Objects) {
        asteroidobj->ProcessEvents(window);
        asteroidobj->rect.setRotation(asteroidobj->rect.getRotation() + 0.5);
        asteroidobj->move();
        window->draw(asteroidobj->getShape());

        if (asteroidobj->rect.getGlobalBounds().intersects(Player->rect.getGlobalBounds())) {
            //std::cout<<"traff en astroide"<<std::endl;
            Player->takeDamage(asteroidobj->CollitionDamage);
            asteroidobj->takeDamage(1000);


        }
    }

    for(auto it = Asteroid_Objects.begin(); it != Asteroid_Objects.end();)
    {
        if ((*it)->health == 0) {

                //KillCount++;
                it = Asteroid_Objects.erase(it);
            
        }



           //std::cout<<"delete"<<std::endl;



        else{
            //window->draw((*it)->rect);
            //(*it)->move();
            ++it;
        }
    }

    for (auto it = Player->projectiles.begin(); it != Player->projectiles.end();) {
        if ((*it) != nullptr && (*it)->shouldDelete) {

            delete *it;
            it = Player->projectiles.erase(it);

        } else {
            window->draw((*it)->rect);
            (*it)->move();
            ++it;
        }
    }

    for (auto it = Enemy_bullets.begin(); it != Enemy_bullets.end();) {
        //if((*it) != nullptr && (*it)->shouldDelete){
        if ((*it)->health == 0) {
            //std::cout<<"breakpoint"<<std::endl;


            if ((*it)->exploding_projetile) {
                //std::cout<<"breakpoint"<<std::endl;
                window->draw(EX->getShape());
                //EX->rect.setPosition((*it)->rect.getPosition().x,(*it)->rect.getPosition().y);
                if ((*it)->Explotion_animation(EX, buffer, Explotion_Enemy, 100, 100)) {
                    (*it)->exploding_projetile = false;
                }

            } else {
                delete *it;
                it = Enemy_bullets.erase(it);
            }

        } else {
            window->draw((*it)->rect);
            (*it)->move();
            if ((*it)->rect.getGlobalBounds().intersects(Player->rect.getGlobalBounds())) {
                (*it)->takeDamage(Player->CollitionDamage);
                Player->takeDamage((*it)->CollitionDamage);
                std::cout << "Player health: " << Player->health << std::endl;
            }
            ++it;
        }
    }

    for (auto bullet: Enemy_bullets) {
        bullet->move();
        window->draw(bullet->rect);

    }


    for (auto it = Enemy_Objects.begin(); it != Enemy_Objects.end(); it++) {
        if ((*it)->shouldDelete) {
            if ((*it)->bound == 1) {
                std::cout << "bound: " << (*it)->bound << "ye" << std::endl;
                (*it)->bound = 0;
                it = Enemy_Objects.erase(it);
            } else {
                if ((*it)->health <= 0) {
                    score += (int) (((*it)->maxHealth) / 60.0);
                    money += (int) (((*it)->maxHealth / 5.0)) / 100.0;
                    std::cout << "Unit maxhealth is: " << (*it)->maxHealth << std::endl;
                    std::cout << "GameDiffculty is: " << GameDifficulty << std::endl;
                    std::cout << "Money is now: " << money << std::endl;
                }
                if ((*it)->health == 0) {
                    window->draw(EX->getShape());
                    if ((*it)->Explotion_animation(EX, buffer, Explotion_Enemy, 100, 100)) {
                        KillCount++;
                        it = Enemy_Objects.erase(it);

                    }
                }
            }
            std::cout<<"number: "<<number<<std::endl;
            std::cout<<"number enemy: "<<Enemy_number<<std::endl;
            std::cout<<"sqauads: "<<number_of_sqadron_on_level<<std::endl;

            if (number>=(Enemy_number*3)) {
                std::cout << "Enter Bossstage:" << std::endl;
                bossStage = true;
            }
            //std::cout<<"KillCount: "<<KillCount<<std::endl;
        }

    }
    //std::cout<<"KillCount: "<<KillCount<<std::endl;


    for (auto it = Boss_objects.begin(); it != Boss_objects.end(); it++) {
        if ((*it)->shouldDelete) {

            window->draw(EX->getShape());

            if ((*it)->BossExplotion(EX, buffer, Explotion_Enemy, 300, 300)) {
                it = Boss_objects.erase(it);
                bossStage = false;
                //end stage:
                Stageover = true;
            }
            if (Stageover) {
                //it = Boss_objects.erase(it);
                score += 1000 * GameDifficulty;
                //number_of_sqadron_on_level = 0;
                GameDifficulty = GameDifficulty * (score / targetScore);
                number = 0;
                music.stop();
                machine.SetState(Machine::StateId::MENU);
            }

        }

    }

    if (bossStage) {
        if (Enemy_Objects.empty() && Spawn_Boss) {
            //bossStage = true;
            CreateBoss();
            Player->Player_can_fire = false;
            Player_Fire = false;
            Spawn_Boss = false;
        }
    }

    ui.setHealthPercentage(Player->health / Player->maxHealth * 100.0f);
    ui.setEnergyPercentage(Player->Energy / Player->MaxEnergy * 100.0f);
    ui.setMoney(money);
    ui.setScore(score);
    ui.update();

    window->draw(Player->getShape());

    for (Object *obj : PlayerEquipment) {
        window->draw(obj->getShape());
    }

    for (Object *uiobject : ui.GetObjects()) {
        window->draw(uiobject->getShape());
    }

    for (sf::Text *txt : ui.GetLabels()) {
        window->draw(*txt);
    }

    for (auto it = MessageBoxes.begin(); it != MessageBoxes.end();) {
        if ((*it)->ShouldDraw()) {
            window->draw((*it)->rect);
            for (sf::Text *txt : (*it)->labels) {
                window->draw(*txt);
            }
        }
        ++it;
    }

    if (Player->health <= 0) {
        std::cout << "Game Over" << std::endl;
        window->draw(EX->getShape());
        if (Player->Explotion_animation(EX, buffer, Explotion_Enemy, 100, 100))
        {
                GameOverShape.setSize(sf::Vector2f(1200,800));
                GameOverShape.setPosition(0,0);
                GameOverShape.setTexture(&GameOver);
                window->draw(GameOverShape);
                window->display();
                //clock.restart();
                while(clock.getElapsedTime().asSeconds() <= 3)
                {
                    std::cout<<"stop"<<std::endl;
                }

                std::cout<<"meny"<<std::endl;
                music.stop();
                money = 0;
                Enemy_number = 0;
                GameDifficulty = 1.0;
                machine.SetState(Machine::StateId::MENU);



        }

    }

    window->display();

}

void level_1::CreateEnemySquadron(int spawnPoint, int health, int target, int amount, int Number) {
    for (int i = 0; i < amount; i++) {
        Enemy = new enemyShips(PP->targetPoints[spawnPoint].x, PP->targetPoints[spawnPoint].y, health, target, Number);
        Enemy_Buffer.push_back(Enemy);
    }
}

void level_1::CreateBoss() {
    this->Boss = new BossClass(500, 0, 1000 + (10 * GameDifficulty), &Boss_1, &Boss_1_bullet_1, 0.5);
    this->Boss_objects.push_back(this->Boss);
}

void level_1::CreateAsteroids(int health, int amount) {
    ypos = -100;
    for (int i = 0; i < amount; i++) {

        xpos = randomGen.pos(randomGen.mt);
        ypos -= randomGen.asteroidSpacer(randomGen.mt);
        Asteroid = new asteroid(health, xpos, ypos);
        Asteroid_Buffer.push_back(Asteroid);

    }
}