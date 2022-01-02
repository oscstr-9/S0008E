 #pragma once
 #include "config.h"

class PerlinNoise
{
private:
    // 1D noise variables
    float *fPerlinNoise1D = nullptr;
    float *fNoiseSeed1D = nullptr;
    int nOutputSize = 256;

    // 2D noise variables
    float *fPerlinNoise2D = nullptr;
    float *fNoiseSeed2D = nullptr;
    int outputWidth = 256;
    int outputHeight = 256;
public:

    PerlinNoise(float outputSize);
    ~PerlinNoise();
    void PerlinNoise1D(int nOctaves, float fScalingBias);
    void PerlinNoise2D(int nOctaves, float fScalingBias);
    void NewSeed1D();
    void NewSeed2D();
    float *GetfPerlinNoise1D();
    float *GetfPerlinNoise2D();
};
