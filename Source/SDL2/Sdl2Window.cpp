#include "SDL2/Sdl2Window.h"

#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>

using namespace std;

namespace Core
{

bool Sdl2Window::mGlewInit = false;

Sdl2Window::Sdl2Window(const string& title, uint width, uint height)
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

void Sdl2Window::SetTitle(const std::string& title)
{
    // TODO
}

void Sdl2Window::SetSize(uint width, uint height)
{
    // TODO
}

void Sdl2Window::PollEvents()
{
    // TODO finish

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

void Sdl2Window::SetVisible(bool visible)
{
    if (mVisible == visible) return;

    mVisible = visible;
    if (mVisible)
    {
        SDL_ShowWindow(mWindow);
        InitGlew();
    }
    else
    {
        SDL_HideWindow(mWindow);
    }
}

void Sdl2Window::InitGlew()
{
    if (mGlewInit) return;

    mGlewInit = true;

    glewExperimental = GL_TRUE;
    glewInit();
}

}