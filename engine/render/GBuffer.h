// Code borrowed from https://ogldev.org/www/tutorial35/tutorial35.html.

#include <GLFW/glfw3.h>
#include "ShaderResource.h"

class GBuffer
{
public:

    enum GBUFFER_TEXTURE_TYPE {
        GBUFFER_TEXTURE_TYPE_COLOR,
        GBUFFER_TEXTURE_TYPE_NORMAL,
        GBUFFER_TEXTURE_TYPE_POSITION,
        GBUFFER_TEXTURE_TYPE_TEXCOORD,
        GBUFFER_NUM_TEXTURES
    };

    GBuffer();

    ~GBuffer();

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void Bind();
    void BindTexturesToShader(std::shared_ptr<ShaderResource> shader);
    void Unbind();
    void Clear();

private:

    GLuint m_fbo;
    GLuint m_textures[GBUFFER_NUM_TEXTURES];
    GLuint m_depthTexture;

    float width;
    float height;
};