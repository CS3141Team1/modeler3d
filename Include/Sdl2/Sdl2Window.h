#pragma once

#include <SDL2/SDL.h>

#include "IWindow.h"

namespace Core
{

class Sdl2Window : public IWindow
{
public:
    Sdl2Window(const std::string& title, unsigned int width, unsigned int height);
    virtual ~Sdl2Window();

    virtual bool IsVisible() const;
    virtual void SetVisible(bool visible);

    virtual const std::string& GetTitle() const;
    virtual void SetTitle(const std::string& title);

    virtual unsigned int GetWidth() const;
    virtual unsigned int GetHeight() const;
    virtual void SetSize(unsigned int width, unsigned int height);

    virtual void PollEvents();
    virtual void SwapBuffers();
private:
    std::string mTitle;
    unsigned int mWidth;
    unsigned int mHeight;
    bool mVisible;
    SDL_Window* mWindow;
    SDL_GLContext mContext;
};

}
