#include "config.h"
#include "Lighting.h"
#include "ShaderResource.h"

Lighting::Lighting(VectorMath3 posIn, VectorMath3 colorIn, float intensityIn)
{
	pos = posIn;
	color = colorIn;
	intensity = intensityIn;
}

Lighting::~Lighting()
{
}

void Lighting::setIntensity(float intensityIn) {
	intensity = intensityIn;
}

void Lighting::setPos(VectorMath3 posIn) {
	pos = posIn;
}

void Lighting::setLightColor(VectorMath3 colorIn) {
	color = colorIn;
}
VectorMath3 Lighting::getColor(){
	return color;
}
VectorMath3 Lighting::getPos(){
	return pos;
}
float Lighting::getIntensity(){
	return intensity;
}

namespace Light{
	// Sets all values required for lighting to work in the shader
void bindLight(std::shared_ptr<ShaderResource> shader, Lighting light, VectorMath3 cameraPos) {

	shader->setVec3(light.getColor(), "lightColor");
	shader->setVec3(light.getPos(), "lightPos");
	shader->setFloat(light.getIntensity(), "intensity");

	shader->setVec3(cameraPos, "viewPos");
	shader->setFloat(1, "specIntensity");
}

void bindLights(std::shared_ptr<ShaderResource> shader, std::vector<Lighting> lights){

	// Max of 16 lights atm
	VectorMath3 lightColor[16];
	VectorMath3 lightPos[16];
	float intensity[16];
	for (int i = 0; i < lights.size(); i++)
	{
		lightColor[i] = lights[i].getColor();
		lightPos[i] = lights[i].getPos();
		intensity[i] = lights[i].getIntensity();
	}

	shader->setLights(lightColor, lightPos, intensity, lights.size());
}
};