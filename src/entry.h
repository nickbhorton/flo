#pragma once

#include <memory>

#include "app.h"

extern std::unique_ptr<flo::Application> create_application();

int main(int argc, char** argv)
{
    std::unique_ptr<flo::Application> app = create_application();
    app->run();
}
