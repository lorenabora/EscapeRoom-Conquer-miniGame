#pragma once

#ifndef HERO_H
#define HERO_H

#include "Entity.h"

class Hero : public Entity
{
public:
    Hero(){}
    Hero(sf::Vector2f position);
    ~Hero() = default;
    std::unique_ptr<Entity> clone() const override;
    std::string getLevelMessage(int gameStage) const override;
    //functie suprascrisa pentru a misca eroul in mod controlat de catre player
    void moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& player, Entity* enemy = nullptr) override;
    //functie care ataca inamicii intr-o anumita raza de actiune doar la apasarea tastei space 
    void attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& enemyHP, sf::Clock& attackTimer) override;
};

#endif