#include "SettingsPanel.h"
#include "imgui.h"

SettingsPanel::SettingsPanel(const std::string& name, bool isVisible) : Panel(name)
{
	SetVisible(isVisible);
}

void SettingsPanel::Render()
{
	if (!IsVisible()) return;

	ImGui::Begin(GetName().c_str(), &m_Visible);
	for (const auto& setting : m_Settings)
		ImGui::Text(setting.c_str());
	ImGui::End();
}

void SettingsPanel::AddSetting(const std::string& settingName)
{
	m_Settings.push_back(settingName);
}

void SettingsPanel::RemoveSetting(const std::string& settingName)
{
	m_Settings.erase(std::remove(m_Settings.begin(), m_Settings.end(), settingName), m_Settings.end());
}