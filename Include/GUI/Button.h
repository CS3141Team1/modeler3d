#pragma once

#include <string>

#include "GUI/Widget.h"

#include "Math/ModelerMath.h"

namespace Gui
{

class IAction;

/**
 * Button for a GUI
 *
 * @author Nicholas Hamilton, Michael Conard
 */
class Button : public Widget
{
public:
    static const Core::Math::Vector3f UpColor;
    static const Core::Math::Vector3f DownColor;
    static const Core::Math::Vector3f HoverColor;

    /**
     * Constructor for a button.
     *
     * @param x x coord
     * @param y y coord
     * @param w width
     * @param h height
     * @param action The callback action for the button click
     * @param text The text on the button
     */
    Button(float32 x, float32 y, float32 w, float32 h, IAction* action = nullptr, const std::string& text = "");
    virtual ~Button();

    /**
     * Called when drawing the button
     *
     * @param gui the GuiRenderer pointer
     */
    virtual void OnDraw(Video::GuiRenderer* gui);
    /**
     * Called when mouse button clicked
     *
     * @param x mouse x
     * @param y mouse y
     * @param button which mouse button clicked
     * @param down is the button going down or up
     */
    virtual void OnMouseButton(float32 x, float32 y, int32 button, bool down);

    IAction* GetAction() { return mAction; }
    void SetAction(IAction* action) { mAction = action; }

    /**
     * Change the text on the button
     *
     * @param text the new text
     */
    void SetText(std::string text) { mText = text; }
private:
    IAction* mAction;
    bool mDown;
    bool mHover;
    std::string mText;
};

}
