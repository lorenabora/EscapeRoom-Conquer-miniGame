#include "Knight.h"

//constructor parametrizat cu apel la constructorul din clasa parinte
Knight::Knight(sf::Vector2f position)
    : Entity(200.f, 200.f, sf::Vector2f(280.f, 280.f), position, "knightR.png")
{}

//functie de clonare/copiere a unei entitati knight
std::unique_ptr<Entity> Knight::clone() const
{
    return std::make_unique<Knight>(*this);
}

//functie de scriere in consola a unor mesaje depinzand de stadiul jocului
std::string Knight::getLevelMessage(int gameStage) const
{
    if (gameStage == 1) return "One more to go!";
    if (gameStage == 2) return "What is happening? Oh, no...the King arises!";
    return "";
}

//functie suprascrisa pt miscarea cavalerilor automat
void Knight::moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& knight, Entity* player)
{
    float speed = 250.f;
    sf::Vector2f enemyPosition = knight.getEntity().getPosition();
    sf::Vector2f playerPosition = player->getEntity().getPosition();
    sf::Vector2f direction = playerPosition - enemyPosition;
    float dist = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (dist > 5.f)
    {
        direction /= dist;  //normalizez directia 
        float angleRad = std::atan2(direction.y, direction.x);
        float angleDeg = angleRad * 180.f / 3.14159265f;
        knight.getEntity().setRotation(sf::degrees(angleDeg + 0.f));    //pentru o miscare mai smooth pe directie
        sf::RectangleShape newPlayer = player->getEntity();
        newPlayer.move(direction * speed * delta_t);
        if (isPlayerWithinWalls(walls, newPlayer))
        {//simulez o miscare pentru a verifica daca am parte de collisions sau nu
            knight.getEntity().move(direction * speed * delta_t);
        }
    }
    else
    {
        float angleRad = std::atan2(playerPosition.y - enemyPosition.y, playerPosition.x - enemyPosition.x);
        float angleDeg = angleRad * 180.f / 3.14159265f;
        knight.getEntity().setRotation(sf::degrees(angleDeg + 0.f));
    }
}

//functie suprascrisa de atac asupra eroului, determinata de o distanta intre cele doua pozitii
void Knight::attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& playerHP, sf::Clock& attackTimer)
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