#pragma once

#include "IAction.h"
#include "Widget.h"

namespace Gui
{

class Screen : public Widget
{
public:
    Screen(IMoveAction* action) : mAction(action) {}
    ~Screen() {}

    void OnUpdate(float64 dt)
    {
        this->SetBounds(
                GetParent()->GetX(),
                GetParent()->GetY(),
                GetParent()->GetWidth(),
                GetParent()->GetHeight());
    }

    void OnMouseMove(int32 x, int32 y, int32 w, int32 h, uint32 buttons)
    {
        if (mAction) mAction->OnActionPerformed(this, x, y, w, h, buttons);
    }
private:
    IMoveAction* mAction;
};

}
