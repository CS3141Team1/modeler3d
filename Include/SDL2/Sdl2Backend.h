#pragma once

#include <IBackend.h>
#include <SDL2/Sdl2Window.h>

namespace Core
{

class Sdl2Backend: public IBackend
{
public:
    Sdl2Backend();
    ~Sdl2Backend();

    void Init();
    void Destroy();

    IWindow* GetWindow() { return &mWindow; }
private:
    static void InitSdl2();

    static bool mSdl2Init;

    Sdl2Window mWindow;
};

}
