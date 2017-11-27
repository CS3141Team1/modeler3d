#pragma once

namespace Gui
{

class Widget;

class IAction
{
public:
    virtual ~IAction() {}

    virtual void OnActionPerformed(Widget* caller) = 0;
};

class IMoveAction
{
public:
    virtual ~IMoveAction() {}

    virtual void OnActionPerformed(Widget* caller, int32 x, int32 y, int32 dx, int32 dy, uint32 buttons) = 0;
};

}
