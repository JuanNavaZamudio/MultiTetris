#include "Text.h"
#include <stdio.h>
#include <string>

#ifndef BUTTON_H
#define BUTTON_H


class Button
{
    public:

        int x;
        int y;
        int width;
        int height;
        bool pushed;
        Text* text;

        Button();
        Button(int x, int y, int width, int height, std::string name, int fontSize);
        virtual ~Button();


        virtual bool action(){return false;}

    protected:

    private:
};

#endif // BUTTON_H
