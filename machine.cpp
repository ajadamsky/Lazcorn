#include "machine.h"
#include "state.h"
#include "states/level_1.h"
#include "states/menu.h"
#include "states/stateInit.h"
#include "states/stateExit.h"
#include "states/shop.h"


Machine::Machine(){

    ammo1.loadFromFile("Sprites/Ammo/Ammo1.png");


    if(!laser_cannon_tx.loadFromFile("Assets/health-bar.png"))
        std::cout << "Error loading PlayerEquipmentTexture" << std::endl;
    else
        std::cout << "OK loading PlayerEquipmentTexture" << std::endl;

    rocket1.loadFromFile("Sprites/Ammo/Rocket_Missile.png");
    oblivirator1.loadFromFile("Assets/health-bar.png");

    if(!laser_cannon_tx.loadFromFile("Sprites/Ammo/Ammo1.png"))
        std::cout << "Error loading PlayerEquipmentTexture" << std::endl;

    if(!rocket_launcher_tx.loadFromFile("Sprites/Ammo/Rocket_Missile.png"))
        std::cout << "Error loading PlayerEquipmentTexture" << std::endl;

    if(!the_oblivirator_tx.loadFromFile("Assets/oblivirator.png"))
        std::cout << "Error loading PlayerEquipmentTexture" << std::endl;


    AvailableEquipment[0] = new equipment(0.5f, &laser, &laser_cannon_tx);
    AvailableEquipment[0]->tx = &laser_cannon_tx;
    AvailableEquipment[0]->rect.setSize(sf::Vector2f(30,30));
    AvailableEquipment[0]->Name = "Laser Cannon";
    AvailableEquipment[0]->UpgradeScale = 9;
    AvailableEquipment[0]->BaseDamage = 30;
    AvailableEquipment[0]->Level = 1;
    AvailableEquipment[0]->UpgradeCost = AvailableEquipment[0]->Level * 90;

    AvailableEquipment[1] = new equipment(0.5f, &rocket, &rocket_launcher_tx);
    AvailableEquipment[1]->tx = &rocket_launcher_tx;
    AvailableEquipment[1]->rect.setSize(sf::Vector2f(30,30));
    AvailableEquipment[1]->Name = "Rocket Launcher";
    AvailableEquipment[1]->UpgradeScale = 10;
    AvailableEquipment[1]->BaseDamage = 40;
    AvailableEquipment[1]->Level = 1;
    AvailableEquipment[1]->UpgradeCost = AvailableEquipment[1]->Level * 120;

    AvailableEquipment[2] = new equipment(0.5f, &oblivirator, &the_oblivirator_tx);
    AvailableEquipment[2]->tx = &the_oblivirator_tx;
    AvailableEquipment[2]->rect.setSize(sf::Vector2f(30,30));
    AvailableEquipment[2]->Name = "The Oblivirator";
    AvailableEquipment[2]->UpgradeScale = 5;
    AvailableEquipment[2]->BaseDamage = 10;
    AvailableEquipment[2]->Level = 1;
    AvailableEquipment[2]->UpgradeCost = AvailableEquipment[2]->Level * 500;

    PlayerEquipment[0] = new equipment(*AvailableEquipment[0]);
    PlayerEquipment[1] = new equipment(*AvailableEquipment[0]);
    PlayerEquipment[2] = new equipment(*AvailableEquipment[0]);

    running = true;

    state = StateId::INIT;

    //Write states
    //states.emplace(StateId::(nameofstate), new State(name));
    states.emplace(StateId::INIT, new StateInit());
    states.emplace(StateId::MENU, new StateMenu());
    states.emplace(StateId::EXIT, new StateExit());
    states.emplace(StateId::SHOP, new StateShop());
}

Machine::~Machine() {
    //Remove state from memory
    for(auto state: states){
        delete state.second;
    }

    states.clear();
}

void Machine::GoNext(sf::RenderWindow* window) {
    states[state]->GoNext(*this, window);
}

void Machine::SetState(StateId state) {
    this->state = state;
}

State* Machine::GetState() {
    return states[state];
}


void Machine::RestartLevel(){


    states.erase(StateId::level_1);
    states.emplace(StateId::level_1, new level_1());

    std::cout << "Test" << std::endl;
}