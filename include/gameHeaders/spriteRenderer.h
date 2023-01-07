#ifndef __SPRITE_RENDERER_H__
#define __SPRITE_RENDERER_H__

#include <shader/shader.h>
#include <gameHeaders/resourceLoader.h>

class SpriteRenderer
{
private:
    Shader shader;
    unsigned int quadVAO;

    void initRenderData();
public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();
    void DrawSprite(Texture2D &texture, 
        glm::vec2 position, 
        glm::vec2 size = glm::vec2(10.0f, 10.0f), 
        float rotate = 0.0f, 
        glm::vec3 color = glm::vec3(1.0f));
};

#endif
