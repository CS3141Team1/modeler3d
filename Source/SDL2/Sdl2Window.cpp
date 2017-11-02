#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/Sdl2Window.h>
#include <SDL2/SdlMouse.h>

#include "GUI/AllWidgets.h"
#include "SDL2/SdlMouse.h"

using namespace std;

namespace Core
{

bool Sdl2Window::mGlewInit = false;

Sdl2Window::Sdl2Window(const string& title, uint width, uint height)
    : mTitle(title),
      mVisible(false),
      mWindow(nullptr)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    mWindow = SDL_CreateWindow
    (
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    mContext = SDL_GL_CreateContext(mWindow);

    GUInterface::Widget* root = new GUInterface::Widget(0,0,0,0);//GetWidth(),GetHeight());
    mEnv = new GUInterface::Environment(root);
    mMouse = new SdlMouse();

    const char* version = (const char*)glGetString(GL_VERSION);
    std::cout << version << std::endl;

    version = (const char*)glGetString(GL_RENDERER);
    std::cout << version << std::endl;
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
	SDL_Event e;

	mMouse->SetClicks(0,0,0);
	mMouse->SetRelativePosition(0,0);

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            SetVisible(false);
        }
        else if(e.type == SDL_MOUSEBUTTONUP)
        {
        	std::cout << "\n*********Click*********\n";
        	int32 button = (int)e.button.button;
        	int32 x = e.button.x;
        	int32 y = GetHeight() - e.button.y - 1;
        	int32 clicks = (int)e.button.clicks;

        	//std::cout << "X: " << x << ", Y: " << y << std::endl;
        	mMouse->SetPosition(x,y);

        	if(button == 1) mMouse->SetLeftClicks(clicks);
        	else if(button == 2) mMouse->SetMiddleClicks(clicks);
        	else mMouse->SetRightClicks(clicks);

        	mEnv->OnMouseButton(x,y,button,true);
        }
        else if(e.type == SDL_MOUSEMOTION)
        {
        	int32 x = e.motion.x;
        	int32 y = GetHeight() - e.motion.y - 1;
        	int32 xRel = e.motion.xrel;
        	int32 yRel = e.motion.yrel;

        	mMouse->SetPosition(x,y);
        	mMouse->SetRelativePosition(xRel,yRel);
        }
    }

}

void Sdl2Window::SwapBuffers()
{
    SDL_GL_SwapWindow(mWindow);
    int width, height;
    SDL_GetWindowSize(mWindow, &width, &height);
    glViewport(0, 0, width, height);

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

SdlMouse* Sdl2Window::GetMouse()
{
	return mMouse;
}

GUInterface::Environment* Sdl2Window::GetEnvironment()
{
	return mEnv;
}

}
