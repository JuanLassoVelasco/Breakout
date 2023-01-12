#ifndef __GAME_H__
#define __GAME_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gameHeaders/spriteRenderer.h>
#include <gameHeaders/gameLevel.h>
#include "vector"

enum GameState 
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
private:
    GameState State;
    bool Keys[1024];
    unsigned int gameWidth;
    unsigned int gameHeight;
    std::vector<GameLevel> Levels;
    unsigned int Level;
public:
    Game(unsigned int w, unsigned int h);
    ~Game();
    void Init();
    bool GetKey(int key) {return Keys[key];}
    GameState GetGameState() {return State;}
    unsigned int GetScreenWidth() {return gameWidth;}
    unsigned int GetScreenHeight() {return gameHeight;}
    void SetKey(int key, bool value);
    void SetGameState(GameState newState);
    void SetScreenWidth(unsigned int newWidth);
    void SetScreenHeight(unsigned int newHeight);
    void SetScreenWidthAndHeight(unsigned int newWidth, unsigned int newHeight);
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};

#endif
