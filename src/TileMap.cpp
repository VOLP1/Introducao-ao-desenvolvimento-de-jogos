#include "TileMap.h"
#include <fstream>
#include <sstream>
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated) {
    this->tileSet = std::unique_ptr<TileSet>(tileSet);
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream map(file);
    if (!map.is_open()) {
        throw std::runtime_error("Unable to open map file: " + file);
    }

    std::string line;
    std::getline(map, line);
    std::stringstream dimensions(line);
    char comma;
    
    // Lê as dimensões do mapa
    dimensions >> mapWidth >> comma >> mapHeight >> comma >> mapDepth;
    std::cout << "Map dimensions: " << mapWidth << "x" << mapHeight << "x" << mapDepth << std::endl;

    // Pula a linha em branco
    std::getline(map, line);
    
    // Lê todos os tiles
    tileMatrix.clear();
    int count = 0;
    int expectedTiles = mapWidth * mapHeight * mapDepth;
    
    while (std::getline(map, line)) {
        std::stringstream lineStream(line);
        int tile;
        while (lineStream >> tile) {
            tileMatrix.push_back(tile - 1); // -1 porque os índices começam em 0
            count++;
            
            // Ignora a vírgula
            if (lineStream.peek() == ',') {
                lineStream.ignore();
            }
        }
    }

    if (count != expectedTiles) {
        std::cout << "Warning: Expected " << expectedTiles << " tiles but got " << count << std::endl;
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = std::unique_ptr<TileSet>(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    int index = z * (mapWidth * mapHeight) + y * mapWidth + x;
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int tileIndex = At(x, y, layer);
            if (tileIndex >= 0) { // -1 representa ausência de tile
                float posX = x * tileSet->GetTileWidth() - cameraX;
                float posY = y * tileSet->GetTileHeight() - cameraY;
                tileSet->RenderTile(tileIndex, posX, posY);
            }
        }
    }
}

void TileMap::Render() {
    for (int layer = 0; layer < mapDepth; layer++) {
        RenderLayer(layer);
    }
}

void TileMap::Update(float) {} // Não faz nada por enquanto

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

int TileMap::GetWidth() { return mapWidth; }
int TileMap::GetHeight() { return mapHeight; }
int TileMap::GetDepth() { return mapDepth; }