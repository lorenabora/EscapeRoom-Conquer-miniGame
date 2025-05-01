#include <Windows.h>
#include "Game.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    Game game;
    game.run();
    return 0;
}