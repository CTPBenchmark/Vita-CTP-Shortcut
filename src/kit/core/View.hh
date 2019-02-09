#ifndef VITAMATERIALKIT_VIEW_HH
#define VITAMATERIALKIT_VIEW_HH

#include "ViewsController.hh"
#include "../Ui.hh"
#include "../Utils.hh"


class View {
protected:
 std::string name;
 Ui *ui;
 ViewsController *viewsController;
 Utils *utils;

public:
    View(std::string name);

    virtual void contents();
    virtual void controls();

    //Lifecycle event
    virtual void beforeEnter();
    virtual void beforeExit();
    virtual void mounted();

    std::string getName() const;

    void setViewsController(ViewsController *viewsController);
    void setUi(Ui *ui);
    void setUtils(Utils *utils);



};


#endif //VITAMATERIALKIT_VIEW_HH
