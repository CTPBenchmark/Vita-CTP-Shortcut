/*
 **
 ** Made by Applelo
 **
 */

#include "../include/Background.hh"

Background::Background() {
	_backgroundColor = COLOR_NIL;
	_iconColor = COLOR_WHITE;
	_foregroundColor = COLOR_NIL;
	_speed = 0.5;
	_position = 0;
	_texture = nullptr;
	_imgWidth = 0;
	_imgHeight = 0;
	_calc = 0;
	// _x = 0;
	// _y = 0;
	// _width = 100;
	// _height = 100;
}

Background::Background(vita2d_texture* texture, int backgroundColor, int iconColor) {
	_texture = texture;
	_imgWidth = vita2d_texture_get_width(texture);
	_imgHeight = vita2d_texture_get_height(texture);
	_backgroundColor = backgroundColor;
	_iconColor = iconColor;
	_foregroundColor = COLOR_NIL;
	_speed = 0.5;
	_position = 0;
	_calc = 0;
}

Background::Background(vita2d_texture* texture, int backgroundColor, int iconColor, int foregroundColor, float speed) {
	_texture = texture;
	_imgWidth = vita2d_texture_get_width(texture);
	_imgHeight = vita2d_texture_get_height(texture);
	_backgroundColor = backgroundColor;
	_iconColor = iconColor;
	_foregroundColor = foregroundColor;
	_speed = speed;
	_position = 0;
	_calc = 0;
}

Background::~Background() {
}

//Setter
void Background::setTexture(vita2d_texture* texture){
	_texture = texture;
	_imgWidth = vita2d_texture_get_width(texture);
	_imgHeight = vita2d_texture_get_height(texture);
}

void Background::setSpeed(float speed){
	_speed = speed;
}

void Background::setBackgroundColor(int backgroundColor){
	_backgroundColor = backgroundColor;
}

void Background::setLogoColor(int iconColor){
	_iconColor = iconColor;
}

void Background::setForegroundColor(int foregroundColor){
	_foregroundColor = foregroundColor;
}

//Getter
float Background::getPosition(){
	return _position;
}

// Display
void Background::displayBackground() {
	_position -= _speed;
	_calc = floor(-_position / 1000);
	 for (int _i = _calc; _i < (4 * (_calc + 1)); _i++) {
		 for (int _j = _calc; _j < (4 * (_calc + 1)); _j++) {
			vita2d_draw_rectangle(_position + (_imgWidth * _i), _position + (_imgHeight * _j), _imgWidth, _imgHeight, _backgroundColor);
			if (_texture)
		 		vita2d_draw_texture_tint(_texture, _position + (_imgWidth * _i), _position + (_imgHeight * _j), _iconColor);
			vita2d_draw_rectangle(_position + (_imgWidth * _i), _position + (_imgHeight * _j), _imgWidth, _imgHeight, _foregroundColor);
		 }
	 }

}
