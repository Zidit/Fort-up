#ifndef GUITYPEDEF_H_INCLUDED
#define GUITYPEDEF_H_INCLUDED

#include <memory>

class guiHandler;
class guiWindow;
class guiObject;
class guiImage;

typedef std::shared_ptr<guiHandler> guiHandlerPtr;
typedef std::shared_ptr<guiWindow> guiWindowPtr;
typedef std::shared_ptr<guiObject> guiObjectPtr;
typedef std::shared_ptr<guiImage> guiImagePtr;




#endif // GUITYPEDEF_H_INCLUDED
