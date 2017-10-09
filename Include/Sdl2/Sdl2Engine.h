#pragma once

#include "IEngine.h"
#include "Sdl2/Sdl2Window.h"

namespace Core
{

class Sdl2Engine : public IEngine
{
public:
    Sdl2Engine();
    virtual ~Sdl2Engine();

    virtual Float64 GetFrames() { return mFps; }
    virtual Float64 GetUpdates() { return mUps; }

    virtual IWindow* GetWindow() { return mWindow; }
    virtual Video::IGraphicsDevice* GetGraphicsDevice();

    virtual void Start(Application* app);
    virtual void Stop();
private:
    Sdl2Window* mWindow;
    Application* mApplication;
    bool mRunning;
    Float64 mFps;
    Float64 mUps;
};

}
