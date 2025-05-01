#pragma once

#ifndef KING_H
#define KING_H

#include "Entity.h"

class King : public Entity
{
public:
    King(sf::Vector2f position);
    std::unique_ptr<Entity> clone() const override;
    std::string getLevelMessage(int gameStage) const override;

    void moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& king, Entity* player = nullptr) override;
    void attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& playerHP, sf::Clock& attackTimer) override;
    void dodgeAttack(sf::RectangleShape& king, sf::RectangleShape& player, const sf::ConvexShape& walls);
};

#endif