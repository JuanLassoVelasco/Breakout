#include <prefabs/ball.hpp>

Ball::Ball(): GameObject(), radius(0.5f), isStuck(true)
{
}

Ball::Ball(glm::vec2 pos, float rad, glm::vec2 initVel, Texture2D tex): 
    GameObject(pos, glm::vec2(2*rad,2*rad), true, tex, glm::vec3(1.0f), 0.0f, initVel),
    radius(rad), isStuck(true)
{
}

glm::vec2 Ball::Move(float dt, unsigned int screenWidth)
{
    glm::vec2 ballPos = GetPosition();
    glm::vec2 ballVel = GetVelocity();

    if (isStuck) { return ballPos; }

    ballPos += ballVel * dt;

    SetPosition(ballPos);

    if (ballPos.x <= 0.0f)
    {
        ballVel.x = -ballVel.x;
        ballPos.x = 0.0f;
        SetVelocity(ballVel);
        SetPosition(ballPos);
    }
    else if (ballPos.x >= screenWidth + 2 * radius)
    {
        ballVel.x = -ballVel.x;
        ballPos.x = screenWidth + 2 * radius;
        SetVelocity(ballVel);
        SetPosition(ballPos);
    }

    if (ballPos.y <= 0.0f)
    {
        ballVel.y = -ballVel.y;
        ballPos.y = 0.0f;
        SetVelocity(ballVel);
        SetPosition(ballPos);
    }

    return ballPos;
}

void Ball::Reset(glm::vec2 pos, glm::vec2 vel)
{
}
