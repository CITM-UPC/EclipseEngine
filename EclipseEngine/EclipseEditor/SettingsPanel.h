#pragma once
#include "Panel.h"
#include <vector>

class SettingsPanel : public Panel
{
public:
	SettingsPanel(const std::string& name, bool isVisible = false);

	void Render() override;
	void AddSetting(const std::string& settingName);
	void RemoveSetting(const std::string& settingName);

private:
	std::vector<std::string> m_Settings;
};

