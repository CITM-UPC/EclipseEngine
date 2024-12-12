#ifndef FPS_PANEL_H
#define FPS_PANEL_H

#include "Panel.h"
#include <vector>

class FPSPanel : public Panel
{
public:
    FPSPanel(const std::string& name, bool isVisible = false);

    void Render() override;
    void Update(float fps, float ms);

private:
    static constexpr int BUFFER_SIZE = 100;
    std::vector<float> m_FPSBuffer;
    std::vector<float> m_MSBuffer;
    int m_CurrentIndex = 0;
};

#endif // FPS_PANEL_H