#ifndef RESOURCETEXTURE_H
#define RESOURCETEXTURE_H

#include <GL/glew.h>
#include <string>


class resourceTexture
{
    public:
        resourceTexture(std::string const &filename);
        ~resourceTexture();

        void reload();
        void release();
        void bind();

        bool isLoaded() {return loaded;}

    private:
        bool loaded;
        int instances;
        std::string _filename;
        GLuint texture_handle;
        void load(std::string const &filename);

};


#endif // RESOURCETEXTURE_H


