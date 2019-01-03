//
// Created by Applelo
//

#include "Checkbox.hh"


Checkbox::Checkbox(vita2d_texture* texture, int x, int y, int width, int height, bool status) : Buttons(texture, x, y, width, height) {
    _status = status;
}


Checkbox::~Checkbox() {

}

const bool Checkbox::getStatus() {
    return _status;
}

void Checkbox::setStatus(const bool status) {
    _status = status;
}

void Checkbox::display() {
    if (_isVisible) {

        if (_selected) {
            vita2d_draw_rectangle( _x-8, _y-8, _width+16, _height+16, RGBA8( 102, 186, 255, _alphaSelect));
            if (_compteurSelect<=100)
                _alphaSelect -= 2;
            else
                _alphaSelect += 2;
            if (_compteurSelect>=200)
                _compteurSelect=0;
            _compteurSelect++;
        }

        if (!_locked) {
            vita2d_draw_rectangle( _x-4, _y-4, _width+8, _height+8, _colorFirst);
            vita2d_draw_rectangle( _x-2, _y-2, _width+4, _height+4, _colorSecond);
            vita2d_draw_rectangle( _x, _y, _width, _height, _colorThird);
        }
        else {
            vita2d_draw_rectangle( _x-4, _y-4, _width+8, _height+8, RGBA8( 150, 150, 150, 100));
            vita2d_draw_rectangle( _x-2, _y-2, _width+4, _height+4, RGBA8( 130, 130, 130, 150));
            vita2d_draw_rectangle( _x, _y, _width, _height, RGBA8( 100, 100, 100, 175));
        }

        if (_status) {
            _centerW = _x + (_width/2) - (vita2d_texture_get_width(_texture)/2);
            _centerH = _y + (_height/2) - (vita2d_texture_get_height(_texture)/2);

            vita2d_draw_texture(_texture, _centerW, _centerH);
        }

    }
}