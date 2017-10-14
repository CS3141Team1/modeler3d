#pragma once

#include "IBackend.h"
#include "Types.h"

namespace Core
{

class Application
{
public:
    Application(IBackend* backend);
    virtual ~Application();

    void Start();
    void Stop();

    float64 GetFrameRate() const { return mFps; }
    float64 GetUpdateRate() const { return mUps; }

    virtual void OnInit() = 0;
    virtual void OnUpdate(float64 dt) = 0;
    virtual void OnRender() = 0;
    virtual void OnDestroy() = 0;
protected:
    Core::IBackend* Backend = nullptr;
    Core::IWindow* Window = nullptr;
private:
    void UpdateLoop();

    bool mRunning = false;
    float64 mFps = 0.0;
    float64 mUps = 0.0;
};

}
