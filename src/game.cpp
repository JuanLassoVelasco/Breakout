#include <gameHeaders/game.h>
#include <glm/ext/matrix_clip_space.hpp>

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_SPEED(500.0f);

const glm::vec2 INIT_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

const float BALL_SPEED_CHANGE_STRENGTH = 2.0f;

GameObject* Player;
Ball* GameBall;

SpriteRenderer *Renderer;

Direction VectorDirection(glm::vec2 vec)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, -1.0f),
        glm::vec2(-1.0f, 0.0f)
    };

    float max = 0.0f;
    unsigned int direction;

    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(vec), compass[i]);

        if (dot_product > max)
        {
            max = dot_product;
            direction = i;
        }
    }

    return (Direction)direction;
}

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

    HandleCollisions();

    if (GameBall->GetPosition().y >= gameHeight)
    {
        ResetGame();
    }
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

void Game::ResolveBallCollision(Collision collision)
{
    Direction penDir = std::get<1>(collision);
    glm::vec2 distFromBall = std::get<2>(collision);
    glm::vec2 ballPos = GameBall->GetPosition();
    glm::vec2 ballVel = GameBall->GetVelocity();
    float ballRad = GameBall->GetRadius();
    glm::vec2 penDist = glm::vec2(ballRad, ballRad);

    penDist.x = penDist.x - std::abs(distFromBall.x);
    penDist.y = penDist.y - std::abs(distFromBall.y);

    if (penDir == LEFT || penDir == RIGHT)
    {
        ballVel.x = -ballVel.x;

        if (penDir == LEFT)
        {
            ballPos.x += penDist.x;
        }
        else
        {
            ballPos.x -= penDist.x;
        }

        GameBall->SetPosition(ballPos);
        GameBall->SetVelocity(ballVel);
    }
    else 
    {
        ballVel.y = -ballVel.y;

        if (penDir == DOWN)
        {
            ballPos.y += penDist.y;
        }
        else
        {
            ballPos.y -= penDist.y;
        }

        GameBall->SetPosition(ballPos);
        GameBall->SetVelocity(ballVel);
    }
}

bool Game::CheckCollision(GameObject &objectOne, GameObject &objectTwo)
{
    bool collisionX;
    bool collisionY;
    bool collided;

    glm::vec2 obOnePos = objectOne.GetPosition();
    glm::vec2 obTwoPos = objectTwo.GetPosition();

    glm::vec2 obOneSize = objectOne.GetSize();
    glm::vec2 obTwoSize = objectTwo.GetSize();

    collisionX = (obOnePos.x + obOneSize.x >= obTwoPos.x && obTwoPos.x + obTwoSize.x >= obOnePos.x);
    collisionY = (obOnePos.y + obOneSize.y >= obTwoPos.y && obTwoPos.y + obTwoSize.y >= obOnePos.y); 

    collided = collisionX && collisionY;

    return collided;
}

Collision Game::CheckCtoBCollision(Ball& ballObject, GameObject& boxObject)
{
    glm::vec2 boxPos = boxObject.GetPosition();
    glm::vec2 ballPos = ballObject.GetPosition();

    glm::vec2 boxSize = boxObject.GetSize();
    float ballRadius = ballObject.GetRadius();

    float halfBoxX = boxSize.x / 2.0f;
    float halfBoxY = boxSize.y / 2.0f;

    glm::vec2 boxCenterPos = boxPos;
    glm::vec2 ballCenterPos = ballPos;
    boxCenterPos.x += halfBoxX;
    ballCenterPos.x += ballRadius;
    boxCenterPos.y += halfBoxY;
    ballCenterPos.y += ballRadius;

    glm::vec2 CenterDiff = ballCenterPos - boxCenterPos;
    glm::vec2 boxP = CenterDiff;

    boxP.x = std::clamp<float>(boxP.x, -halfBoxX, halfBoxX);
    boxP.y = std::clamp<float>(boxP.y, -halfBoxY, halfBoxY);

    boxP = boxCenterPos + boxP;

    glm::vec2 distFromBall = boxP - ballCenterPos;

    float distMag = glm::length(distFromBall);

    if (distMag < ballObject.GetRadius())
    {
        return std::make_tuple(true, VectorDirection(distFromBall), distFromBall);
    }
    else
    {
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
    }
}

void Game::HandlePlayerCollisions()
{
    Collision collision = CheckCtoBCollision(*GameBall, *Player);

    if (std::get<0>(collision))
    {
        glm::vec2 playerPos = Player->GetPosition();
        glm::vec2 ballPos = GameBall->GetPosition();
        glm::vec2 ballVel = GameBall->GetVelocity();
        glm::vec2 playerSize = Player->GetSize();
        float ballRad = GameBall->GetRadius();

        float playerCenterPos = playerPos.x + playerSize.x / 2.0f;
        float landDistance = (ballPos.x + ballRad) - playerCenterPos;
        float percentDist = landDistance / (playerSize.x / 2.0f);

        ballVel.x = INIT_BALL_VELOCITY.x * percentDist * BALL_SPEED_CHANGE_STRENGTH;
        ballVel.y = -1.0 * std::abs(ballVel.y);
        GameBall->SetVelocity(ballVel);
    }
}

void Game::HandleCollisions()
{
    GameLevel* currentLevel = &this->Levels[this->Level];

    for (GameObject &brick: *currentLevel->GetBricks())
    {
        if (!brick.isDestroyed)
        {
            Collision collision = CheckCtoBCollision(*GameBall, brick);

            if (std::get<0>(collision))
            {
                if (!brick.isSolid)
                {
                    brick.isDestroyed = true;
                }

                ResolveBallCollision(collision);
            }
        }
    }

    HandlePlayerCollisions();
}

void Game::ResetGame()
{
    delete GameBall;

    Texture2D ballSprite = ResourceLoader::GetTexture("face");
    glm::vec2 playerPos = glm::vec2(this->gameWidth / 2.0f - PLAYER_SIZE.x / 2.0f, this->gameHeight - PLAYER_SIZE.y);
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

    GameBall = new Ball(ballPos, BALL_RADIUS, INIT_BALL_VELOCITY, ballSprite);

    this->Levels[Level].ResetLevel();
    ResetPlayer(playerPos);
}

void Game::ResetPlayer(glm::vec2 playerPos)
{
    delete Player;

    Texture2D playerSprite = ResourceLoader::GetTexture("paddle");

    Player = new GameObject(playerPos, PLAYER_SIZE, false, playerSprite);
}
