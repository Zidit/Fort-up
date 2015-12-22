#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H


#include <string>
#include "resource.h"
#include "resourcetexture.h"
#include "resourceshader.h"


const std::string texture_path = "./res/images/";
const std::string shader_path = "./res/shaders/";

class resourceManager
{
    public:
        resourceManager();
        virtual ~resourceManager();


        unsigned int getResourseCount(){return 0;}
        unsigned int getMemoryUsage(){return 0;}

        resourceTexture* loadTexture(std::string const &filename) {return mgrTexture.load(texture_path + filename);}
        resourceShader*  loadShader(std::string const &filename) {return mgrShader.load(shader_path + filename);}
        void reloadShader(std::string const &filename) {mgrShader.reload(shader_path + filename);}

    protected:
    private:

        ResourceManager<resourceTexture> mgrTexture;
        ResourceManager<resourceShader> mgrShader;


};



#endif // RESOURCEMANAGER_H
