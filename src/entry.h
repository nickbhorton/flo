#pragma once

#include <memory>

#include "app.h"
#include "log/log.h"

extern std::unique_ptr<flo::Application> create_application();

int main(int argc, char** argv)
{
#ifdef FLO_DEBUG
    flo::log::debug("main function started");
#endif
    std::unique_ptr<flo::Application> app = create_application();
    app->run();
#ifdef FLO_DEBUG
    flo::log::debug("main function finished");
#endif
}
