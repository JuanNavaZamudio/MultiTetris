#include "Button.h"

#ifndef STARTBUTTON_H
#define STARTBUTTON_H


class StartButton: public Button
{
    public:

        StartButton();
        virtual ~StartButton();

        bool action();

    protected:

    private:
};

#endif // STARTBUTTON_H
