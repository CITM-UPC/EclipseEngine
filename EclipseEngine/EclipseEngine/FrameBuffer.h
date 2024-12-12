#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class Framebuffer
{
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void Initialize();
    void Resize(int width, int height);

    inline unsigned int GetFBO() const { return m_FramebufferID; }
    inline unsigned int GetTextureID() const { return m_TextureID; }
    inline unsigned int GetRenderBufferID() const { return m_RenderbufferID; }
    inline void Getsize(int& w, int& h) { w = m_Width, h = m_Height; }
    inline void SetClearColor(float r, float g, float b, float a) { m_ccR = r, m_ccG = g, m_ccB = b, m_ccA = a; }
    inline void GetClearColor(float& r, float& g, float& b, float& a) { r = m_ccR , g = m_ccG , b = m_ccB, a = m_ccA; }
    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }

private:
    unsigned int m_FramebufferID;
    unsigned int m_TextureID;
    unsigned int m_RenderbufferID;

    int m_Width, m_Height;
    float m_ccR, m_ccG, m_ccB, m_ccA;
};

#endif // FRAMEBUFFER_H
