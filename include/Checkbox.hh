//
// Created by Applelo
//

#ifndef CHECKBOX_HH
#define CHECKBOX_HH

# include "Buttons.hh"

class Checkbox : public Buttons {
private:
    bool _status;

public:
    Checkbox(vita2d_texture* texture, int x, int y, int width, int height, bool status);
    virtual ~Checkbox();
    const bool getStatus();
    void setStatus(const bool status);
    virtual void display();


};


#endif //CHECKBOX_HH
