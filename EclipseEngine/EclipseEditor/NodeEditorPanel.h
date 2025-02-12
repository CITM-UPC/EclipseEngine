#ifndef NODEEDITORPANEL_H
#define NODEEDITORPANEL_H

#include "Panel.h"
#include <string>
#include <vector>
#include "imgui-node-editor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

struct Node {
    int Id;
    int InputPinId;
    int OutputPinId;
};

class NodeGraph {
public:
    std::vector<Node> nodes;

    void CreateExampleNode(int id) {
        Node node;
        node.Id = id;
        node.InputPinId = id * 2;   // Unique Input Pin ID
        node.OutputPinId = id * 2 + 1; // Unique Output Pin ID

        nodes.push_back(node);
    }
};

class NodeEditorPanel : public Panel
{
public:
    NodeEditorPanel(const std::string& name, bool isVisible = true);
    ~NodeEditorPanel();

    void Render() override;

private:
    ed::EditorContext* m_EditorContext;
    NodeGraph m_NodeGraph;

    void RenderNodes();
};

#endif // NODEEDITORPANEL_H
