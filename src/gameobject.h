#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include "resourcemanager.h"
#include <glm/glm.hpp>

class gameObject
{
    public:
        gameObject() : _static(false), _visible(true), _wireFrame(false){;}
        virtual ~gameObject(){;}

        virtual void _update(unsigned int dt) = 0;
        virtual void _render(glm::mat4 *matrix) = 0;
        virtual void init(resourceManager *mgr) = 0;
        virtual void destroy(resourceManager *mgr){;}

        void render(glm::mat4 *matrix)
        {
            if(_visible)
            {
                if(_wireFrame) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
                _render(matrix);
                if(_wireFrame) glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            }
        }
        void update(unsigned int dt) {if(!_static) _update(dt);}

        void setVisible(bool Visible) {_visible = Visible;}
        void setStatic(bool Static) {_static = Static;}
        void setWireFrame(bool WireFrame) {_wireFrame = WireFrame;}

        bool isVisible() {return _visible;}
        bool isStatis() {return _static;}
        bool isWireFrame() {return _wireFrame;}


    private:
        bool _static;
        bool _visible;
    protected:
        bool _wireFrame;
};

#endif // GAMEOBJECT_H
