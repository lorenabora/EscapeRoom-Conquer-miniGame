#include "Game.h"

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "EscapeRoom: Conquer"),
    safeZone(sf::Vector2f({ 850.f,1720.f })),
    chest(sf::Vector2f(150.f, 370.f))
{
    try
    {
        if (!font.openFromFile("BASKVILL.TTF"))
        {
            throw FileLoadingException();
        }
        playButton = std::make_unique<sf::Text>(font);
        gameOverText = std::make_unique<sf::Text>(font);
        gameMessage = std::make_unique<sf::Text>(font);
        playButton->setString("Play");
        gameOverText->setString("Game Over");
        gameMessage->setString("HINT: Don't forget the sword~");
        gameMessage->setCharacterSize(40);
        gameMessage->setFillColor(sf::Color::White);
        gameMessage->setPosition(sf::Vector2f(10.f, 20.f));
    }
    catch (const FileLoadingException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    int firstKnight = 0;
    hero = std::make_unique<Hero>(sf::Vector2f(2730.f, 790.f));
    king = std::make_unique<King>(sf::Vector2f(150.f, 780.f));
    addKnights();
    for (auto& knight : knights)
    {
        if (!firstKnight)
        {
            knight = std::make_unique<Knight>(sf::Vector2f(300.f, 500.f));
            firstKnight++;
        }
        else
        {
            knight = std::make_unique<Knight>(sf::Vector2f(300.f, 1100.f));
        }
    }
    Hero* heroPtr = dynamic_cast<Hero*>(hero.get());
    King* kingPtr = dynamic_cast<King*>(king.get());
    initializeWalls();
    initializeChest();
    initializeSafeZone();
    initializeBackground();
    initializeUI();
}

void Game::addKnights()
{
    knights.push_back(std::make_unique<Knight>(sf::Vector2f(300.f, 500.f)));
    knights.push_back(knights[0]->clone());
}

std::string Game::getGameMessage() const
{
    if (gameStage == 1) return "One more to go!";
    if (gameStage == 2) return "What is happening? Oh, no...the King arises!";
    if (gameStage == 3) return "Yohooo! Finally I can say Game Over!";
    return "";
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::initializeWalls()
{
    walls.setPointCount(6);
    walls.setPoint(0, { 500.f, 40.f });
    walls.setPoint(1, { 2850.f, 40.f });
    walls.setPoint(2, { 2850.f, 1760.f });
    walls.setPoint(3, { 500.f, 1760.f });
    walls.setPoint(4, { 40.f, 1409.f });
    walls.setPoint(5, { 40.f, 350.f });
    walls.setFillColor(sf::Color::Transparent);
    walls.setOutlineThickness(3.f);
    walls.setOutlineColor(sf::Color(0, 25, 51));
}
void Game::initializeChest()
{
    chest.setFillColor(sf::Color::Transparent);
    chest.setOutlineThickness(3.f);
    chest.setOutlineColor(sf::Color::Magenta);
    chest.setPosition(sf::Vector2f(2700.0f, 1150.0f));
}
void Game::initializeSafeZone()
{
    safeZone.setPosition(sf::Vector2f({ 2200.f, 40.f }));
    safeZone.setOutlineColor(sf::Color::Black);
}
void Game::initializeBackground()
{
    if (!backgroundTexture.loadFromFile("backgroundGame.jpeg"))
    {
        std::cerr << "Error: Could not load background image!\n";
    }
    else
    {
        backgroundSprite = std::make_unique<sf::Sprite>(backgroundTexture);
        backgroundSprite->setScale(sf::Vector2f(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y)
        );
    }
}

void Game::initializeUI() 
{
    startScreen.setSize(sf::Vector2f(3000.f, 2000.f));
    startScreen.setFillColor(sf::Color(0,0,0,200));  // Semi-transparent for blur effect

    playButton->setFont(font);
    playButton->setString("Play");
    playButton->setCharacterSize(100);
    playButton->setPosition(sf::Vector2f(1350.f, 800.f));
    playButton->setFillColor(sf::Color::Green);

    blurEffect.setSize(sf::Vector2f(3000.f, 2000.f));
    blurEffect.setFillColor(sf::Color(0, 0, 0, 200));  // Semi-transparent overlay

    gameOverText->setFont(font);
    gameOverText->setString("Game Over");
    gameOverText->setCharacterSize(100);
    gameOverText->setPosition(sf::Vector2f(1200.f, 800.f));
    gameOverText->setFillColor(sf::Color::Red);
}

void Game::updateGameMessage()
{
    if (gameStage == 1)
    {
        gameMessage->setString("One more to go!");
    }
    else if (gameStage == 2)
    {
        gameMessage->setString("What is happening? Oh no... The King arises!");
    }
    else if (gameStage == 3)
    {
        gameMessage->setString("Yohooo! Finally, I can say Game Over!");
    }
}

void Game::handleEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (gameState == GameState::Menu) 
        {
            if (const auto* resizedEvent = event->getIf<sf::Event::Resized>()) {
                sf::Vector2u newSize = resizedEvent->size;
                sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(static_cast<float>(newSize.x), static_cast<float>(newSize.y)));
                window.setView(sf::View(visibleArea));
                backgroundSprite->setScale(sf::Vector2f(
                    static_cast<float>(newSize.x) / backgroundTexture.getSize().x,
                    static_cast<float>(newSize.y) / backgroundTexture.getSize().y)
                );
            }
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) 
            { 
                if (playButton->getGlobalBounds().contains(sf::Vector2f(mousePressed->position))) 
                {
                    gameState = GameState::Playing; 
                }
            }
        }
    }
}

