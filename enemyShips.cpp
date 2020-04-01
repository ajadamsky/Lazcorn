//
// Created by BearMace on 06/11/2017.
//

#include <random>
#include "enemyShips.h"
#include "gameConfig.h"



sf::Texture* enemy_texture_ptr;
int * enemy_target_ptr;


enemyShips::enemyShips(int x, int y, int health,int target,int number) {
    enemy_texture_ptr = &enemy_texture;
    enemy_target_ptr = &target;

    enemy_texture.loadFromFile("Assets/Nation1_Enemy_ship_1.png");


    this->rect.setTexture(enemy_texture_ptr);
    this->rect.setPosition(x,y);
    //this->rect.setFillColor(sf::Color::Red);
    this->health = health;
    this->maxHealth = health;
    this->PathNumber = number;
    this->rect.setSize(sf::Vector2f(100,100));
    this->CollitionDamage = 10;
    this->weapons[0] = new equipment(*AvailableEquipment[0]);
    this->weapons[1] = new equipment(*AvailableEquipment[0]);
    this->weapons[2] = new equipment(*AvailableEquipment[0]);
    this->HealthBarBackground->setPosition(500,500);
    this->HealthBar->setPosition(500,500);
    this->HealthBarBackground->setSize(sf::Vector2f(this->getShape().getSize().x, 10));
    this->HealthBar->setOrigin(0,0);
    this->HealthBar->setSize(sf::Vector2f(this->getShape().getSize().x-4, 10));
    this->HealthBarBackgroundTexture.loadFromFile("Assets/energy-bar.png");
    this->HealthBarTexture.loadFromFile("Assets/health-bar.png");
    this->HealthBar->setTexture(&HealthBarTexture);
    this->HealthBarBackground->setTexture(&HealthBarBackgroundTexture);
}

void enemyShips::shoot(equipment* weapon, sf::Vector2f velocity)
{
    if(weapon->clock.getElapsedTime().asSeconds() > weapon->FireRate) {
        Object *p = new Object(0, 0, 1.0f, 1.0f, weapon->projectile->ObjectTexture(), weapon->projectile->rect.getSize().x, weapon->projectile->rect.getSize().y);
        p->CollitionDamage = 30.0f;
        p->rect.setPosition(weapon->getShape().getPosition().x + 10, weapon->getShape().getPosition().y);
        p->velocity = velocity;
        p->parent = this;
        projectiles.push_back(p);
        weapon->clock.restart();
    }
}

enemyShips::enemyShips() {
    this->rect.setPosition(0,0);
    this->health = this->maxHealth;
}


int enemyShips::enemymovement(enemyShips* eneobj, float time,pathPoints* PP,sf::Vector2f Player,int PlayerWidth, std::vector<Object*> *Bulllet_list)
{
    //std::cout<<"Number of targets: "<<PathNumber;
    Direction.x = PP->targetPoints[target].x - rect.getPosition().x;
    Direction.y = PP->targetPoints[target].y - rect.getPosition().y;

    float hyp = sqrt(Direction.x*Direction.x+Direction.y*Direction.y);

    Direction.x   /=  hyp;
    Direction.y   /=  hyp;

    //x += dirX*speed*delta;

    velocity.x = Direction.x*speed*time;
    velocity.y = Direction.y*speed*time;


    //std::cout<<"ships x velocity: "<<eneobj->velocity.x<<std::endl;
    //std::cout<<"ships y velocity: "<<eneobj->velocity.y<<std::endl;



    //Enemy Shooting Player logic algoritme.


    int i = int(this->rect.getPosition().x+0.5);
    int y = int(this->rect.getPosition().y +0.5);

    //std::cout<<"ship coordinates x: "<<i<<std::endl;
    //std::cout<<"ship coordinates y: "<<y<<std::endl;


    if(i < PP->targetPoints[this->target].x+5 && i > PP->targetPoints[this->target].x-5  &&
       y   <  PP->targetPoints[this->target].y+5 && y   >  PP->targetPoints[this->target].y-5) {
        /*if (this->Enemy_out_of_bound) {
            std::cout << "Enemy out of bound\n" << std::endl;
        }*/

        if (PathCount == PathNumber) {
            //this->target = spawn(el);
            this->target = rand()%3;
            std::cout<<"target"<<target<<std::endl;
            //this->Enemy_out_of_bound = true;
            //this->Out_bound = true;
            bound = 1;
            if(exit){
                std::cout << "exittarget: " << target;
                shouldDelete = true;
            }
            exit = true;

        }
            /*else
            {
                        this->target = spawn(el);
                        this->Enemy_out_of_bound = true;
                        std::cout << "exittarget: " << target;
            }*/



            //target  =   rand()%4;
        else {
            //this->target = targetPoint(el);
            this->target = rand()% 10 +4;
            PathCount++;
            //this->Enemy_out_of_bound = true;
            //std::cout<<"current target: "<<target;
        }
    }
        //}


        //std::cout<<"target"<<target<<std::endl;
        //=3;
    if(EnemyFire){
        Enemy_fire(time);
        for(int i = 0; i < 1; i++) {
            if (Player.x < weapons[i]->rect.getPosition().x + rect.getSize().x + range &&
                Player.x > weapons[i]->rect.getPosition().x - range && can_fire) {

                shoot(weapons[i], sf::Vector2f(0.0f, 10.0f));
                weapons[i]->can_fire = false;
            }

        }
    /*Enemy_fire(time);
    if(Player.x<rect.getPosition().x+rect.getSize().x+range&&Player.x>rect.getPosition().x-range&&can_fire)
    {
        //std::cout<<"Boss fire!"<<std::endl;
        buffer.loadFromFile("Sounds/fighter_laser.wav");
        sound.setBuffer(buffer);
        sound.play();
        Object* bullet = new Object(rect.getPosition().x+rect.getSize().x/2,rect.getPosition().y+rect.getSize().y,1.0f,1.0f,Project_Texture,30,30);
        bullet->velocity= sf::Vector2f(0.0f,15.0f);
        bullet->rect.setRotation(180);
        Bulllet_list->push_back(bullet);
        can_fire = false;
    }*/
}
}

void enemyShips::Enemy_fire(float time)
{
    if(FireClock.getElapsedTime().asSeconds()>fireRate)
    {
        //std::cout<<"Boss shooting"<<std::endl;
        can_fire = true;
        FireClock.restart();
    }
}
void enemyShips::moveOverride() {
    weapons[0]->rect.setPosition(this->rect.getPosition().x, this->rect.getPosition().y + 25);
    HealthBarBackground->setPosition(this->rect.getPosition().x, this->rect.getPosition().y);
    HealthBar->setPosition(this->rect.getPosition().x+2, this->rect.getPosition().y+1);
    HealthBar->setScale(health/maxHealth, 1);
}
