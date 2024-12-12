#ifndef BASICPANEL_H
#define BASICPANEL_H

#include "Panel.h"
#include <string>

class BasicPanel : public Panel
{
public:
    BasicPanel(const std::string& name, bool isVisible = false);
    void Render() override;
};

#endif // BASICPANEL_H
