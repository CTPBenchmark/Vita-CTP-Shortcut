#include <psp2/kernel/processmgr.h>
#include "kit_override/core/CustomApp.hh"
#include "views/Welcome.hh"


int main() {


    auto *welcome = new Welcome("Welcome");

    auto *app = new CustomApp("Welcome");
    app->insertView(welcome);


    app->main();

}
