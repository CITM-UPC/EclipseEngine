#ifndef CONSOLE_PANEL_H
#define CONSOLE_PANEL_H

#include "Panel.h"
#include <vector>
#include <string>

class ConsolePanel : public Panel 
{
public:
    ConsolePanel(const std::string& name, bool visible = true);

    void Render() override;
    void Log(const std::string& message);

private:
    std::vector<std::string> m_Logs; // Stores log messages
};

#endif // CONSOLE_PANEL_H