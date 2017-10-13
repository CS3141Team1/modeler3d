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

    virtual float64 GetFrames() { return mFps; }
    virtual float64 GetUpdates() { return mUps; }

    virtual IWindow* GetWindow() { return mWindow; }
    virtual Video::IGraphicsDevice* GetGraphicsDevice() { return mWindow->GetGraphicsDevice(); }

    virtual void Start(Application* app);
    virtual void Stop();
private:
    Sdl2Window* mWindow;
    Application* mApplication;
    bool mRunning;
    float64 mFps;
    float64 mUps;
};

}
