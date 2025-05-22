#include <Windows.h>
#include "Game.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    /*Game game;
    game.run();
    return 0;*/ //inainte de singleton pattern

    //dupa singleton pattern applied
    Game* game = Game::getInstance();  // instanta unica
    HealthUI ui;
    Hero hero;

    game->run(); 
    hero.addObserver(&ui);  // Conectez UI-ul ca observator
    hero.updateHPBar(25, hero.getHPBar(), 100);  // Jucatorul pierde HP ? UI-ul este notificat

    Game::destroyInstance();  // curatenia de final
    return 0;
}