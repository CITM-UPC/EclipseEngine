#ifndef PANEL_H
#define PANEL_H

#include <string>
#include <vector>

class Panel 
{
public:
    Panel(const std::string& name) : m_Name(name), m_Visible(false) {}
    virtual ~Panel() {}

    virtual void Render() = 0;

    const std::string& GetName() const { return m_Name; }
    bool IsVisible() const { return m_Visible; }
    void SetVisible(bool visible) { m_Visible = visible; }
	virtual bool CleanUp() { return true; }

protected:
    std::string m_Name;
    bool m_Visible;
};

#endif // PANEL_H