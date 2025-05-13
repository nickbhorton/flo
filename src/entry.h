#pragma once

#include <memory>

#include "app.h"
#include "log/log.h"

extern std::unique_ptr<flo::Application> create_application();

int main(int argc, char** argv)
{
    flo::log::debug("main function started");
    std::unique_ptr<flo::Application> app = create_application();
    app->run();
    flo::log::debug("main function finished");
}
