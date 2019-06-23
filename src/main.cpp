#include "app/kit_override/core/CustomApp.hh"

#include "app/views/Welcome.hh"
#include "app/views/settings/Settings.hh"
#include "app/views/settings/Customization.hh"


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
