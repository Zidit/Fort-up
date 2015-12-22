#ifndef WORLD_H
#define WORLD_H

#include <PolyVoxCore/CubicSurfaceExtractor.h>
#include <PolyVoxCore/MarchingCubesSurfaceExtractor.h>
#include <PolyVoxCore/SurfaceMesh.h>
#include <PolyVoxCore/LargeVolume.h>
#include <PolyVoxCore/ConstVolumeProxy.h>

#include <vector>
#include <glm/gtc/noise.hpp>
#include <string>
#include "block.h"
#include "entity.h"

template<typename VoxelType>
class isQuadNeeded
{
public:
    bool operator()(VoxelType back, VoxelType front, uint32_t& materialToUse, PolyVox::FaceNames dir);
    void setBlockList(std::vector<staticBlockData> *blockList) {this->blockList = blockList;}
private:
    std::vector<staticBlockData> *blockList;
    blockRenderData getRenderData(rawBlockData rawData);

};


class world
{
    public:
        world();
        ~world();
        void initialize();
        void tick();
        void save();

        bool getMesh(const PolyVox::Region &block, PolyVox::SurfaceMesh<PolyVox::PositionMaterial> *mesh );
        bool meshNeedUpadte(const PolyVox::Region &region);

        PolyVox::LargeVolume<rawBlockData>::Sampler *getSampler() {return new PolyVox::LargeVolume<rawBlockData>::Sampler(volume);}

        bool hitBlock(const PolyVox::Vector3DInt32 &position);
        bool useBlock(const PolyVox::Vector3DInt32 &position);
        bool placeBlock(const PolyVox::Vector3DInt32 &position, const int id);

        bool getBoundingBox(const PolyVox::Vector3DInt32 &position, boundingBoxData& boundingBox);

        block getBlock(const PolyVox::Vector3DInt32 &position);
        bool raycast(const PolyVox::Vector3DFloat &startPoint, const PolyVox::Vector3DFloat &ray, PolyVox::Vector3DInt32 &blockPosition);
        bool raycast(const PolyVox::Vector3DFloat &startPoint, const PolyVox::Vector3DFloat &ray, PolyVox::Vector3DInt32 &blockPosition, PolyVox::Vector3DInt32 &lastMismatch);

    protected:
    private:
        void poke(const PolyVox::Vector3DInt32 &voxel);

        PolyVox::LargeVolume<rawBlockData> *volume;
        std::vector<PolyVox::Vector3DInt32> needMeshUpdate;
        std::vector<PolyVox::Vector3DInt32> voxelUpdated;
        std::vector<staticBlockData> defaultBlockData;

        void initializeAllBlocks();

        isQuadNeeded<rawBlockData> quadMaterial;
        void saveVoxelData(const PolyVox::ConstVolumeProxy<rawBlockData> &voxel, const PolyVox::Region& region);
        void loadVoxelData(const PolyVox::ConstVolumeProxy<rawBlockData> &voxel, const PolyVox::Region& region);
};






#endif // WORLD_H
