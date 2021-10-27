#include "Tilegrid.h"
#include "RenderDebug.h"

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
    float posY = -(numOfY - 1) * tileSize;
    for(int y = 0; y < numOfY; y++)
    {
        // create new empty row for storing tiles
        std::vector<Tile> tileRow;
        tiles.push_back(tileRow);
        float posX = -(numOfX - 1) * tileSize;
        for(int x = 0; x < numOfX; x++)
        {
            // create new tile to add to this row of tiles
            Tile tile;
            tile.size = tileSize;
            tile.pos.x = x;
            tile.pos.y = y;
            tile.worldPos = VectorMath2(posX, posY);

            // make the tile ground or wall
            srand(time(0) + increment++);
            random = rand()%10;
            // lower number means less chance of becoming ground
            if(random < 8)
            {
                tile.type = Type::GROUND;
            }
            else
            {
                tile.type = Type::WALL;
            }

            // -------- testing --------
            // if(x == 0 && y == 37)
            // {
            //     tile.type = Type::WALL;
            // }
            // --------

            tiles[y].push_back(tile);
            tileInPos.insert(std::make_pair(tile.pos, tile));

            posX += 2 * tileSize;
        }
        posY += 2 * tileSize;
    }
    // -------- Add walls around grid --------
    posY = -(numOfY + 1) * tileSize;
    for(int y = -1; y < numOfY + 1; y++)
    {
        // create new empty row for storing tiles
        std::vector<Tile> tileRow;
        tiles.push_back(tileRow);
        float posX = -(numOfX + 1) * tileSize;
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
                // add on tilePos
                if(y == numOfY)
                {
                    posY = (numOfY + 1) * tileSize;
                }
                tile.worldPos = VectorMath2(posX, posY);
                tile.type = Type::WALL;
                tiles[tiles.size() - 1].push_back(tile);
                tileInPos.insert(std::make_pair(tile.pos, tile));
                posX += 2 * tileSize;
            }
            posY += 2 * tileSize;
        }
        // side borders
        else
        {
            // left
            Tile tile;
            tile.size = tileSize;
            tile.pos.x = -1;
            tile.pos.y = y;
            posX = -(numOfX + 1) * tileSize;
            tile.worldPos = VectorMath2(posX, posY);
            tile.type = Type::WALL;
            tiles[tiles.size() - 1].push_back(tile);
            tileInPos.insert(std::make_pair(tile.pos, tile));

            // right
            tile.size = tileSize;
            tile.pos.x = numOfX;
            posX = -(numOfX - 1) * tileSize;
            posX += tile.pos.x * 2 * tileSize;
            tile.worldPos.x = posX;
            tiles[tiles.size() - 1].push_back(tile);
            tileInPos.insert(std::make_pair(tile.pos, tile));

            posY += 2 * tileSize;
        }
    }
    // -------- Grid size --------
    VectorMath2 pos(0, 0);
    sizeX = numOfX * tileInPos.at(pos).size;
    sizeY = numOfY * tileInPos.at(pos).size;
    // -------- Add neighbors to the tiles --------
    for(int y = 0; y < tiles.size(); y++)
    {
        for(int x = 0; x < tiles[y].size(); x++)
        {
            if(tiles[y][x].type == Type::WALL)
            {
                if(x == 0 && y == 37)
                    addWallToNeighbors(tiles[y][x]);
                else
                    addWallToNeighbors(tiles[y][x]);
            }
            else
            {
                addGroundToNeighbors(tiles[y][x]);
            }
        }
    }
}

