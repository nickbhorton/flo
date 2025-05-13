#include <flo.h>

class Sandbox : public flo::Application
{
public:
    Sandbox() {}
    ~Sandbox() {}
};

std::unique_ptr<flo::Application> create_application() { return std::make_unique<Sandbox>(); }
