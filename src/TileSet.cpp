#include "TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : 
    tileWidth(tileWidth),
    tileHeight(tileHeight) {
    
    // Carrega o sprite do tileset
    tileSet.Open(file);
    
    if(tileSet.IsOpen()) {
        // Calcula quantos tiles cabem horizontalmente e verticalmente
        int columns = tileSet.GetWidth() / tileWidth;
        int rows = tileSet.GetHeight() / tileHeight;
        tileCount = columns * rows;
        
        std::cout << "TileSet loaded: " << columns << "x" << rows << " tiles" << std::endl;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index >= (unsigned)tileCount) {
        return; // Índice inválido
    }

    // Calcula a posição do tile no tileset
    int tilesPerRow = tileSet.GetWidth() / tileWidth;
    int row = index / tilesPerRow;
    int column = index % tilesPerRow;
    
    // Define a área do tile atual
    tileSet.SetClip(column * tileWidth, 
                    row * tileHeight, 
                    tileWidth, 
                    tileHeight);
    
    // Renderiza na posição especificada
    tileSet.Render(x, y);
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}