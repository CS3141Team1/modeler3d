#pragma once

#include "IBackend.h"
#include "Types.h"

namespace Core
{

/**
 * Program base. Uses a backend to update and render
 *
 * @author Nicholas Hamilton
 */
class Application
{
public:
    Application(IBackend* backend);
    virtual ~Application();

    /**
     * Start the application, call this at the beginning
     */
    void Start();

    /**
     * Stop the application, call this when the program should quit
     */
    void Stop();

    /**
     * Get the current frames per second
     */
    float64 GetFrameRate() const { return mFps; }

    /**
     * Get the current updates per second
     */
    float64 GetUpdateRate() const { return mUps; }

    /**
     * Called when the application is initializing
     */
    virtual void OnInit() = 0;

    /**
     * Called when the application is updating
     *
     * @param dt Time since last update in seconds
     */
    virtual void OnUpdate(float64 dt) = 0;

    /**
     * Called when the application is rendering
     */
    virtual void OnRender() = 0;

    /**
     * Called when the application is ending
     */
    virtual void OnDestroy() = 0;
protected:
    /** Pointer to the backend being used */
    Core::IBackend* Backend = nullptr;
    /** Convenience pointer to the window being used */
    Core::IWindow* Window = nullptr;
    /** Convenience pointer to the graphics device being used */
    Video::IGraphicsDevice* Graphics = nullptr;
private:
    void UpdateLoop();

    bool mRunning = false;
    float64 mFps = 0.0;
    float64 mUps = 0.0;
};

}
