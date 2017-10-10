#include "Sdl2/Sdl2Engine.h"

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include "ThreadUtil.h"
#include "TimeUtil.h"
#include "Types.h"

#include <iostream>

namespace Core
{

bool SdlInit = false;
bool GlewInit = false;

void InitSdl()
{
    if (!SdlInit)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SdlInit = true;
    }
}

void InitGlew()
{
    if (!GlewInit)
    {
        glewExperimental = GL_TRUE;
        glewInit();
        GlewInit = true;
    }
}

Sdl2Engine::Sdl2Engine()
    : mApplication(nullptr),
      mRunning(false),
      mFps(0.0),
      mUps(0.0)
{
    InitSdl();
    mWindow = new Sdl2Window("Test", 800, 600);
}

Sdl2Engine::~Sdl2Engine()
{
    delete mWindow;
}

Video::IGraphicsDevice* Sdl2Engine::GetGraphicsDevice()
{
    return nullptr;
}

void Sdl2Engine::Start(Application* app)
{
    if (app == nullptr) return;

    mRunning = true;
    mWindow->SetVisible(true);
    InitGlew();

    app->OnInit();

    uint32 tps = 0;
    float64 ticks = Time::Seconds();
    float64 skipTicks = 1.0 / 60.0;

    uint32 fps = 0;
    float64 frames = Time::Seconds();
    float64 skipFrames = 1.0 / 60.0;

    float64 time = Time::Seconds();

    while (mRunning)
    {
        while (ticks < Time::Seconds())
        {
            ticks += skipTicks;
            tps++;
            mWindow->PollEvents();
            app->OnUpdate(0.0);
        }

        if (frames < Time::Seconds())
        {
            frames += skipFrames;
            fps++;
            app->OnRender();
            mWindow->SwapBuffers();
        }

        if (Time::Seconds() - time >= 1.0)
        {
            std::cout << "FPS: " << fps << ", ";
            std::cout << "Ticks: " << tps << std::endl;
            fps = tps = 0;
            time = Time::Seconds();
        }

        mRunning &= mWindow->IsVisible();

        Thread::Sleep(std::max(0.0, (ticks - Time::Seconds()) * 1000));
    }

    app->OnExit();
}

void Sdl2Engine::Stop()
{
    mRunning = false;
}

}
