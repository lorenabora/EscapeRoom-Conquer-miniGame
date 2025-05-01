#include "Entity.h"

Entity::Entity(float hp, float maxHP, sf::Vector2f size, sf::Vector2f position, const std::string& textureFile)
    : hp(hp), maxHP(maxHP), gameStage(gameStage)
{
    entity.setSize(size);
    entity.setPosition(position);
    entity.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));

    entityTexture.loadFromFile(textureFile);
    entity.setTexture(&entityTexture);

    hpBar.setSize(sf::Vector2f(maxHP, 25.f));
    hpBar.setPosition(position);
}
sf::RectangleShape& Entity::getEntity()
{
    return entity;
}
sf::RectangleShape& Entity::getHPBar() 
{ 
    return hpBar; 
}
float& Entity::getHP() 
{ 
    return hp; 
}
void Entity::updateHPBar(float currentHP, sf::RectangleShape& hpBar, float maxHP)
{
    if (currentHP < 0)
    {
        currentHP = 0;
    }
    float newWidth = static_cast<float>((currentHP / maxHP) * 200.f) >= 5.f ? static_cast<float>((currentHP / maxHP) * 200.f) : 5.f;
    hpBar.setSize(sf::Vector2f(newWidth, 25.f));
    if (currentHP <= maxHP * 0.25f)
    {
        hpBar.setFillColor(sf::Color::Red);
    }
    else
    {
        hpBar.setFillColor(sf::Color::Green);
    }
}
void Entity::moveHPBar(sf::RectangleShape& player, sf::RectangleShape& hpBar, sf::ConvexShape& walls, float delta_t, float speed)
{
    sf::Vector2f hpBarPosition = hpBar.getPosition();
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2f hpOffset(-105.f, -140.f);
    sf::Vector2f targetPosition = playerPosition + hpOffset;
    sf::Vector2f direction = targetPosition - hpBarPosition;
    float dist = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));

    if (dist != 0)
    {
        direction /= dist;
    }
    sf::Vector2f potentialPosition = hpBarPosition + (direction * speed * delta_t);
    sf::RectangleShape testHPBar = hpBar;
    testHPBar.setPosition(potentialPosition);

    if (isPlayerWithinWalls(walls, testHPBar))
    {
        hpBar.setPosition(potentialPosition);
    }
}
bool Entity::isAlive() const
{
    return hp >= 5.f;
}

bool Entity::isPointInsideConvexShape(const sf::ConvexShape& polygon, const sf::Vector2f& p)
{
    const size_t count = polygon.getPointCount();
    if (count < 3)
    {
        return false;
    }

    sf::Transform transform = polygon.getTransform();
    float prevCross = 0.f;

    for (size_t i = 0; i < count; ++i)
    {
        sf::Vector2f curr = transform.transformPoint(polygon.getPoint(i));
        sf::Vector2f next = transform.transformPoint(polygon.getPoint((i + 1) % count));
        sf::Vector2f edge = next - curr;
        sf::Vector2f toPoint = p - curr;
        float cross = edge.x * toPoint.y - edge.y * toPoint.x;

        if (i == 0)
        {
            prevCross = cross;
        }
        else
        {
            if (cross * prevCross < 0)
                return false;
        }
    }
    return true;
}

bool Entity::isPlayerWithinWalls(const sf::ConvexShape& walls, const sf::RectangleShape& player)
{
    const auto bounds = player.getGlobalBounds();
    sf::Vector2f center(bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f);
    try
    {
        if (!isPointInsideConvexShape(walls, center))
        {
            throw InvalidMovementException();
        }
    }
    catch (const InvalidMovementException& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

void Entity::draw(sf::RenderWindow& window)
{
    if (isAlive())
    {
        window.draw(entity);
        window.draw(hpBar);
    }
}