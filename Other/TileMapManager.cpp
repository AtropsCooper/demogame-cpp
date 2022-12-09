#include "TileMapManager.h"
#include "Game.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "CollisionBoxComponent.h"
#include <cstdlib>

const int MIN_ROOM_SIZE = 8;
const int MAX_ROOM_SIZE = 24;
const int HALLWAY_WIDTH = 2;
const int GENERATE_TRYS = 20;

const char FLOOR_NORMAL = 1;
const char WALL_MID = 11;
const char WALL_TOP = 12;
const char WALL_LEFT = 13;
const char WALL_LEFT_TOP = 14;
const char WALL_RIGHT = 15;
const char WALL_RIGHT_TOP = 16;
const char CORNER_TL = 21;
const char CORNER_BL = 22;
const char CORNER_TR = 23;
const char CORNER_BR = 24;

const SDL_Rect R_FLOOR_NORMAL = {16, 64, 16, 16};
const SDL_Rect R_WALL_MID = {32, 16, 16, 16};
const SDL_Rect R_WALL_LEFT = {0, 128, 16, 16};
const SDL_Rect R_WALL_RIGHT = {16, 128, 16, 16};
const SDL_Rect R_CORNER_TOP_LEFT = {32, 112, 16, 16};
const SDL_Rect R_CORNER_LEFT = {32, 128, 16, 16};
const SDL_Rect R_CORNER_BOTTOM_LEFT = {32, 144, 16, 16};

TileMapManager::TileMapManager(Game *game) : mGame(game)
{
}

TileMapManager::~TileMapManager()
{
    ClearTileEntities();
}

void TileMapManager::Initialize()
{
    mTileTexture = mGame->GetTexture("dungeon");
    memset(mTiles, 0, sizeof(mTiles));
}

