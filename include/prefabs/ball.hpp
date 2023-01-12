#ifndef __BALL_HPP__
#define __BALL_HPP__

#include <gameHeaders/gameObject.h>
#include <glm/glm.hpp>

class Ball : public GameObject
{
private:
    float radius;
public:
    bool isStuck;

    Ball();
    Ball(glm::vec2 pos, float rad, glm::vec2 initVel, Texture2D tex);
    float GetRadius() { return radius; }
    glm::vec2 Move(float dt, unsigned int screenWidth);
    void Reset(glm::vec2 pos, glm::vec2 vel);
};

#endif
