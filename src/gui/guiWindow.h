#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include "guiObject.h"
#include <memory>
#include <list>
#include "gui/guiTypedef.h"

class guiWindow
{
    public:
        guiWindow();
        virtual ~guiWindow();

        void render();
        void addObject(guiObjectPtr object);

    protected:
    private:


};

#endif // GUIWINDOW_H
