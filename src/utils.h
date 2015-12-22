#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <math.h>
#include <glm/glm.hpp>
#include "PolyVoxCore/Vector.h"
#include "PolyVoxCore/LargeVolume.h"

PolyVox::Vector3DFloat roundVectorTo3DFloat(const PolyVox::Vector3DFloat &vec);
PolyVox::Vector3DInt32 roundVectorTo3DInt(const PolyVox::Vector3DFloat &vec);
PolyVox::Vector3DFloat castTo3DFloat(const glm::vec3 &vec);
PolyVox::Vector3DInt32 castTo3DInt(const glm::vec3 &vec);

glm::vec3 castToVec3(const PolyVox::Vector3DFloat &vec);
glm::vec3 castToVec3(const PolyVox::Vector3DInt32 &vec);


bool regionsOverlap(const PolyVox::Region &R1, const PolyVox::Region &R2);

int floor(const int value, const int period);
void glCheckError(unsigned int line);

#endif // UTILS_H_INCLUDED
