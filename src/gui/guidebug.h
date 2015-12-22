#ifndef GUIDEBUG_H
#define GUIDEBUG_H

#include <SFGUI/SFGUI.hpp>
#include <glm/glm.hpp>

class guiDebug
{
    public:
        guiDebug();

        void initialize(sfg::Desktop *desktop);
        void setPlayerPosition(glm::vec3 pos);
        void setPlayerTarget(glm::vec3 pos, uint8_t type, uint8_t hp);
        void setRenderData(int rendered, int loaded);
        void setFps(int fps);
        void setCursor(int x, int y);

    protected:
    private:

        sfg::Label::Ptr m_labelPlayerPosition;
        sfg::Label::Ptr m_labelPlayerTarget;
        sfg::Label::Ptr m_labelBlocksLoaded;
        sfg::Label::Ptr m_labelFps;
        sfg::Label::Ptr m_labelCursor;
        sfg::Box::Ptr box;
        sfg::Window::Ptr window_gui;
};

#endif // GUIDEBUG_H
