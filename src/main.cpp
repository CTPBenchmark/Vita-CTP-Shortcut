#include <psp2/kernel/processmgr.h>
#include "kit_override/core/CustomApp.hh"


int main() {

    auto *app = new CustomApp("Welcome");
    app->main();

}
