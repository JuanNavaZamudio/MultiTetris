#include <stdio.h>
#include <string>

#include "Button.h"

#ifndef INSTRUCTIONSBUTTON_H
#define INSTRUCTIONSBUTTON_H


class InstructionsButton: public Button
{
    public:

        bool action();
        void paintInstructions();

        InstructionsButton();
        InstructionsButton(int x, int y, int width, int height, std::string text, int fontSize);
        virtual ~InstructionsButton();

    protected:

    private:
};

#endif // INSTRUCTIONSBUTTON_H
