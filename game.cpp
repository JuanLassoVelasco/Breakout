#include <gameHeaders/game.h>

Game::Game(unsigned int w, unsigned int h): State(GAME_ACTIVE), Keys(), width(w), height(h) 
{

}

Game::~Game()
{

}

void Game::Init() 
{

}

void Game::SetKey(int key, bool value) 
{
    Keys[key] = value;
}

void Game::SetGameState(GameState newState) 
{
    State = newState;
}

void Game::SetScreenWidth(unsigned int newWidth) 
{
    width = newWidth;
}

void Game::SetScreenHeight(unsigned int newHeight) 
{
    height = newHeight;
}

void Game::SetScreenWidthAndHeight(unsigned int newWidth, unsigned int newHeight)
{
    width = newWidth;
    height = newHeight;
}

void Game::ProcessInput(float dt) 
{

}

void Game::Update(float dt) 
{

}

void Game::Render() 
{

}
