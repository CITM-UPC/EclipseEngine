#ifndef ASSETSPANEL_H
#define ASSETSPANEL_H

#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>

#include "EclipseEngine/Texture.h"
#include "Panel.h"
#include "ResourceImporter.h"

class GameObject;

class AssetsPanel : public Panel
{
public:
    AssetsPanel(const std::string& name, bool visible = true);

    void Render() override;

private:
    void RenderBreadcrumbNavigation();
    void RenderDeletePopUp();
    std::filesystem::path m_CurrentDirectory;
	ResourceImporter m_Importer;

    // Renaming logic
    bool m_IsRenaming = false;             
    std::string m_RenameBuffer;            // Holds the new file name
    std::filesystem::path m_RenamingPath;  // The file path being renamed

	bool m_ShowDeletePopup = false;
    std::filesystem::path m_DeletePath;

    const float iconSize = 80.0f;
    const int columns = 8; // Number of columns
    const char* payloadType = "ASSET_FILE";

	std::unique_ptr<Texture> m_FolderIcon;
    std::unordered_map<std::string, std::unique_ptr<Texture>> m_FileIcons;
    std::unique_ptr<Texture> m_DefaultFileIcon;
};

#endif // ASSETSPANEL_H
