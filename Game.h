#pragma once

#ifndef GAME_H
#define GAME_H

#include "Entity.h" 
#include "Hero.h" 
#include "Knight.h" 
#include "King.h"

enum class GameState { Menu, Playing, GameOver }; //modificare

class Game
{
private:
    sf::RenderWindow window;
    GameState gameState = GameState::Menu; //modificare
    std::unique_ptr<Entity> hero;
    std::vector<std::unique_ptr<Entity>> knights;
    void addKnights();
    std::unique_ptr<Entity> king;
    sf::Clock clock, heroAttackTimer, enemyAttackTimer;
    sf::ConvexShape walls;
    sf::RectangleShape chest, safeZone;
    sf::Texture backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;
    //sf::Texture newSkin;
    int gameStage = 0, knightAlive = 0;
    sf::Font font;
    std::unique_ptr<sf::Text> gameMessage;

    sf::RectangleShape startScreen;
    std::unique_ptr<sf::Text> playButton;
    sf::RectangleShape blurEffect;
    std::unique_ptr<sf::Text> gameOverText;

public:
    Game();
    ~Game(){}

    std::string getGameMessage() const;
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    void run();

private:
    void initializeWalls();
    void initializeChest();
    void initializeSafeZone();
    void initializeBackground();

    void initializeUI(); 
    void renderMenu();  
    void renderGameOver(); 

    void updateGameMessage();
    void handleEvents();
    bool isInSafeZone(const sf::RectangleShape& zone, const sf::RectangleShape& player);
    void changeTexture(sf::RectangleShape& player, const std::string& newTexture);
    void betweenKnights(sf::RectangleShape& knight1, const sf::RectangleShape& knight2, const sf::ConvexShape& walls);
    void update();
    void render();
};

#endif