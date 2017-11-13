#include "GUI/Button.h"

#include <iostream>

#include "GUI/IAction.h"

using namespace Core::Math;
using namespace Video;

namespace Gui
{

const Vector3f Button::UpColor(0.8);
const Vector3f Button::DownColor(0.4);
const Vector3f Button::HoverColor(0.6, 0.6, 0.8);

Button::Button(float32 x, float32 y, float32 w, float32 h, IAction* action)
    : Widget(x, y, w, h),
      mAction(action),
      mDown(false),
      mHover(false) {}

Button::~Button() {}

void Button::OnDraw(GuiRenderer* g)
{
    if (mDown)
    {
        g->SetColor(DownColor);
    }
    else if (mHover)
    {
        g->SetColor(HoverColor);
    }
    else
    {
        g->SetColor(UpColor);
    }

    g->FillRect(GetX(), GetY(), GetWidth(), GetHeight());
    g->SetColor(0, 0, 0);
    g->DrawText("Text", GetHeight() / 2, GetWidth() / 2, GetHeight() / 2);
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
