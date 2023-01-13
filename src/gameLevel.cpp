#include <gameHeaders/gameLevel.h>
#include <stdlib.h>
#include <stdio.h>
#include "sstream"
#include "fstream"
#include "iostream"
#include "cstring"

void GameLevel::LoadLevel(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    this->Bricks.clear();

    unsigned int tileCode;

    std::string line;
    std::ifstream fileStream(file);
    std::vector<std::vector<unsigned int>> brickData;

    if (!fileStream) 
    {
        throw invalid_input("Could not open level file");
    }

    while (std::getline(fileStream, line))
    {
        std::istringstream sstream(line);
        std::vector<unsigned int> row;

        while (sstream >> tileCode)
        {
            row.push_back(tileCode);
        }
        
        brickData.push_back(row);
    }

    fileStream.close();
    
    if (brickData.size() > 0)
    {
        this->initLevel(brickData, levelWidth, levelHeight);
    }
}

void GameLevel::initLevel(std::vector<std::vector<unsigned int>> brickData, unsigned int levelWidth, unsigned int levelHeight)
{
    unsigned int height = brickData.size();
    unsigned int width = brickData[0].size();
    float unit_height = levelHeight / static_cast<float>(height);
    float unit_width = levelWidth / static_cast<float>(width);

    Texture2D solidBlockTex = ResourceLoader::GetTexture("block_solid");
    Texture2D blockTex = ResourceLoader::GetTexture("block");

    for (unsigned int y = 0; y < height; y++)
    {
        for (unsigned int x = 0; x < width; x++)
        {
            if (brickData[y][x] == 1)
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                glm::vec3 color(0.8f, 0.8f, 0.7f);
                GameObject obj(pos, size, true, solidBlockTex, color);
                this->Bricks.push_back(obj);
            }
            else if (brickData[y][x] > 1)
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                glm::vec3 color(0.8f, 0.8f, 0.7f);

                if (brickData[y][x] == 2)
                {
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                }
                else if (brickData[y][x] == 3)
                {
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                }
                else if (brickData[y][x] == 4)
                {
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                }
                else if (brickData[y][x] == 5)
                {
                    color = glm::vec3(1.0f, 0.5f, 0.0f);
                }

                GameObject obj(pos, size, false, blockTex, color);
                this->Bricks.push_back(obj);
            }
        }
    }
    
}

void GameLevel::DrawLevel(SpriteRenderer &renderer)
{
    for (size_t i = 0; i < Bricks.size(); i++)
    {
        if (this->Bricks[i].isDestroyed) {continue;}

        this->Bricks[i].Draw(renderer);
    }
}

bool GameLevel::IsComplete() 
{
    unsigned int bricksLeft = 0;

    for (size_t i = 0; i < Bricks.size(); i++)
    {
        if (this->Bricks[i].isSolid) {continue;}

        if (!this->Bricks[i].isDestroyed) {bricksLeft++;}
    }

    if (bricksLeft <= 0) {return true;}
    
    return false;
}

void GameLevel::ResetLevel()
{
    for (size_t i = 0; i < Bricks.size(); i++)
    {
        if (this->Bricks[i].isSolid) {continue;}

        if (this->Bricks[i].isDestroyed) 
        {
            this->Bricks[i].isDestroyed = false;
        }
    }
}

std::vector<GameObject> *GameLevel::GetBricks()
{
    return &this->Bricks;
}


