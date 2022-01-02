#include <random>
#include <iostream>
#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(float outputSize){
    nOutputSize = outputSize;
    fNoiseSeed1D = new float[nOutputSize];
    fPerlinNoise1D = new float[nOutputSize];
    
    // Create an array of random numbers to act as a seed for the perlin noise
    for(int i = 0; i < nOutputSize; i++){
        fNoiseSeed1D[i] = (float)rand()/(float)RAND_MAX;
    }

    outputWidth = outputSize;
    outputHeight = outputSize;
    fPerlinNoise2D = new float[outputWidth*outputHeight];
    fNoiseSeed2D = new float[outputWidth*outputHeight];

    for(int i = 0; i < outputWidth * outputHeight; i++){
        fNoiseSeed2D[i] = (float)rand()/(float)RAND_MAX;
    }

}

PerlinNoise::~PerlinNoise(){
    //silent
    }

void PerlinNoise::NewSeed1D(){
        for(int i = 0; i < nOutputSize; i++){
        fNoiseSeed1D[i] = (float)rand()/(float)RAND_MAX;
    }
}
void PerlinNoise::NewSeed2D(){
        for(int i = 0; i < outputWidth * outputHeight; i++){
        fNoiseSeed2D[i] = (float)rand()/(float)RAND_MAX;
    }
}
void PerlinNoise::PerlinNoise1D(int nOctaves, float fScalingBias){
    for (int x = 0; x < outputWidth; x++)
    {  
        float fNoise = 0.0f;
        float fScale = 1.0f;
        float fScaleSum = 0.0f;

        for (int j = 0; j < nOctaves; j++)
        {
            // Make sample points that can later be linearly interpolated between
            int nPitch = nOutputSize >> j;
            int nSample1 = (x / nPitch) * nPitch;
            // % makes the samples able to wrap around in array
            int nSample2 = (nSample1 + nPitch) % nOutputSize;

            float fBlend = (float)(x - nSample1) / (float)nPitch;
            // Linear interpolation formula
            float fSample = (1.0f - fBlend) * fNoiseSeed1D[nSample1] + fBlend * fNoiseSeed1D[nSample2];

            fNoise += fSample * fScale;
            fScaleSum += fScale;
            fScale = fScale / fScalingBias;

        }
        fPerlinNoise1D[x] = fNoise / fScaleSum;
    }
}

void PerlinNoise::PerlinNoise2D(int nOctaves, float fScalingBias){
    for (int x = 0; x < outputWidth; x++)
    {
        for (int y = 0; y < outputHeight; y++)
        {
            float fNoise = 0.0f;
            float fScale = 1.0f;
            float fScaleSum = 0.0f;

            for (int j = 0; j < nOctaves; j++)
            {
                // Make sample points that can later be linearly interpolated between
                int nPitch = outputWidth >> j;
                int xSample1 = (x / nPitch) * nPitch;
                int ySample1 = (y / nPitch) * nPitch;
                // % makes the samples able to wrap around in array
                int xSample2 = (xSample1 + nPitch) % outputWidth;
                int ySample2 = (ySample1 + nPitch) % outputWidth;

                float xfBlend = (float)(x - xSample1) / (float)nPitch;
                float yfBlend = (float)(y - ySample1) / (float)nPitch;

                // Linear interpolation formula
                float fSampleT = (1.0f - xfBlend) * fNoiseSeed2D[ySample1 * outputWidth + xSample1] + xfBlend * fNoiseSeed2D[ySample1 * outputWidth + xSample2];
                float fSampleB = (1.0f - xfBlend) * fNoiseSeed2D[ySample2 * outputWidth + xSample1] + xfBlend * fNoiseSeed2D[ySample2 * outputWidth + xSample2];

                fScaleSum += fScale;
                fNoise += (yfBlend * (fSampleB - fSampleT) + fSampleT) * fScale;
                fScale = fScale / fScalingBias;

            }
            fPerlinNoise2D[y * outputWidth + x] = fNoise / fScaleSum;
        }
    }
}


float* PerlinNoise::GetfPerlinNoise1D(){
    return fPerlinNoise1D;
}

float* PerlinNoise::GetfPerlinNoise2D(){
    return fPerlinNoise2D;
}