#include <gameHeaders/game.h>
#include <glm/ext/matrix_clip_space.hpp>

SpriteRenderer *Renderer;

Game::Game(unsigned int w, unsigned int h): State(GAME_ACTIVE), Keys(), width(w), height(h) 
{
    
}

Game::~Game()
{

}

void Game::Init() 
{
    ResourceLoader::LoadShader("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/shaders/vertexShader.vs", "/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/shaders/fragmentShader.fs", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceLoader::GetShader("sprite").use();
    ResourceLoader::GetShader("sprite").SetInteger("image", 0);
    ResourceLoader::GetShader("sprite").SetMatrix4("projection", projection);

    Shader spriteShader = ResourceLoader::GetShader("sprite");

    Renderer = new SpriteRenderer(spriteShader);

    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/awesomeface.png", true, "face");
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
    Texture2D spriteTexture = ResourceLoader::GetTexture("face");

    Renderer->DrawSprite(spriteTexture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
