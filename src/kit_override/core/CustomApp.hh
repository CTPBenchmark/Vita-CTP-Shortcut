#ifndef VITAMATERIALKIT_CUSTOMAPP_HH
#define VITAMATERIALKIT_CUSTOMAPP_HH


#include "../../kit/core/App.hh"
#include "CustomUi.hh"

class CustomApp : App {
private:
    vita2d_texture *wallolo;
public:
    CustomApp(const char *firstView);
protected:
    void beforeView() override;
};


#endif //VITAMATERIALKIT_CUSTOMAPP_HH
