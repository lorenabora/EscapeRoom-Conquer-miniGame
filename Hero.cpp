#include "Hero.h"

Hero::Hero(sf::Vector2f position)
    : Entity(200.f, 200.f, sf::Vector2f(280.f, 280.f), position, "heroF-removebg-preview.png")
{
}

std::unique_ptr<Entity> Hero::clone() const
{
    return std::make_unique<Hero>(*this);
}

std::string Hero::getLevelMessage(int gameStage) const
{
    if (gameStage == 0) return "Let's get the party started!";
    return "";
}

void Hero::moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& player, Entity* enemy)
{
    const float speed = 400.f;
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        movement.y -= speed * delta_t;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        movement.y += speed * delta_t;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        movement.x -= speed * delta_t;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        movement.x += speed * delta_t;
    }

    if (movement.x != 0.f || movement.y != 0.f)
    {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement.x /= length;
        movement.y /= length;
        movement.x *= speed * delta_t;
        movement.y *= speed * delta_t;
        float rotationAngle = std::atan2(movement.y, movement.x);
        float rotationDeg = rotationAngle * 180.f / 3.14159265f;
        player.getEntity().setRotation(sf::degrees(rotationDeg + 180.f));
    }

    try
    {
        sf::RectangleShape newPlayer = player.getEntity();
        newPlayer.move(movement);
        if (!isPlayerWithinWalls(walls, newPlayer))
        {
            throw InvalidMovementException();
        }
        player.getEntity().move(movement);
    }
    catch (const InvalidMovementException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Hero::attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& enemyHP, sf::Clock& attackTimer)
{
    try
    {
        sf::Vector2f playerPos = player.getPosition();
        sf::Vector2f enemyPos = enemy.getPosition();

        float distance = std::sqrt(std::pow(playerPos.x - enemyPos.x, 2) + std::pow(playerPos.y - enemyPos.y, 2));

        if (distance <= attackRange && attackTimer.getElapsedTime().asSeconds() >= 0.5f)
        {
            enemyHP -= 10.f;
            attackTimer.restart();
        }
        else
        {
            throw InvalidAttackException();
        }
    }
    catch (const InvalidAttackException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}