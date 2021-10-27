#pragma once
#include "core/MatrixMath.h"
#include "render/GraphicsNode.h"
#include "render/ShaderResource.h"
#include "GameObject.h"
#include "Tilegrid.h"
#include <memory>

class Enemy : public GameObject
{
private:
    MatrixMath positionMatrix = Identity();
    MatrixMath rotationMatrix = Identity();
    MatrixMath rotationCorrectionMatrix = RotateMatrix(M_PI, VectorMath3(0,0,1))  * RotateMatrix(M_PI/2, VectorMath3(0,-1,0));

    GraphicsNode* enemyObject;

    float movementSpeed = 1;
    float rotAngle;

    unsigned int waveNum = 0;
public:
    Enemy();
    Enemy(std::shared_ptr<ShaderResource> shaders, VectorMath2 posIn);
    ~Enemy();
    void CreateSpawnWave(std::shared_ptr<ShaderResource> shader, MatrixMath viewMat, Tilegrid tilegrid);
    void MoveToPoint(VectorMath2 posIn, float deltaTime);
    void DrawEnemy();
    void Destroy();
};