#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <memory>
#include <exception>

#include "ExceptionsG.h"

class Entity
{
protected:
    sf::RectangleShape entity, hpBar;
    sf::Texture entityTexture;
    float hp, maxHP;
    int gameStage;

public:
    Entity(float hp, float maxHP, sf::Vector2f size, sf::Vector2f position, const std::string& textureFile);
    virtual ~Entity() = default;
    virtual std::unique_ptr<Entity> clone() const = 0;

    virtual std::string getLevelMessage(int gameStage) const = 0;

    sf::RectangleShape& getEntity();
    sf::RectangleShape& getHPBar();
    float& getHP();
    virtual void moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& entity, Entity* enemy = nullptr) = 0;
    virtual void attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& enemyHP, sf::Clock& attackTimer) = 0;
    void updateHPBar(float currentHP, sf::RectangleShape& hpBar, float maxHP);
    void moveHPBar(sf::RectangleShape& player, sf::RectangleShape& hpBar, sf::ConvexShape& walls, float delta_t, float speed);
    bool isAlive() const;
    bool isPointInsideConvexShape(const sf::ConvexShape& polygon, const sf::Vector2f& p);
    bool isPlayerWithinWalls(const sf::ConvexShape& walls, const sf::RectangleShape& player);
    void draw(sf::RenderWindow& window);
};

#endif