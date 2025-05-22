#pragma once

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Entity.h"

class Knight : public Entity
{
public:
    Knight(sf::Vector2f position);
    ~Knight() = default;
    std::unique_ptr<Entity> clone() const override;
    std::string getLevelMessage(int gameStage) const override;
    void moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& knight, Entity* player = nullptr) override;
    void attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& playerHP, sf::Clock& attackTimer) override;
};

#endif