void TileMapManager::GenerateMap()
{
    std::vector<SDL_Rect> connectedRoomVec;
    std::vector<SDL_Rect> unconnectedRoomVec;
    auto Connect = [&](std::vector<SDL_Rect>::iterator itroom)
    {
        connectedRoomVec.emplace_back(*itroom);
        unconnectedRoomVec.erase(itroom);
    };

    for (int i = 0; i < GENERATE_TRYS; i++)
    {
        int roomW = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
        int roomH = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
        int roomX = rand() % (MAPSIZE - roomW - 1);
        int roomY = rand() % (MAPSIZE - roomH - 1);
        unconnectedRoomVec.emplace_back(SDL_Rect{roomX, roomY, roomW, roomH});
    }

    Connect(unconnectedRoomVec.begin());
    // Helper func for generating hallways
    auto Hallway = [&map=mTiles](int fromX, int fromY, int toX, int toY) -> void
    {
        if (fromX != toX || fromY != toY)
        {
            if (fromY == toY)
            {
                for (int i = MyMath::Min(fromX, toX); i < MyMath::Max(fromX, toX) + HALLWAY_WIDTH; i++)
                {
                    for (int j = fromY; j < fromY + HALLWAY_WIDTH; j++)
                    {
                        map[i][j] = FLOOR_NORMAL;
                    }
                }
            }
            else if (fromX == toX)
            {
                for (int i = MyMath::Min(fromY, toY); i < MyMath::Max(fromY, toY) + HALLWAY_WIDTH; i++)
                {
                    for (int j = fromX; j < fromX + HALLWAY_WIDTH; j++)
                    {
                        map[j][i] = FLOOR_NORMAL;
                    }
                }
            }
            // else: Not in line
        }
        // else: only a point
    };

    while (unconnectedRoomVec.size() != 0) // until there is no unconnected room
    {
        // Pick one room as connected
        int connectedRoomIndex = rand() % connectedRoomVec.size();
        SDL_Rect connectedRoom = connectedRoomVec[connectedRoomIndex];
        // Pick A random unconnected room
        int unconnectedRoomIndex = rand() % unconnectedRoomVec.size();
        auto itUnconnectedRoom = unconnectedRoomVec.begin() + unconnectedRoomIndex;
        SDL_Rect unconnectedRoom = *itUnconnectedRoom;

        bool isHorizontalL = connectedRoom.x + connectedRoom.w < unconnectedRoom.x;
        bool isHorizontalR = unconnectedRoom.x + unconnectedRoom.w < connectedRoom.x;
        bool isVerticalB = connectedRoom.y + connectedRoom.h < unconnectedRoom.y;
        bool isVerticalT = unconnectedRoom.y + unconnectedRoom.h < connectedRoom.y;

        // Horizontally connect
        auto ConnectHorizontal = [&]()
        {
            SDL_Rect left;
            SDL_Rect right;
            if (isHorizontalL)
            {
                left = connectedRoom;
                right = unconnectedRoom;
            }
            else
            {
                left = unconnectedRoom;
                right = connectedRoom;
            }
            int leftX = left.x + left.w;
            int leftY = rand() % (left.h - HALLWAY_WIDTH) + left.y;
            int rightX = right.x;
            int rightY = rand() % (right.h - HALLWAY_WIDTH) + right.y;
            int midX = rand() % (rightX - leftX) + leftX;
            Hallway(leftX, leftY, midX, leftY);
            Hallway(midX, leftY, midX, rightY);
            Hallway(midX, rightY, rightX, rightY);
        };
        // Vertically connect
        auto ConnectVertical = [&]()
        {
            SDL_Rect top;
            SDL_Rect bottom;
            if (isVerticalT)
            {
                top = connectedRoom;
                bottom = unconnectedRoom;
            }
            else
            {
                top = unconnectedRoom;
                bottom = connectedRoom;
            }
            int topX = rand() % (top.w - HALLWAY_WIDTH) + top.x;
            int topY = top.y;
            int bottomX = rand() % (bottom.w - HALLWAY_WIDTH) + bottom.x;
            int bottomY = bottom.y + bottom.h;
            int midY = rand() % (topY - bottomY) + bottomY;
            Hallway(topX, topY, topX, midY);
            Hallway(bottomX, midY, topX, midY);
            Hallway(bottomX, midY, bottomX, bottomY);
        };

        if ((isHorizontalL || isHorizontalR) && (isVerticalT || isVerticalB))
        {
            if (rand() % 2 == 1)
            {
                ConnectHorizontal();
            }
            else
            {
                ConnectVertical();
            }
        }
        else if (isHorizontalL || isHorizontalR)
        {
            ConnectHorizontal();
        }
        else if (isVerticalT || isVerticalB)
        {
            ConnectVertical();
        }
        // else: two rooms collapsed
        Connect(itUnconnectedRoom);
    }

    for (auto room : connectedRoomVec)
    {
        for (int i = room.x; i < MyMath::Min((room.x + room.w), MAPSIZE); i++)
        {
            for (int j = room.y; j < MyMath::Min((room.y + room.h), MAPSIZE); j++)
            {
                mTiles[i][j] = FLOOR_NORMAL;
            }
        }
    }

    // Iterate over the elements of the mTiles for Adding WALL.
    for (int row = 0; row < MAPSIZE; row++) {
        for (int col = 0; col < MAPSIZE; col++) {

            // If the current element has a value of FLOOR, check its adjacent elements.
            if (mTiles[row][col] == FLOOR_NORMAL) {

            // Check the element above.
            if (row > 0 && mTiles[row-1][col] == 0) {
                mTiles[row-1][col] = WALL_MID;
            }

            // Check the element below.
            if (row < MAPSIZE - 1 && mTiles[row+1][col] == 0) {
                mTiles[row+1][col] = WALL_MID;
            }

            // Check the element to the left.
            if (col > 0 && mTiles[row][col-1] == 0) {
                mTiles[row][col-1] = WALL_MID;
            }

            // Check the element to the right.
            if (col < MAPSIZE - 1 && mTiles[row][col+1] == 0) {
                mTiles[row][col+1] = WALL_MID;
            }

            // Check the top-left diagonal element.
            if (row > 0 && col > 0 && mTiles[row-1][col-1] == 0) {
                mTiles[row-1][col-1] = WALL_MID;
            }

            // Check the top-right diagonal element.
            if (row > 0 && col < MAPSIZE - 1 && mTiles[row-1][col+1] == 0) {
                mTiles[row-1][col+1] = WALL_MID;
            }

            // Check the bottom-left diagonal element.
            if (row < MAPSIZE - 1 && col > 0 && mTiles[row+1][col-1] == 0) {
                mTiles[row+1][col-1] = WALL_MID;
            }

            // Check the bottom-right diagonal element.
            if (row < MAPSIZE - 1 && col < MAPSIZE - 1 && mTiles[row+1][col+1] == 0) {
                mTiles[row+1][col+1] = WALL_MID;
            }
            }
        }
    }
}

void TileMapManager::Instanciate()
{
    
    for (int i = 0; i < MAPSIZE; i++)
    {
        for (int j = 0; j < MAPSIZE; j++)
        {
            if (mTiles[i][j] != 0)
            {
                Entity* tile = new Entity(mGame);
                tile->mPosition.x = static_cast<float>(i);
                tile->mPosition.y = static_cast<float>(j);
                mTileEntities.emplace_back(tile);
                SpriteComponent* sprite = new SpriteComponent(tile, 0);
                switch (mTiles[i][j])
                {
                case FLOOR_NORMAL:
                    sprite->SetTexture(mTileTexture, &R_FLOOR_NORMAL);
                    break;
                case WALL_MID:
                    sprite->SetTexture(mTileTexture, &R_WALL_MID);
                    //new CollisionBoxComponent(tile, 4);
                    break;

                default:
                    break;
                }
            }
        }
    }
}

void TileMapManager::ClearTileEntities()
{
    for (auto t : mTileEntities)
    {
        t->SetState(Entity::EDead);
    }
    mTileEntities.clear();
}