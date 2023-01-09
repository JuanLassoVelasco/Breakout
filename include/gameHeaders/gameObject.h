#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <gameHeaders/texture.h>
#include <glm/glm.hpp>
#include <gameHeaders/spriteRenderer.h>

class GameObject
{
private:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 size;
    float rotation;
    glm::vec3 color;
    Texture2D objectTexture;
public:
    bool isSolid;
    bool isDestroyed;

    GameObject();
    GameObject(glm::vec2 iPos, glm::vec2 s, bool solid, Texture2D tex, float r = 0.0f, glm::vec2 iVel = glm::vec2(0.0f, 0.0f), glm::vec3 c = glm::vec3(1.0f));
    ~GameObject();
    glm::vec2 GetPosition() {return position;}
    glm::vec2 GetVelocity() {return velocity;}
    glm::vec2 GetSize() {return size;}
    float GetRotation() {return rotation;}
    glm::vec3 GetColor() {return color;}
    Texture2D GetTexture() {return objectTexture;}
    void SetPosition(glm::vec2 newPos) {position = newPos;}
    void SetVelocity(glm::vec2 newVel) {velocity = newVel;}
    void SetSize(glm::vec2 newSize) {size = newSize;}
    void SetRotation(float newRot) {rotation = newRot;}
    void SetColor(glm::vec3 newColor) {color = newColor;}
    void SetTexture(Texture2D newTex) {objectTexture = newTex;}

    virtual void Draw(SpriteRenderer &renderer);
};

#endif