bool Game::isInSafeZone(const sf::RectangleShape& zone, const sf::RectangleShape& player)
{
    return zone.getGlobalBounds().contains(player.getPosition());
}
void Game::changeTexture(sf::RectangleShape& player, const std::string& newTexture)
{
    auto* newSkin = new sf::Texture();
    if (!newSkin->loadFromFile(newTexture))
    {
        std::cerr << "Error loading texture: " << newTexture << std::endl;
        delete newSkin;
        return;
    }

    player.setTexture(newSkin);

    sf::IntRect textureRect(sf::Vector2i(0, 0), sf::Vector2i(static_cast<int>(newSkin->getSize().x), static_cast<int>(newSkin->getSize().y)));
    player.setTextureRect(textureRect);
}
void Game::betweenKnights(sf::RectangleShape& knight1, const sf::RectangleShape& knight2, const sf::ConvexShape& walls)
{
    sf::Vector2f posK1 = knight1.getPosition(), posK2 = knight2.getPosition();
    sf::Vector2f direction = posK1 - posK2;
    float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (length > 0)
    {
        direction /= length;
        if (length < 200.f)
        {
            sf::Vector2f newPos = posK1 + (direction * (200.f - length));
            if (walls.getGlobalBounds().contains(newPos)) {
                knight1.move(direction * (200.f - length));
            }
        }
    }
}

