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

}
