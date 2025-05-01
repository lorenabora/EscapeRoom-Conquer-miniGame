#pragma once

#ifndef HERO_H
#define HERO_H

#include "Entity.h"

class Hero : public Entity
{
public:
    Hero(sf::Vector2f position);
    std::unique_ptr<Entity> clone() const override;
    std::string getLevelMessage(int gameStage) const override;

    void moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& player, Entity* enemy = nullptr) override;

    void attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& enemyHP, sf::Clock& attackTimer) override;
};

#endif