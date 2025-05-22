#pragma once

#ifndef GAME_H
#define GAME_H

#include "Entity.h" 
#include "Hero.h" 
#include "Knight.h" 
#include "King.h"
#include "Subjects.h"
#include "SFML/Audio.hpp"

enum class GameState { Menu, Playing, GameOver }; 

class Game: public Subjects
{
private:
    static Game* instance; //incerc sa implementez Singleton pattern

    sf::RenderWindow window;
    GameState gameState = GameState::Menu; 
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

    sf::Music bgMusic;

    Game();

public:
    //Game();
    //~Game(){}

    //Obtinem instanta unica
    static Game* getInstance() 
    {
        if (!instance) instance = new Game();
        return instance;
    }

    static void destroyInstance() 
    { 
        //Curatam instanta la final
        delete instance;
        instance = nullptr;
    }
    void updateGameHealth() 
    {
        notifyObservers("Update Health Bar");  //acum Game notifica observatorii
    }
    //musica de fundal pentru ca de ce nu
    void playBackgroundMusic() {
        if (!bgMusic.openFromFile("Epic-Action-Battle-Medieval-Background-Music-_No-Copyright_.ogg")) {
            std::cerr << "Error loading background music!" << std::endl;
            return;
        }
        if (bgMusic.getStatus() != sf::SoundSource::Status::Playing) {
            bgMusic.play();
        }
        bgMusic.setVolume(30);  // ajustare volum
        bgMusic.play();         // play
    }

    //Dezactivam copierea
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

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
    //void changeTexture(sf::RectangleShape& player, const std::string& newTexture);

    template <typename T> //acum pot schimba textura oricarui obiect desenabil care permite adaugarea unei texturi
    void changeTexture(T& entity, const std::string& newTextureFile)
    {
        auto* newSkin = new sf::Texture();
        if (!newSkin->loadFromFile(newTextureFile))
        {
            std::cerr << "Error loading texture: " << newTextureFile << std::endl;
            delete newSkin;
            return;
        }

        entity.setTexture(newSkin);

        sf::IntRect textureRect(sf::Vector2i(0, 0), sf::Vector2i(static_cast<int>(newSkin->getSize().x), static_cast<int>(newSkin->getSize().y)));
        entity.setTextureRect(textureRect);
    }
    void betweenKnights(sf::RectangleShape& knight1, const sf::RectangleShape& knight2, const sf::ConvexShape& walls);
    void update();
    void render();
};

#endif