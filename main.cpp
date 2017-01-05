
#include "ui/app/App.h"
#include "ui/frags/WindowOptions.h"

#include <memory>

using namespace ui::app;
using namespace ui::frags;

int main(int argc, char **argv) {
    AppOptions options = AppOptions::parseCmdLine(argc, argv);

    WindowOptions& windowOptions = options.getMainWindowOptions();
    windowOptions.setWidth(640);
    windowOptions.setHeight(480);

    std::unique_ptr<App> app = App::create(options);
    return app.get()->run();
}