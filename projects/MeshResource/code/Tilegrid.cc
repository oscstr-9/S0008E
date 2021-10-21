#include "Tilegrid.h"

Tilegrid::Tilegrid(int numOfX, int numOfY, float zPlacement, float tileSize)
{
    this->numOfX = numOfX;
    this->numOfY = numOfY;
    this->zPlacement = zPlacement;
    createGrid(tileSize);
}

void Tilegrid::createGrid(float tileSize)
{
    // -------- Tiles --------
    int random;
    int increment = 0;
    for(int y = 0; y < numOfY; y++)
    {
        // create new empty row for storing tiles
        std::vector<Tile> tileRow;
        tiles.push_back(tileRow);
        for(int x = 0; x < numOfX; x++)
        {
            // create new tile to add to this row of tiles
            Tile tile;
            tile.size = tileSize;
            tile.pos.x = x;
            tile.pos.y = y;

            // make the tile ground or wall
            srand(time(0) + increment++);
            random = rand()%10;
            // lower number means less chance of becoming ground
            if(random < 7)
            {
                tile.type = Type::GROUND;
            }
            else
            {
                tile.type = Type::WALL;
            }

            tiles[y].push_back(tile);
        }
    }
    // -------- Add walls around grid --------
    for(int y = -1; y < numOfY + 1; y++)
    {
        // create new empty row for storing tiles
        std::vector<Tile> tileRow;
        tiles.push_back(tileRow);
        // bottom and top border
        if(y == -1 || y == numOfY)
        {
            for(int x = -1; x < numOfX + 1; x++)
            {
                // create new tile to add to this row of tiles
                Tile tile;
                tile.size = tileSize;
                tile.pos.x = x;
                tile.pos.y = y;
                tile.type = Type::WALL;
                tiles[tiles.size() - 1].push_back(tile);
            }
        }
        // side borders
        else
        {
            Tile tile;
            tile.size = tileSize;
            tile.pos.x = -1;
            tile.pos.y = y;
            tile.type = Type::WALL;
            tiles[tiles.size() - 1].push_back(tile);

            tile.size = tileSize;
            tile.pos.x = numOfX;
            tiles[tiles.size() - 1].push_back(tile);
        }
    }
    // -------- Grid size --------
    sizeX = numOfX * tiles[0][0].size;
    sizeY = numOfY * tiles[0][0].size;
}


// setup everything so only draw needs to be called during runtime
// assumes the square and wall are the same size; from -1 to 1 in the obj file
void Tilegrid::createGraphics(std::shared_ptr<ShaderResource> shaders, bool showBorders)
{
    // ground, just one square at the size of the width * height of this tilegrid
    std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("wall.png");
    texture->LoadFromFile();
    std::shared_ptr<MeshResource> mesh = MeshResource::LoadObj("square");
    MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(0, 0, zPlacement)) * ScalarMatrix(VectorMath3(sizeX, sizeY, 1));
    groundTile = GraphicsNode(mesh, texture, shaders, transform);

    // walls, one graphicsnode per wall
    std::shared_ptr<TextureResource> wallTexture = std::make_shared<TextureResource>("cubepic.png");
    wallTexture->LoadFromFile();
    std::shared_ptr<MeshResource> wallMesh = MeshResource::LoadObj("cube");
    for(int y = 0; y < numOfY; y++)
    {
        for(int x = 0; x < numOfX; x++)
        {
            if(tiles[y][x].type == Type::WALL)
            {
                MatrixMath transform = Identity(); // wall transform is set in placeWalls()
                wallTiles.push_back(GraphicsNode(wallMesh, wallTexture, shaders, transform));
            }
        }
    }

    // set the rendering of each wall to be in their respective spot on the grid
    placeWalls();
    if(showBorders)
        createBorderGraphics(shaders);
}

void Tilegrid::createBorderGraphics(std::shared_ptr<ShaderResource> shaders)
{
    std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("cubepic.png");
    texture->LoadFromFile();
    std::shared_ptr<MeshResource> mesh = MeshResource::LoadObj("cube");

    float wallPosX = -(numOfX + 1) * tiles[0][0].size;
    float wallPosY = -(numOfY + 1) * tiles[0][0].size;

    float zOffset = 0.8;

    for(int y = -1; y < numOfY + 1; y++)
    {
        wallPosX = -(numOfX + 1) * tiles[0][0].size;
        // bottom and top border
        if(y == -1 || y == numOfY)
        {
            for(int x = -1; x < numOfX + 1; x++)
            {
                MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tiles[0][0].size, tiles[0][0].size, 1));
                wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));
                wallPosX += 2 * tiles[0][0].size;
            }
            wallPosY += 2 * tiles[0][0].size;
        }
        // side borders
        else
        {
            // left
            MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tiles[0][0].size, tiles[0][0].size, 1));
            wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));
            wallPosX += 2 * tiles[0][0].size * (numOfX + 1);

            // right
            transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tiles[0][0].size, tiles[0][0].size, 1));
            wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));
            wallPosY += 2 * tiles[0][0].size;
        }
    }
}

void Tilegrid::placeWalls()
{
    float wallPosX = -(numOfX - 1) * tiles[0][0].size;
    float wallPosY = -(numOfY - 1) * tiles[0][0].size;
    int wallInt = 0;
    for(int y = 0; y < numOfY; y++)
    {
        wallPosX = -(numOfX - 1) * tiles[0][0].size;
        for(int x = 0; x < numOfX; x++)
        {
            if(tiles[y][x].type == Type::WALL)
            {
                MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + 0.3)) * 
                    ScalarMatrix(VectorMath3(tiles[0][0].size, tiles[0][0].size, 1));
                wallTiles[wallInt++].setTransform(transform);
            }
            wallPosX += 2 * tiles[0][0].size;
        }
        wallPosY += 2 * tiles[0][0].size;
    }
}

void Tilegrid::Draw()
{
    groundTile.Draw();
    for(GraphicsNode tile : wallTiles)
    {
        tile.Draw();
    }
}


Tilegrid::~Tilegrid()
{
}