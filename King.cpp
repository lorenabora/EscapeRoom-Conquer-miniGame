#include "King.h"

King::King(sf::Vector2f position)
    : Entity(250.f, 250.f, sf::Vector2f(300.f, 300.f), position, "kingTexture.png")
{}

std::unique_ptr<Entity> King::clone() const
{
    return std::make_unique<King>(*this);
}

std::string King::getLevelMessage(int gameStage) const
{
    if (gameStage == 3) return "Yohooo! Finally I can say Game Over!";
    return "";
}

void King::moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& king, Entity* player)
{
    float speed = 250.f;
    sf::Vector2f enemyPosition = king.getEntity().getPosition();
    sf::Vector2f playerPosition = player->getEntity().getPosition();
    sf::Vector2f direction = playerPosition - enemyPosition;
    float dist = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (dist > 5.f)
    {
        direction /= dist;
        float angleRad = std::atan2(direction.y, direction.x);
        float angleDeg = angleRad * 180.f / 3.14159265f;
        king.getEntity().setRotation(sf::degrees(angleDeg + 0.f));
        sf::RectangleShape newPlayer = player->getEntity();
        newPlayer.move(direction * speed * delta_t);
        if (isPlayerWithinWalls(walls, newPlayer))
        {
            king.getEntity().move(direction * speed * delta_t);
        }
    }
    else
    {
        float angleRad = std::atan2(playerPosition.y - enemyPosition.y, playerPosition.x - enemyPosition.x);
        float angleDeg = angleRad * 180.f / 3.14159265f;
        king.getEntity().setRotation(sf::degrees(angleDeg + 0.f));
    }
}

void King::attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& playerHP, sf::Clock& attackTimer)
{
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f enemyPos = enemy.getPosition();
    float distance = std::sqrt(std::pow(playerPos.x - enemyPos.x, 2) + std::pow(playerPos.y - enemyPos.y, 2));
    if (distance <= attackRange && attackTimer.getElapsedTime().asSeconds() >= 1.5f)
    {
        playerHP -= 10.f;
        attackTimer.restart();
    }
}

void King::dodgeAttack(sf::RectangleShape& king, sf::RectangleShape& player, const sf::ConvexShape& walls)
{
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f kingPos = king.getPosition();
    sf::Vector2f direction = kingPos - playerPos;
    float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (length < 50.f)
    {
        direction /= length;
        float distanceFactor = (1.0f >= 200.0f / length ? 1.0f : 200.f / length);
        float randomMove = static_cast<float>(rand() % 50 + 10) * distanceFactor;
        sf::Vector2f newPos = kingPos + (direction * randomMove);
        if (walls.getGlobalBounds().contains(newPos))
        {
            king.move(-direction * randomMove);
        }
        else
        {
            std::cout << "Dodge failed! King stays inside the battlefield.\n";
        }
    }
}