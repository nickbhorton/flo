#include "app.h"
#include "log/log.h"

flo::Application::Application() { flo::log::debug("flo::Application constructor"); }
flo::Application::~Application() { flo::log::debug("flo::Application destructor"); }

void flo::Application::run() {}
