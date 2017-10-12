#include "InstructionsButton.h"

InstructionsButton::InstructionsButton()
{
    //ctor
}

InstructionsButton::InstructionsButton(int x, int y, int width, int height, std::string text, int fontSize)
:Button(x,y,width,height,text,fontSize){
}

InstructionsButton::~InstructionsButton()
{
    //dtor
}

bool InstructionsButton::action(){

    return false;
}

void InstructionsButton::paintInstructions(){

}
