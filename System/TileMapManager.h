#pragma once
#include "System.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "Constants.h"


class TileMapManager
{
public:
    TileMapManager(Game *game);
    ~TileMapManager();

    void Initialize();
    void ReadMapFromFile(const std::string &fileName);
    void GenerateMap();
    void Instanciate();
    void ClearTileEntities();

private:
    SDL_Texture* mTileTexture;
    
    class Game* mGame;
    std::vector<class Entity*> mTileEntities;
    unsigned char mTiles[MAPSIZE][MAPSIZE];
}; 


/*

   wall_side_top_left 0 112 16 16
    wall_side_top_right 16 112 16 16
    wall_side_mid_left 0 128 16 16
    wall_side_mid_right 16 128 16 16
    wall_side_front_left 0 144 16 16
    wall_side_front_right 16 144 16 16

    wall_corner_top_left 32 112 16 16
    wall_corner_top_right 48 112 16 16
    wall_corner_left 32 128 16 16
    wall_corner_right 48 128 16 16
    wall_corner_bottom_left 32 144 16 16
    wall_corner_bottom_right 48 144 16 16
    wall_corner_front_left 32 160 16 16
    wall_corner_front_right 48 160 16 16

    wall_inner_corner_l_top_left 80 128 16 16
    wall_inner_corner_l_top_rigth 64 128 16 16
    wall_inner_corner_mid_left 80 144 16 16
    wall_inner_corner_mid_rigth 64 144 16 16
    wall_inner_corner_t_top_left 80 160 16 16
    wall_inner_corner_t_top_rigth 64 160 16 16

*/