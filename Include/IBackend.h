#pragma once

#include "IGraphicsDevice.h"
#include "IWindow.h"

namespace Core
{

/**
 * Backend for an application,
 * includes window and graphics support
 *
 * @author Nicholas Hamilton
 */
class IBackend
{
public:
    virtual ~IBackend() {}

    /**
     * Called when application is starting up
     */
    virtual void Init() = 0;

    /**
     * Called when application is updating
     *
     * @param dt Time since last update in seconds
     */
    virtual void Update(float64 dt) = 0;

    /**
     * Called when application is ending
     */
    virtual void Destroy() = 0;

    /**
     * Get pointer to window
     */
    virtual IWindow* GetWindow() = 0;

    /**
     * Get pointer to graphics device
     */
    virtual Video::IGraphicsDevice* GetGraphicsDevice() = 0;
};

}
