
#include "ui/app/App.h"

#include <memory>

using namespace ui::app;

int main(int argc, char **argv) {
    AppOptions options = AppOptions::parseCmdLine(argc, argv);
    std::unique_ptr<App> app = App::create(options);
    return app.get()->run();
}