#include "kit_override/core/CustomApp.hh"

#include "views/Welcome.hh"
#include "views/settings/Settings.hh"
#include "views/settings/Customization.hh"


int main() {
    auto *welcome = new Welcome("Welcome");
    auto *settings = new Settings("Settings");
    auto *customization = new Customization("Customization");

    auto *app = new CustomApp("Welcome");
    app->insertView(welcome);
    app->insertView(settings);
    app->insertView(customization);

    app->main();

}
