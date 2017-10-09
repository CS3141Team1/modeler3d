#include "Sdl2/Sdl2Engine.h"

#include <string>

using namespace std;

namespace Core
{

Sdl2Window::Sdl2Window(const string& title, unsigned int width, unsigned int height)
    : mTitle(title),
      mWidth(width),
      mHeight(height),
      mVisible(false),
      mWindow(nullptr)
{
    mWindow = SDL_CreateWindow
    (
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    mContext = SDL_GL_CreateContext(mWindow);
}

Sdl2Window::~Sdl2Window()
{
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
}

const std::string& Sdl2Window::GetTitle() const
{
    return mTitle;
}

void Sdl2Window::SetTitle(const std::string& title)
{
}

unsigned int Sdl2Window::GetWidth() const
{
    return mWidth;
}

unsigned int Sdl2Window::GetHeight() const
{
    return mHeight;
}

void Sdl2Window::SetSize(unsigned int width, unsigned int height)
{
}

void Sdl2Window::PollEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            SetVisible(false);
        }
    }
}

void Sdl2Window::SwapBuffers()
{
    SDL_GL_SwapWindow(mWindow);
}

bool Sdl2Window::IsVisible() const
{
    return mVisible;
}

void Sdl2Window::SetVisible(bool visible)
{
    if (mVisible == visible) return;

    mVisible = visible;
    if (mVisible)
    {
        SDL_ShowWindow(mWindow);
    }
    else
    {
        SDL_HideWindow(mWindow);
    }
}

}
