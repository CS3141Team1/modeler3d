#pragma once

#include <SDL2/SDL.h>

#include "IWindow.h"
#include "Types.h"

namespace Core
{

class Sdl2Window : public IWindow
{
public:
    Sdl2Window(const std::string& title, uint width, uint height);
    virtual ~Sdl2Window();

    virtual bool IsVisible() const;
    virtual void SetVisible(bool visible);

    virtual const std::string& GetTitle() const;
    virtual void SetTitle(const std::string& title);

    virtual uint GetWidth() const;
    virtual uint GetHeight() const;
    virtual void SetSize(uint width, uint height);

    virtual void PollEvents();
    virtual void SwapBuffers();
private:
    std::string mTitle;
    uint mWidth;
    uint mHeight;
    bool mVisible;
    SDL_Window* mWindow;
    SDL_GLContext mContext;
};

}
