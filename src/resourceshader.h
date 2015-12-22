#ifndef RESOURCESHADER_H
#define RESOURCESHADER_H

#include <GL/glew.h>
#include <vector>
#include <string>

class resourceShader{
    public:
        resourceShader(std::string const &filename);
        ~resourceShader();

        void reload();
        void bind();
        GLuint getHandler() {return program_handle;}
        bool isLoaded() {return loaded;}

    private:
        bool loaded;
        int instances;
        std::string _filename;
        GLuint program_handle;
        std::vector<GLuint> objects;

        void load(std::string const &filename);
        bool compile(std::string const &filename);
        bool link();
};





#endif // RESOURCESHADER_H
