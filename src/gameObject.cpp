#include <gameHeaders/gameObject.h>

GameObject::GameObject(): position(glm::vec3(0.0f)), 
    size(1.0f, 1.0f), 
    isSolid(true),
    objectTexture(),
    color(glm::vec3(1.0f)), 
    rotation(0.0f), 
    velocity(glm::vec2(0.0f, 0.0f)),  
    isDestroyed(false)
{
}

GameObject::GameObject(
    glm::vec2 iPos, 
    glm::vec2 s, 
    bool solid, 
    Texture2D tex, 
    glm::vec3 c,
    float r,
    glm::vec2 iVel): position(iPos),   
        size(s), 
        isSolid(solid),
        objectTexture(tex),
        color(c), 
        rotation(r),
        velocity(iVel), 
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
