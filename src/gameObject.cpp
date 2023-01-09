#include <gameHeaders/gameObject.h>

GameObject::GameObject(): position(glm::vec3(0.0f)), 
    velocity(glm::vec2(0.0f, 0.0f)), 
    rotation(0.0f), 
    size(1.0f), 
    color(glm::vec3(1.0f)), 
    isSolid(true), 
    isDestroyed(false)
{
}

GameObject::GameObject(
    glm::vec2 iPos, 
    glm::vec2 s, 
    bool solid, 
    Texture2D tex, 
    float r = 0.0f,
    glm::vec2 iVel = glm::vec2(0.0f, 0.0f), 
    glm::vec3 c = glm::vec3(1.0f)): position(iPos), 
        velocity(iVel), 
        rotation(r), 
        size(s), 
        color(c), 
        isSolid(solid), 
        isDestroyed(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->objectTexture, this->position, this->size, this->rotation, this->color);
}
