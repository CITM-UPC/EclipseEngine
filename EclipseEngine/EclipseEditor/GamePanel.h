#ifndef GAME_PANEL_H
#define GAME_PANEL_H

#include "EclipseEngine/Framebuffer.h"
#include "EclipseEngine/Camera.h"
#include "Panel.h"

class GamePanel : public Panel
{
public:
    GamePanel(const std::string& name, Framebuffer* framebuffer, Camera* camera, bool visible = true);
    ~GamePanel() {}

    void Render() override;

    void Resize(int width, int height);

private:
    Framebuffer* m_Framebuffer;
    Camera* m_camera;
};

#endif // GAME_PANEL_H
