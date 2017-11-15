#include "GUI/Button.h"

#include <iostream>

#include "GUI/IAction.h"

using namespace Core::Math;
using namespace Video;

namespace Gui
{

const Vector3f Button::UpColor(1.0);
const Vector3f Button::DownColor(0.6);
const Vector3f Button::HoverColor(0.6, 0.6, 0.8);

Button::Button(float32 x, float32 y, float32 w, float32 h, IAction* action, const std::string& text)
    : Widget(x, y, w, h),
      mAction(action),
      mDown(false),
      mHover(false),
      mText(text) {}

Button::~Button() {}

void Button::OnDraw(GuiRenderer* g)
{
    Vector3f col(1);

    if (mDown)
    {
        g->SetColor(DownColor);
        col = DownColor;
    }
    else if (mHover)
    {
        g->SetColor(HoverColor);
        col = HoverColor;
    }
    else
    {
        g->SetColor(UpColor);
        col = UpColor;
    }

    g->FillRect(GetX(), GetY(), GetWidth(), GetHeight());
    g->SetColor(Vector3f(1, 1, 1) * col);
    g->DrawText(mText, 15, GetX() + GetWidth() / 2, GetY() + GetHeight() / 2);
}

void Button::OnMouseButton(float32 x, float32 y, int32 button, bool down)
{
    if (mDown && !down)
    {
        if (mAction)
        {
            mAction->OnActionPerformed(this);
        }
    }

    mDown = down;
}

}
