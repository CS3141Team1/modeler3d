#include "Application.h"

namespace Core
{

Application::Application(IEngine* engine)
    : Engine(engine),
      GraphicsDevice(engine->GetGraphicsDevice())
{}

}
