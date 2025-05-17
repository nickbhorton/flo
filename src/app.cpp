#include "app.h"
#include "log/log.h"

flo::Application::Application()
{
#ifdef FLO_DEBUG
    flo::log::debug("flo::Application constructor");
#endif
}
flo::Application::~Application()
{
#ifdef FLO_DEBUG
    flo::log::debug("flo::Application destructor");
#endif
}

void flo::Application::run() {}
