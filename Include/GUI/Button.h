#pragma once

#include <string>

#include "GUI/Widget.h"

#include "Math/ModelerMath.h"

namespace Gui
{

class IAction;

/**
 * button for a GUI
 *
 * @author Nicholas Hamilton
 */
class Button : public Widget
{
public:
    static const Core::Math::Vector3f UpColor;
    static const Core::Math::Vector3f DownColor;
    static const Core::Math::Vector3f HoverColor;

    Button(float32 x, float32 y, float32 w, float32 h, IAction* action = nullptr, const std::string& text = "");
    virtual ~Button();

    virtual void OnDraw(Video::GuiRenderer* gui);
    virtual void OnMouseButton(float32 x, float32 y, int32 button, bool down);

    IAction* GetAction() { return mAction; }
    void SetAction(IAction* action) { mAction = action; }
private:
    IAction* mAction;
    bool mDown;
    bool mHover;
    std::string mText;
};

}
