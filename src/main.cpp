#include <psp2/kernel/processmgr.h>
#include "kit_override/core/CustomApp.hh"
#include "views/Welcome.hh"
#include "views/settings/Settings.hh"


int main() {


    auto *welcome = new Welcome("Welcome");
    auto *settings = new Settings("Settings");

    auto *app = new CustomApp("Welcome");
    app->insertView(welcome);
    app->insertView(settings);


    app->main();

}
