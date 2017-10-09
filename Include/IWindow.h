#pragma once

#include <string>

namespace Video
{

class IGraphicsDevice;

}

namespace Core
{

class IWindow
{
public:
    virtual ~IWindow() {}

    virtual bool IsVisible() const = 0;
    virtual void SetVisible(bool visible) = 0;

    virtual const std::string& GetTitle() const = 0;
    virtual void SetTitle(const std::string& title) = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;
    virtual void SetSize(unsigned int width, unsigned int height) = 0;

    virtual void PollEvents() = 0;
    virtual void SwapBuffers() = 0;
};

}
