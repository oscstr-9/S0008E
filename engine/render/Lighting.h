#include "core/VectorMath.h"
#include "core/MatrixMath.h"
#include "render/ShaderResource.h"
#include <memory>
#include <vector>

class Lighting
{
	VectorMath3 pos;
	VectorMath3 color;
	float intensity;

public:
	Lighting(VectorMath3 posIn, VectorMath3 colorIn, float intensityIn);
	~Lighting();
	void setIntensity(float intensityIn);
	void setPos(VectorMath3 posIn);
	void setLightColor(VectorMath3 colorIn);

	VectorMath3 getColor();
	VectorMath3 getPos();
	float getIntensity();
};

namespace Light{
	void bindLight(std::shared_ptr<ShaderResource> shader, Lighting light, VectorMath3 cameraPos);
	void bindLights(std::shared_ptr<ShaderResource> shader, std::vector<Lighting> lights);
};
