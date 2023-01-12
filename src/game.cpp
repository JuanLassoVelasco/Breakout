#include <gameHeaders/game.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <prefabs/ball.hpp>

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_SPEED(500.0f);

const glm::vec2 INIT_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

GameObject* Player;
Ball* GameBall;

SpriteRenderer *Renderer;

Game::Game(unsigned int w, unsigned int h): State(GAME_ACTIVE), Keys(), gameWidth(w), gameHeight(h) 
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

    float lvlHeight = gameHeight / 2;

    ResourceLoader::LoadShader("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/shaders/vertexShader.vs", "/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/shaders/fragmentShader.fs", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->gameWidth), static_cast<float>(this->gameHeight), 0.0f, -1.0f, 1.0f);

    ResourceLoader::GetShader("sprite").use();
    ResourceLoader::GetShader("sprite").SetInteger("image", 0);
    ResourceLoader::GetShader("sprite").SetMatrix4("projection", projection);

    Shader spriteShader = ResourceLoader::GetShader("sprite");

    Renderer = new SpriteRenderer(spriteShader);

    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/background.jpg", false, "background");
    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/block.png", false, "block");
    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/block_solid.png", false, "block_solid");
    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/paddle.png", true, "paddle");
    ResourceLoader::LoadTexture("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/assets/awesomeface.png", true, "face");

    Texture2D playerSprite = ResourceLoader::GetTexture("paddle");
    Texture2D ballSprite = ResourceLoader::GetTexture("face");

    try
    {
        lvlOne.LoadLevel("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/levels/level1.txt", this->gameWidth, lvlHeight);
        lvlTwo.LoadLevel("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/levels/level2.txt", this->gameWidth, lvlHeight);
        lvlThree.LoadLevel("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/levels/level3.txt", this->gameWidth, lvlHeight);
        lvlFour.LoadLevel("/home/juan-ros-workspace/Documents/OpenGL_Dev/Breakout/levels/level4.txt", this->gameWidth, lvlHeight);
    }
    catch(const invalid_input & e)
    {
        std::cerr << e.what() << '\n';
    }

    this->Levels.push_back(lvlOne);
    this->Levels.push_back(lvlTwo);
    this->Levels.push_back(lvlThree);
    this->Levels.push_back(lvlFour);

    this->Level = 3;

    glm::vec2 playerPos = glm::vec2(this->gameWidth / 2.0f - PLAYER_SIZE.x / 2.0f, this->gameHeight - PLAYER_SIZE.y);
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

    Player = new GameObject(playerPos, PLAYER_SIZE, false, playerSprite);
    GameBall = new Ball(ballPos, BALL_RADIUS, INIT_BALL_VELOCITY, ballSprite);
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
    gameWidth = newWidth;
}

void Game::SetScreenHeight(unsigned int newHeight) 
{
    gameHeight = newHeight;
}

void Game::SetScreenWidthAndHeight(unsigned int newWidth, unsigned int newHeight)
{
    gameWidth = newWidth;
    gameHeight = newHeight;
}

void Game::ProcessInput(float dt) 
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_SPEED * dt;

        if (this->Keys[GLFW_KEY_A]) 
        {
            glm::vec2 playerPos = Player->GetPosition();

            if (playerPos.x >= 0.0f) 
            {
                playerPos.x -= velocity;
                Player->SetPosition(playerPos);
                
                if (GameBall->isStuck)
                {
                    glm::vec2 ballPos = GameBall->GetPosition();
                    ballPos.x -= velocity;
                    GameBall->SetPosition(ballPos);
                }
            }
        }
        else if (this->Keys[GLFW_KEY_D])
        {
            glm::vec2 playerPos = Player->GetPosition();

            if (playerPos.x <= gameWidth - PLAYER_SIZE.x)
            {
                playerPos.x += velocity;
                Player->SetPosition(playerPos);

                if (GameBall->isStuck)
                {
                    glm::vec2 ballPos = GameBall->GetPosition();
                    ballPos.x += velocity;
                    GameBall->SetPosition(ballPos);
                }
            }
        }

        if (this->Keys[GLFW_KEY_SPACE])
        {
            GameBall->isStuck = false;
        }
    }
}

void Game::Update(float dt) 
{
    GameBall->Move(dt, gameWidth);
}

void Game::Render() 
{
    Texture2D backGroundTex = ResourceLoader::GetTexture("background");
    Texture2D faceTex = ResourceLoader::GetTexture("face");

    if (this->State == GAME_ACTIVE)
    {
        Renderer->DrawSprite(backGroundTex, glm::vec2(0.0f, 0.0f), glm::vec2(this->gameWidth, this->gameHeight));

        if (this->Levels.size() <= 0) {return;}
        
        this->Levels[this->Level].DrawLevel(*Renderer);

        Player->Draw(*Renderer);
        GameBall->Draw(*Renderer);
    }
}
