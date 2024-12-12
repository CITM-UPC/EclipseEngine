#include "Framebuffer.h"
#include <GL/glew.h>
#include <stdexcept>

Framebuffer::Framebuffer(int width, int height)
    : m_Width(width), m_Height(height), m_ccR(0.1f), m_ccG(0.1f), m_ccB(0.1f), m_ccA(1.0f)
{
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_FramebufferID);
    glDeleteTextures(1, &m_TextureID);
    glDeleteRenderbuffers(1, &m_RenderbufferID);
}

void Framebuffer::Initialize() {
    glGenFramebuffers(1, &m_FramebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

    // Create color texture
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

    // Create depth-stencil renderbuffer
    glGenRenderbuffers(1, &m_RenderbufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferID);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(int width, int height)
{
    m_Width = width;
    m_Height = height;

    // Resize texture
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    // Resize renderbuffer
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
}
