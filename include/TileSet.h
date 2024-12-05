#ifndef TILESET_H
#define TILESET_H

#include "Sprite.h"
#include <string>

class TileSet {
private:
    Sprite tileSet;
    int tileWidth;
    int tileHeight;
    int tileCount;

public:
    TileSet(int tileWidth, int tileHeight, std::string file);
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
};

#endif