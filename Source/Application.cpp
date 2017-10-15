#include "Application.h"

#include <iostream>

#include "ThreadUtil.h"
#include "TimeUtil.h"

using namespace std;

namespace Core
{

Application::Application(IBackend* backend)
    : Backend(backend),
      Window(backend->GetWindow()),
      Graphics(backend->GetGraphicsDevice())
{
}

Application::~Application()
{
}

void Application::Start()
{
    if (mRunning) return;

    mRunning = true;
    UpdateLoop();
}

void Application::Stop()
{
    if (!mRunning) return;

    mRunning = false;
}

void Application::UpdateLoop()
{
//    Backend->Init();
    Window->SetVisible(true);
    OnInit();

    uint32 ups = 0;
    float64 updates = Time::Seconds();
    float64 skipUpdates = 1.0 / 60.0;

    uint32 fps = 0;
    float64 frames = Time::Seconds();
    float64 skipFrames = 1.0 / 60.0;

    float64 time = Time::Seconds();

    while (mRunning)
    {
        while (updates < Time::Seconds())
        {
            updates += skipUpdates;
            ups++;
            Window->PollEvents();
            // TODO actual dt
            OnUpdate(skipUpdates);
        }

        if (frames < Time::Seconds())
        {
            frames += skipFrames;
            fps++;
            OnRender();
            Window->SwapBuffers();
        }

        if (Time::Seconds() - time >= 1.0)
        {
            cout << "Frames: " << fps << ", ";
            cout << "Updates: " << ups << endl;
            mFps = fps;
            mUps = ups;
            fps = ups = 0;
            time = Time::Seconds();
        }

        mRunning &= Window->IsVisible();

        Thread::Sleep(std::max(0.0, (updates - Time::Seconds()) * 1000));
    }

    OnDestroy();
    Backend->Destroy();
}

}
