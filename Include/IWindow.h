#pragma once

#include <string>

#include "GUI/Environment.h"
#include "Sdl2/SdlMouse.h"

namespace Video
{

class IGraphicsDevice;

}

namespace Core
{

/**
 * Interface for a window
 *
 * @author Nicholas Hamilton
 */
class IWindow
{
public:
    virtual ~IWindow() {}

    // get/set visibility
    virtual bool IsVisible() const = 0;
    virtual void SetVisible(bool visible) = 0;

    // get/set title
    virtual const std::string& GetTitle() const = 0;
    virtual void SetTitle(const std::string& title) = 0;

    // get/set size
    virtual uint GetWidth() const = 0;
    virtual uint GetHeight() const = 0;
    virtual void SetSize(uint width, uint height) = 0;

    virtual GUInterface::Environment* GetEnvironment() = 0;
    virtual SdlMouse* GetMouse() = 0;

    /**
     * Call to update input events
     */
    virtual void PollEvents() = 0;

    /**
     * Call to render to screen
     */
    virtual void SwapBuffers() = 0;
};

}
