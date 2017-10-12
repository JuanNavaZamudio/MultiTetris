#include <stdio.h>
#include <string>

#include "Button.h"

Button::Button()
{
    //dtor
}


Button::Button(int x, int y, int width, int height, std::string name, int fontSize)
{
    printf("building  button..\n");
    this->x = x;
    this->y = y;
    this->text = new Text(x + width * 1/4 ,y + height * 1 / name.size(), fontSize, name);
}

Button::~Button()
{
    //dtor
}