void Tilegrid::addWallToNeighbors(Tile wall)
{
    VectorMath2 upLeftPos, upPos, upRightPos, leftPos, rightPos, downLeftPos, downPos, downRightPos;
    upLeftPos.x = wall.pos.x - 1;
    upLeftPos.y = wall.pos.y + 1;
    upPos.x = wall.pos.x;
    upPos.y = wall.pos.y + 1;
    upRightPos.x = wall.pos.x + 1;
    upRightPos.y = wall.pos.y + 1;
    leftPos.x = wall.pos.x - 1;
    leftPos.y = wall.pos.y;
    rightPos.x = wall.pos.x + 1;
    rightPos.y = wall.pos.y;
    downLeftPos.x = wall.pos.x - 1;
    downLeftPos.y = wall.pos.y - 1;
    downPos.x = wall.pos.x;
    downPos.y = wall.pos.y - 1;
    downRightPos.x = wall.pos.x + 1;
    downRightPos.y = wall.pos.y - 1;

    // check if pos is on a tile before adding
    if(upLeftPos.x != -2 && upLeftPos.y != numOfY + 1)
        tileInPos.at(upLeftPos).neighborWalls.push_back(wall);
    if(upPos.y != numOfY + 1)
        tileInPos.at(upPos).neighborWalls.push_back(wall);
    if(upRightPos.x != numOfX + 1 && upRightPos.y != numOfY + 1)
        tileInPos.at(upRightPos).neighborWalls.push_back(wall);
    if(leftPos.x != -2)
        tileInPos.at(leftPos).neighborWalls.push_back(wall);
    if(rightPos.x != numOfX + 1)
        tileInPos.at(rightPos).neighborWalls.push_back(wall);
    if(downLeftPos.x != -2 && downLeftPos.y != -2)
        tileInPos.at(downLeftPos).neighborWalls.push_back(wall);
    if(downPos.y != -2)
        tileInPos.at(downPos).neighborWalls.push_back(wall);
    if(downRightPos.x != numOfX + 1 && downRightPos.y != -2)
        tileInPos.at(downRightPos).neighborWalls.push_back(wall);

}
void Tilegrid::addGroundToNeighbors(Tile ground)
{
    VectorMath2 upLeftPos, upPos, upRightPos, leftPos, rightPos, downLeftPos, downPos, downRightPos;
    upLeftPos.x = ground.pos.x - 1;
    upLeftPos.y = ground.pos.y + 1;
    upPos.x = ground.pos.x;
    upPos.y = ground.pos.y + 1;
    upRightPos.x = ground.pos.x + 1;
    upRightPos.y = ground.pos.y + 1;
    leftPos.x = ground.pos.x - 1;
    leftPos.y = ground.pos.y;
    rightPos.x = ground.pos.x + 1;
    rightPos.y = ground.pos.y;
    downLeftPos.x = ground.pos.x - 1;
    downLeftPos.y = ground.pos.y - 1;
    downPos.x = ground.pos.x;
    downPos.y = ground.pos.y - 1;
    downRightPos.x = ground.pos.x + 1;
    downRightPos.y = ground.pos.y - 1;

    // check if pos is on a tile before adding
    if(upLeftPos.x != -2 && upLeftPos.y != numOfY + 1)
        tileInPos.at(upLeftPos).neighborGround.push_back(ground);
    if(upPos.y != numOfY + 1)
        tileInPos.at(upPos).neighborGround.push_back(ground);
    if(upRightPos.x != numOfX + 1 && upRightPos.y != numOfY + 1)
        tileInPos.at(upRightPos).neighborGround.push_back(ground);
    if(leftPos.x != -2)
        tileInPos.at(leftPos).neighborGround.push_back(ground);
    if(rightPos.x != numOfX + 1)
        tileInPos.at(rightPos).neighborGround.push_back(ground);
    if(downLeftPos.x != -2 && downLeftPos.y != -2)
        tileInPos.at(downLeftPos).neighborGround.push_back(ground);
    if(downPos.y != -2)
        tileInPos.at(downPos).neighborGround.push_back(ground);
    if(downRightPos.x != numOfX + 1 && downRightPos.y != -2)
        tileInPos.at(downRightPos).neighborGround.push_back(ground);

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
            VectorMath2 pos;
            pos.y = y;
            pos.x = x;
            if(tileInPos.at(pos).type == Type::WALL)
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

    VectorMath2 pos;
    pos.x = 0;
    pos.y = 0;
    float wallPosX = -(numOfX + 1) * tileInPos.at(pos).size;
    float wallPosY = -(numOfY + 1) * tileInPos.at(pos).size;

    float zOffset = 0.8;

    for(int y = -1; y < numOfY + 1; y++)
    {
        wallPosX = -(numOfX + 1) * tileInPos.at(pos).size;
        // bottom and top border
        if(y == -1 || y == numOfY)
        {
            for(int x = -1; x < numOfX + 1; x++)
            {
                MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tileInPos.at(pos).size, tileInPos.at(pos).size, 1));
                wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));
                wallPosX += 2 * tileInPos.at(pos).size;
            }
            wallPosY += 2 * tileInPos.at(pos).size;
        }
        // side borders
        else
        {
            // left
            MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tileInPos.at(pos).size, tileInPos.at(pos).size, 1));
            wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));

            // right
            wallPosX += 2 * tileInPos.at(pos).size * (numOfX + 1);
            transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tileInPos.at(pos).size, tileInPos.at(pos).size, 1));
            wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));
            wallPosY += 2 * tileInPos.at(pos).size;
        }
    }
}

