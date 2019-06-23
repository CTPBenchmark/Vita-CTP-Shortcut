#ifndef VITAMATERIALKIT_CUSTOMAPP_HH
#define VITAMATERIALKIT_CUSTOMAPP_HH

#include "kit/core/App.hh"

class CustomApp : public App {
public:
    CustomApp(const char *firstView);
protected:
    void beforeView() override;
};


#endif //VITAMATERIALKIT_CUSTOMAPP_HH
