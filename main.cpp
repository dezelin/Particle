
#include "ui/app/App.h"

#include <widgets/Button.h>

using namespace ui::app;
using namespace ui::widgets;

int main(int argc, char **argv) {
    try {
        AppOptions options = AppOptions::parseCmdLine(argc, argv);

        WindowOptions &windowOptions = options.getMainWindowOptions();
        windowOptions.setWidth(640);
        windowOptions.setHeight(480);

        std::unique_ptr<App> app = App::create(options);

        OverlayOptions overlayOptions;
        app->getMainWindow()->setOverlay(Overlay::create(overlayOptions));

        ButtonOptions button1Options;
        button1Options.setBgColor(Color::fromRgba(Color::Red));
        button1Options.setRect(Rectangle(100, 100, 300, 300));

        app->getMainWindow()->getOverlay()->addChild(
                Button::create(button1Options));

        ButtonOptions button2Options;
        button2Options.setBgColor(Color::fromRgba(Color::Green));
        button2Options.setRect(Rectangle(150, 150, 350, 350));

        app->getMainWindow()->getOverlay()->addChild(
                Button::create(button2Options));

        ButtonOptions button3Options;
        button3Options.setBgColor(Color::fromRgba(Color::Blue));
        button3Options.setRect(Rectangle(300, 100, 500, 500));

        app->getMainWindow()->getOverlay()->addChild(
                Button::create(button3Options));

        return app.get()->run();

    } catch (std::exception &e) {

    }

    return 1;
}