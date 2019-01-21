#ifndef VITAMATERIALKIT_VIEWSCONTROLLER_HH
#define VITAMATERIALKIT_VIEWSCONTROLLER_HH

#define VIEWS_CONTROLLER_EXIT "VIEWS_CONTROLLER_EXIT"
#define VIEWS_CONTROLLER_EXIT_LOOP "VIEWS_CONTROLLER_EXIT_LOOP"

#include <string>

class ViewsController {
private:
    std::string actualView;
public:
    ViewsController(std::string actualView);

    std::string getActualView();
    void setActualView(std::string actualView);
};


#endif //VITAMATERIALKIT_VIEWSCONTROLLER_HH