void Game::update()
{
    if (gameState != GameState::Playing) return;

    updateGameMessage();
    bool ok = 0, kingOk = 0;
    float m_delta_t = clock.restart().asSeconds();
    hero->moveEntity(walls, m_delta_t, *hero);
    hero->moveHPBar(hero->getEntity(), hero->getHPBar(), walls, m_delta_t, 400.f);
    for (auto& knight : knights)
    {
        knight->moveHPBar(knight->getEntity(), knight->getHPBar(), walls, m_delta_t, 250.f);
    }
    king->moveHPBar(king->getEntity(), king->getHPBar(), walls, m_delta_t, 250.f);

    if (!isInSafeZone(safeZone, hero->getEntity()))
    {
        if (Hero* heroPtr = dynamic_cast<Hero*>(hero.get()))
        {
            for (auto& knight : knights)
            {
                knight->moveEntity(walls, m_delta_t, *knight, heroPtr);
            }
        }
    }
    betweenKnights(knights[0]->getEntity(), knights[1]->getEntity(), walls);

    if (isInSafeZone(chest, hero->getEntity()) && !ok)
    {
        ok = 1;
        changeTexture(hero->getEntity(),"heroWithSword.png");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        for (auto& knight : knights)
        {
            if (knight->getHP() > 0.f)
            {
                hero->attack(hero->getEntity(), knight->getEntity(), 200.f, knight->getHP(), heroAttackTimer);
            }
        }
        if (gameStage == 2)
        {
            hero->attack(hero->getEntity(), king->getEntity(), 200.f, king->getHP(), heroAttackTimer);
        }
    }

    if (knights[0]->getHP() <= 0.f)
    {
        knights[0]->getEntity().setPosition(sf::Vector2f(-1000.f, -1000.f));
        gameStage = 1;
        knightAlive = 1;
    }
    else if (knights[1]->getHP() <= 0.f)
    {
        knights[1]->getEntity().setPosition(sf::Vector2f(-1000.f, -1000.f));
        gameStage = 1;
        knightAlive = 0;
    }
    if (knights[0]->getHP() <= 0.f && knights[1]->getHP() <= 0.f)
    {
        knights[knightAlive]->getEntity().setPosition(sf::Vector2f(-1000.f, -1000.f));
        gameStage = 2;
    }
    if (gameStage == 2)
    {
        if (King* kingPtr = dynamic_cast<King*>(king.get()))
        {
            king->moveEntity(walls, m_delta_t, *kingPtr, dynamic_cast<Hero*>(hero.get()));
            if (!kingOk)
            {
                kingOk = 1;
                changeTexture(king->getEntity(), "kingWithSword.png");
            }
        }
    }
    if (king->getHP() <= 5.f)
    {
        king->getEntity().setPosition(sf::Vector2f(-1000.f, -1000.f));
        gameStage = 3;
    }
    if (hero->getHP() <= 5.f)
    {
        hero->getEntity().setPosition(sf::Vector2f(5000.f, 780.f));
        gameState = GameState::GameOver;
    }
    for (auto& knight : knights)
    {
        knight->attack(hero->getEntity(), knight->getEntity(), 100.f, hero->getHP(), enemyAttackTimer);
        knight->updateHPBar(knight->getHP(), knight->getHPBar(), 200.f);
    }

    king->attack(hero->getEntity(), king->getEntity(), 180.f, hero->getHP(), enemyAttackTimer);
    King* kingPtr = dynamic_cast<King*>(king.get());
    if (kingPtr)
    {
        kingPtr->dodgeAttack(king->getEntity(), hero->getEntity(), walls);
    }

    hero->updateHPBar(hero->getHP(), hero->getHPBar(), 200.f);
    king->updateHPBar(king->getHP(), king->getHPBar(), 200.f);
}

void Game::render()
{
    window.clear();

    if (gameState == GameState::Menu)
    {
        renderMenu();
    }
    else if (gameState == GameState::Playing)
    {
        window.draw(walls);
        window.draw(chest);
        window.draw(safeZone);
        if (backgroundSprite)
        {
            window.draw(*backgroundSprite);
        }
        hero->draw(window);
        for (auto& knight : knights)
        {
            knight->draw(window);
        }
        king->draw(window);
        window.draw(*gameMessage);
    }
    else if (gameState == GameState::GameOver) 
    {
        renderGameOver();
    }
    window.display();
}

void Game::renderGameOver() 
{
    if (backgroundSprite)
    {
        window.draw(*backgroundSprite);
    }
    window.draw(blurEffect);
    window.draw(*gameOverText);
}

void Game::renderMenu() 
{
    if (backgroundSprite)
    {
        window.draw(*backgroundSprite);
    }
    window.draw(startScreen);  
    window.draw(*playButton);   
}

std::ostream& operator<<(std::ostream& os, const Game& game)
{
    os << game.getGameMessage();
    return os;
}