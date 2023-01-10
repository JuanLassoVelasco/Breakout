#include <gameHeaders/game.h>
#include <glm/ext/matrix_clip_space.hpp>

SpriteRenderer *Renderer;

Game::Game(unsigned int w, unsigned int h): State(GAME_ACTIVE), Keys(), width(w), height(h) 
{
    
}

Game::~Game()
{
    // delete Renderer;
}

void Game::Init() 
{
    GameLevel lvlOne;
    GameLevel lvlTwo;
    GameLevel lvlThree;
    GameLevel lvlFour;

    float lvlHeight = height / 2;

    ResourceLoader::LoadShader("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/shaders/vertexShader.vs", "/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/shaders/fragmentShader.fs", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceLoader::GetShader("sprite").use();
    ResourceLoader::GetShader("sprite").SetInteger("image", 0);
    ResourceLoader::GetShader("sprite").SetMatrix4("projection", projection);

    Shader spriteShader = ResourceLoader::GetShader("sprite");

    Renderer = new SpriteRenderer(spriteShader);

    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/background.jpg", false, "background");
    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/block.png", false, "block");
    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/block_solid.png", false, "block_solid");
    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/awesomeface.png", true, "face");

    try
    {
        lvlOne.LoadLevel("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/levels/level1.txt", this->width, lvlHeight);
        lvlTwo.LoadLevel("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/levels/level2.txt", this->width, lvlHeight);
        lvlThree.LoadLevel("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/levels/level3.txt", this->width, lvlHeight);
        lvlFour.LoadLevel("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/levels/level4.txt", this->width, lvlHeight);
    }
    catch(const invalid_input & e)
    {
        std::cerr << e.what() << '\n';
    }

    this->Levels.push_back(lvlOne);
    this->Levels.push_back(lvlTwo);
    this->Levels.push_back(lvlThree);
    this->Levels.push_back(lvlFour);

    this->Level = 0;
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
    Texture2D backGroundTex = ResourceLoader::GetTexture("background");
    Texture2D faceTex = ResourceLoader::GetTexture("face");

    if (this->State == GAME_ACTIVE)
    {
        Renderer->DrawSprite(backGroundTex, glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height));

        if (this->Levels.size() <= 0) {return;}
        
        this->Levels[this->Level].DrawLevel(*Renderer);
    }
}
