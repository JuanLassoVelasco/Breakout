#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include <gameHeaders/gameObject.h>
#include <stdlib.h>
#include <stdio.h>
#include <errorHeaders/invalidInput.hpp>
#include "vector"

class GameLevel
{
private:
    std::vector<GameObject> Bricks;

    void initLevel(std::vector<std::vector<unsigned int>> brickData, unsigned int levelWidth, unsigned int levelHeight);
public:
    GameLevel() {}
    ~GameLevel() {}
    void LoadLevel(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    void DrawLevel(SpriteRenderer &renderer);
    bool IsComplete();
};

#endif
