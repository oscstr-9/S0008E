#pragma once

#include "config.h"
#include <GL/glew.h>
#include "GBuffer.h"
#include <cstdio>

GBuffer::GBuffer(){}
GBuffer::~GBuffer(){}

bool GBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
    width = WindowWidth;
    height = WindowHeight;
    // Create the FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

    // Create the gbuffer textures
    glGenTextures(GBUFFER_NUM_TEXTURES, m_textures);
    glGenTextures(1, &m_depthTexture);

    for (unsigned int i = 0 ; i < GBUFFER_NUM_TEXTURES ; i++) {
       glBindTexture(GL_TEXTURE_2D, m_textures[i]);
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, NULL);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
    }

    // depth
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                  NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
    glDrawBuffers(GBUFFER_NUM_TEXTURES, DrawBuffers);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", Status);
        return false;
    }

    // restore default FBO
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    return true;
}

void GBuffer::Bind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}
void GBuffer::BindTexturesToShader(std::shared_ptr<ShaderResource> shader) {
    glBlitNamedFramebuffer(m_fbo, 0, 0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

    shader->setSampler(0, "color");
    shader->setSampler(1, "normal");
    shader->setSampler(2, "worldPos");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_COLOR]);

    //glBindTexture(GL_TEXTURE_2D, pixel_texture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMAL]);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION]);
}

void GBuffer::Unbind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GBuffer::Clear() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
    glDrawBuffers(GBUFFER_NUM_TEXTURES, DrawBuffers);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}