void Tilegrid::placeWalls()
{
    VectorMath2 pos;
    pos.x = 0;
    pos.y = 0;
    float wallPosX = -(numOfX - 1) * tileInPos.at(pos).size;
    float wallPosY = -(numOfY - 1) * tileInPos.at(pos).size;
    int wallInt = 0;
    for(int y = 0; y < numOfY; y++)
    {
        wallPosX = -(numOfX - 1) * tileInPos.at(pos).size;
        for(int x = 0; x < numOfX; x++)
        {
            pos.y = y;
            pos.x = x;
            if(tileInPos.at(pos).type == Type::WALL)
            {
                MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + 0.3)) * 
                    ScalarMatrix(VectorMath3(tileInPos.at(pos).size, tileInPos.at(pos).size, 1));
                wallTiles[wallInt++].setTransform(transform);
            }
            wallPosX += 2 * tileInPos.at(pos).size;
        }
        wallPosY += 2 * tileInPos.at(pos).size;
    }
}

void Tilegrid::Draw(MatrixMath viewMat)
{
    groundTile.Draw();
    for(GraphicsNode tile : wallTiles)
    {
        VectorMath4 cullingPos = VectorMath4(tile.getTransform()[3][0], tile.getTransform()[3][1],tile.getTransform()[3][2],tile.getTransform()[3][3]);
        cullingPos = viewMat.VectorMultiplication(cullingPos);
        cullingPos.x /= cullingPos.w;
        cullingPos.y /= cullingPos.w;
        if(cullingPos.x < 1 && cullingPos.x > -1 && cullingPos.y < 1 && cullingPos.y > -1){
            tile.Draw();
        }
    }
    for (int y = 0; y < 40; y++)
    {
        for (int x = 0; x < 40; x++)
        {
            float px = (float)x - 40/2 + 0.4;
            float py = (float)y - 40/2 + 0.4;
            VectorMath4 cullingPos = VectorMath4(px,py,0,1);
            cullingPos = viewMat.VectorMultiplication(cullingPos);

            cullingPos.x /= cullingPos.w;
            cullingPos.y /= cullingPos.w;
            if(cullingPos.x < 1 && cullingPos.x > -1 && cullingPos.y < 1 && cullingPos.y > -1){
                Debug::DrawSquare(0.8, VectorMath3(px, py, -6.9), VectorMath4(0,1,0,1));
            }
            else
                Debug::DrawSquare(0.8, VectorMath3(px, py, -6.9), VectorMath4(1,0,0,1));
        } 
    }
}


Tilegrid::~Tilegrid()
{
}