/*
 **
 ** Made by Applelo
 **
 */

#include "Background.hh"

Background::Background() {
	this->backgroundColor = RGBA8(0,0,0,0);
	this->iconsColor = RGBA8(255,255,255,255);
	this->foregroundColor = RGBA8(0,0,0,0);
	this->speed = DEFAULT_SPEED;
	this->position = 0;
	this->texture = nullptr;
	this->imgWidth = 0;
	this->imgHeight = 0;
	this->calc = 0;
}

Background::Background(vita2d_texture* texture, int backgroundColor, int iconsColor) {
	this->texture = texture;
	this->imgWidth = vita2d_texture_get_width(texture);
	this->imgHeight = vita2d_texture_get_height(texture);
	this->backgroundColor = backgroundColor;
	this->iconsColor = iconsColor;
	this->foregroundColor = RGBA8(0,0,0,0);
	this->speed = DEFAULT_SPEED;
	this->position = 0;
	this->calc = 0;
}

Background::Background(vita2d_texture* texture, int backgroundColor, int iconColor, int foregroundColor, float speed) {
	this->texture = texture;
	this->imgWidth = vita2d_texture_get_width(texture);
	this->imgHeight = vita2d_texture_get_height(texture);
	this->backgroundColor = backgroundColor;
	this->iconsColor = iconColor;
	this->foregroundColor = foregroundColor;
	this->speed = speed;
	this->position = 0;
	this->calc = 0;
}

Background::~Background() {
}

//Setter
void Background::setTexture(vita2d_texture* texture){
	this->texture = texture;
	this->imgWidth = vita2d_texture_get_width(texture);
	this->imgHeight = vita2d_texture_get_height(texture);
}

void Background::setSpeed(int speed){
	this->speed = speed;
}

void Background::setBackgroundColor(int backgroundColor){
	this->backgroundColor = backgroundColor;
}

void Background::setIconColor(int iconColor){
	this->iconsColor = iconColor;
}

void Background::setForegroundColor(int foregroundColor){
	this->foregroundColor = foregroundColor;
}

//Getter
float Background::getPosition(){
	return this->position;
}

// Display
void Background::display() {
	this->position -= (speed * 0.1);
	this->calc = (int)floor(-position / 1000);

	 for (int _i = calc; _i < (4 * (calc + 1)); _i++) {
		 for (int _j = calc; _j < (4 * (calc + 1)); _j++) {
			vita2d_draw_rectangle(position + (imgWidth * _i), position + (imgHeight * _j), imgWidth, imgHeight, (unsigned int)backgroundColor);

			if (texture) {
		 		vita2d_draw_texture_tint(texture, position + (imgWidth * _i), position + (imgHeight * _j), (unsigned int)iconsColor);
			}

			vita2d_draw_rectangle(position + (imgWidth * _i), position + (imgHeight * _j), imgWidth, imgHeight, (unsigned int)foregroundColor);
		 }
	 }

}
