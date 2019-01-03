/*
 **
 ** Made by Applelo
 **
 */


#include "Buttons.hh"

Buttons::Buttons() {
	_x = 0;
	_y = 0;
	_text = "";
	_width = 0;
	_height = 0;
	_centerW = 0;
	_centerH = 0;
	_locked = false;
	_isVisible = true;
	_selected = false;
	_alphaSelect = 255;
	_compteurSelect = 0;
	_texture = nullptr;
	_tfont = nullptr;
    _colorFirst = COLOR_BUTTON_FIRST;
    _colorSecond = COLOR_BUTTON_SECOND;
    _colorThird = COLOR_BUTTON_FIRST;
    _colorFont = COLOR_WHITE;
}

Buttons::Buttons(vita2d_pgf* font, const std::string name, int x, int y, int width, int height) {
	 _tfont = font;
	 _text = name;
	 _x = x;
	 _y = y;
	 _width = width;
	 _height = height;
	_centerW = 0;
	_centerH = 0;
	_locked = false;
	_isVisible = true;
	_selected = false;
	_alphaSelect = 255;
	_compteurSelect = 0;
	_texture = nullptr;
	_colorFirst = COLOR_BUTTON_FIRST;
	_colorSecond = COLOR_BUTTON_SECOND;
	_colorThird = COLOR_BUTTON_FIRST;
	_colorFont = COLOR_WHITE;
}

Buttons::Buttons(vita2d_pgf* font, const std::string name, int x, int y, int width, int height, unsigned int colorFirst, unsigned int colorSecond, unsigned int colorThird, unsigned int colorFont) {
	_tfont = font;
	_text = name;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_centerW = 0;
	_centerH = 0;
	_locked = false;
	_isVisible = true;
	_selected = false;
	_alphaSelect = 255;
	_compteurSelect = 0;
	_texture = nullptr;
	_colorFirst = colorFirst;
	_colorSecond = colorSecond;
	_colorThird = colorThird;
	_colorFont = colorFont;
}


Buttons::Buttons(vita2d_texture* texture, int x, int y, int width, int height) {
	 _texture = texture;
	 _text = "";
	 _x = x;
	 _y = y;
	 _width = width;
	 _height = height;
	_centerW = 0;
	_centerH = 0;
	_locked = false;
	_isVisible = true;
	_selected = false;
	_alphaSelect = 255;
	_compteurSelect = 0;
	_tfont = nullptr;
	_colorFirst = COLOR_BUTTON_FIRST;
	_colorSecond = COLOR_BUTTON_SECOND;
	_colorThird = COLOR_BUTTON_FIRST;
	_colorFont = COLOR_WHITE;
}

Buttons::~Buttons() {
}

//Setter
void Buttons::setX(const int x) {
	_x = x;
}

void Buttons::setY(const int y) {
	_y = y;
}

void Buttons::setText(const std::string text){
	_text = text;
}

void Buttons::setWidth(const int width){
	_width = width;
}

void Buttons::setHeight(const int height){
	_height = height;
}

void Buttons::setFont(vita2d_pgf* tfont){
	_tfont = tfont;
}

void Buttons::setLocked(const bool locked) {
	_locked = locked;
}
void Buttons::setIsVisible(const bool isVisible) {
	_isVisible = isVisible;
}
void Buttons::setSelected(const bool selected) {
	_selected = selected;
}

void Buttons::setTexture(vita2d_texture* texture){
	_texture = texture;
}

//Getter
const int Buttons::getX() const{
	return _x;
}

const int Buttons::getY() const{
	return _y;
}

const std::string Buttons::getText() const {
	return _text;
}

const int Buttons::getWidth() const{
	return _width;
}

const int Buttons::getHeight() const {
	return _height;
}

const bool Buttons::getLocked() const {
	return _locked;
}

const bool Buttons::getIsVisible() const {
	return _isVisible;
}

const bool Buttons::getSelected() const {
	return _selected;
}



// Display
void Buttons::display() {
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

		if (_tfont) {
			_centerW = _x + (_width / 2) - (vita2d_pgf_text_width(_tfont, 1.2, _text.c_str()) / 2);
			_centerH = _y + (_height / 2) + (vita2d_pgf_text_height(_tfont, 1.2, _text.c_str()) / 2);

			vita2d_pgf_draw_textf(_tfont, _centerW, _centerH, _colorFont, 1.2, _text.c_str());
		}
		else if (_texture) {
			_centerW = _x + (_width/2) - (vita2d_texture_get_width(_texture)/2);
			_centerH = _y + (_height/2) - (vita2d_texture_get_height(_texture)/2);

			vita2d_draw_texture(_texture, _centerW, _centerH);
		}

		}
}

//Touch
const bool Buttons::touchButton(const int x, const int y) const {

	if (x > _x && x < (_x + _width) && y > _y && y < (_y + _height) && !_locked)
		return true;

	return false;
}
