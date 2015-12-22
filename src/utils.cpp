
#include "utils.h"
#include <GL/glew.h>
PolyVox::Vector3DFloat roundVectorTo3DFloat(const PolyVox::Vector3DFloat &vec)
{
    PolyVox::Vector3DFloat tmp;
    tmp.setX(floor(vec.getX() + 0.5));
    tmp.setY(floor(vec.getY() + 0.5));
    tmp.setZ(floor(vec.getZ() + 0.5));
    return tmp;
}

PolyVox::Vector3DInt32 roundVectorTo3DInt(const PolyVox::Vector3DFloat &vec)
{
    PolyVox::Vector3DInt32 tmp;
    tmp.setX(floor(vec.getX() + 0.5));
    tmp.setY(floor(vec.getY() + 0.5));
    tmp.setZ(floor(vec.getZ() + 0.5));
    return tmp;
}

PolyVox::Vector3DFloat castTo3DFloat(const glm::vec3 &vec)
{
    PolyVox::Vector3DFloat tmp;
    tmp.setX(vec.x);
    tmp.setY(vec.y);
    tmp.setZ(vec.z);
    return tmp;
}

PolyVox::Vector3DInt32 castTo3DInt(const glm::vec3 &vec)
{
    return roundVectorTo3DInt(castTo3DFloat(vec));
}

glm::vec3 castToVec3(const PolyVox::Vector3DFloat &vec)
{
    glm::vec3 tmp;
    tmp.x = vec.getX();
    tmp.y = vec.getY();
    tmp.z = vec.getZ();
    return tmp;
}

glm::vec3 castToVec3(const PolyVox::Vector3DInt32 &vec)
{
    glm::vec3 tmp;
    tmp.x = vec.getX();
    tmp.y = vec.getY();
    tmp.z = vec.getZ();
    return tmp;
}


bool regionsOverlap(const PolyVox::Region &R1, const PolyVox::Region &R2){

    if(R1.containsPointInX(R2.getLowerCorner().getX()) || R1.containsPointInX(R2.getUpperCorner().getX()))
        if(R1.containsPointInY(R2.getLowerCorner().getY()) || R1.containsPointInY(R2.getUpperCorner().getY()))
            if(R1.containsPointInZ(R2.getLowerCorner().getZ()) || R1.containsPointInZ(R2.getUpperCorner().getZ()))
                return true;
    return false;
}

int floor(const int value, const int period){

    int m = value % period;

    if(value < 0 ) return value - m - period;
    else return value - m;
}



void glCheckError(unsigned int line)
{
    // Get the last error
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR)
    {
        std::string error = "unknown error";
        std::string description  = "no description";

        // Decode the error code
        switch (errorCode)
        {
            case GL_INVALID_ENUM :
            {
                error = "GL_INVALID_ENUM";
                description = "an unacceptable value has been specified for an enumerated argument";
                break;
            }

            case GL_INVALID_VALUE :
            {
                error = "GL_INVALID_VALUE";
                description = "a numeric argument is out of range";
                break;
            }

            case GL_INVALID_OPERATION :
            {
                error = "GL_INVALID_OPERATION";
                description = "the specified operation is not allowed in the current state";
                break;
            }

            case GL_STACK_OVERFLOW :
            {
                error = "GL_STACK_OVERFLOW";
                description = "this command would cause a stack overflow";
                break;
            }

            case GL_STACK_UNDERFLOW :
            {
                error = "GL_STACK_UNDERFLOW";
                description = "this command would cause a stack underflow";
                break;
            }

            case GL_OUT_OF_MEMORY :
            {
                error = "GL_OUT_OF_MEMORY";
                description = "there is not enough memory left to execute the command";
                break;
            }

            case GL_INVALID_FRAMEBUFFER_OPERATION_EXT :
            {
                error = "GL_INVALID_FRAMEBUFFER_OPERATION_EXT";
                description = "the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"";
                break;
            }
        }

        // Log the error
        std::cout << "An internal OpenGL call " << line << " failed: "
              << error << ", " << description
              << std::endl;
    }
}



