#include "world.h"
#include "utils.h"
#include <SFML/Window.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
#include "PolyVoxCore/Raycast.h"

template <typename VoxelType>
bool isQuadNeeded<VoxelType>::operator()(VoxelType back, VoxelType front, uint32_t& materialToUse, PolyVox::FaceNames dir)
{
    blockRenderData f = getRenderData(front);
    blockRenderData b = getRenderData(back);

    if(b.useDeafultRender && !f.useDeafultRender)
    {
        if (dir == PolyVox::PositiveY) materialToUse =  b.materialTop;
        else if (dir == PolyVox::NegativeY) materialToUse =  b.materialBottom;
        else materialToUse =  b.materialSide;

        return true;
    }

    return false;
}

template <typename VoxelType>
blockRenderData isQuadNeeded<VoxelType>::getRenderData(rawBlockData rawData)
{
    blockData data;
    data.rawData = rawData;
    return blockList->at(data.id).renderData;

}


void world::loadVoxelData(const PolyVox::ConstVolumeProxy<rawBlockData> &volume, const PolyVox::Region& region)
{


    if (region.getLowerCorner().getY() < 0 || region.getUpperCorner().getY() > 64) return;


    std::stringstream filename;
    filename << "../world/reg" << region.getLowerCorner() << ".mcc";
    std::ifstream myfile;
    //std::cout << "Region " << region.getLowerCorner() << "-" << region.getUpperCorner() << " loading: " << filename.str() << "\n";
    myfile.open (  filename.str(), std::ios::binary | std::ios::in);
    if (myfile.is_open()) {

        for (int z = region.getLowerCorner().getZ(); z <= region.getUpperCorner().getZ(); z++)
        {
            for (int x = region.getLowerCorner().getX(); x <= region.getUpperCorner().getX(); x++)
            {
                for (int y = region.getLowerCorner().getY(); y <= region.getUpperCorner().getY(); y++)
                {
                    rawBlockData vox;
                    myfile.read((char *) &vox, sizeof(vox));
                    volume.setVoxelAt(x,y,z, vox);

                }
            }
        }
      //  std::cout << "Region " << region.getLowerCorner() << "-" << region.getUpperCorner() << " loaded: " << filename.str() << "\n";
        myfile.close();
    }
    else {


        for (int z = region.getLowerCorner().getZ(); z <= region.getUpperCorner().getZ(); z++)
        {
            for (int x = region.getLowerCorner().getX(); x <= region.getUpperCorner().getX(); x++)
            {
                for (int y = region.getLowerCorner().getY(); y <= region.getUpperCorner().getY(); y++)
                {
                    float a = glm::perlin(glm::vec3(x / 32.f, z / 32.f, y / 32.f));

                    rawBlockData voxel;

                    voxel = block(1, defaultBlockData[1]).getRawData();

                    if( a > 0.1)
                    {
                        voxel = block(0, defaultBlockData[0]).getRawData();
                    }
                    if(x == 0 && z == 0)
                    {
                        voxel = block(1, defaultBlockData[1]).getRawData();

                    }
                    if (y < 2)
                    {
                        voxel = block(2, defaultBlockData[2]).getRawData();
                    }

                    volume.setVoxelAt(x, y, z, voxel);
                }
            }
        }
    }
}

void world::saveVoxelData(const PolyVox::ConstVolumeProxy<rawBlockData> &voxel, const PolyVox::Region& region)
{

    std::stringstream filename;
    filename << "../world/reg" << region.getLowerCorner() << ".mcc";
    std::ofstream myfile;
    myfile.open (  filename.str(), std::ios::binary | std::ios::trunc | std::ios::out);
    if (myfile.is_open()) {

        for (int z = region.getLowerCorner().getZ(); z <= region.getUpperCorner().getZ(); z++)
        {
            for (int x = region.getLowerCorner().getX(); x <= region.getUpperCorner().getX(); x++)
            {
                for (int y = region.getLowerCorner().getY(); y <= region.getUpperCorner().getY(); y++)
                {
                    rawBlockData vox = voxel.getVoxelAt(x, y, z);
                    myfile.write((char *) &vox, sizeof(vox));
                }
            }
        }


       // std::cout << "Region " << region.getLowerCorner() << "-" << region.getUpperCorner() << " saved: " << filename.str() << "\n";
    }
    myfile.close();
}




world::world()
{
    //ctor
}
world::~world()
{
    volume->flushAll();
    delete volume;
}

void world::initialize()
{
    volume = new PolyVox::LargeVolume<rawBlockData>(std::bind(&world::loadVoxelData, this, std::placeholders::_1, std::placeholders::_2), std::bind(&world::saveVoxelData, this, std::placeholders::_1, std::placeholders::_2));
    volume->setCompressionEnabled(true);
    volume->setMaxNumberOfBlocksInMemory(1024*8);
    volume->setMaxNumberOfUncompressedBlocks(1024);
    volume->setBorderValue(0);

    quadMaterial.setBlockList(&defaultBlockData);

    initializeAllBlocks();

}

void world::initializeAllBlocks()
{

    //blockName, type, value, toughness,  useDeafultRender, materialSide, materialTop, materialBottom
    defaultBlockData.push_back(staticBlockData{"empty", 0, 0, 0, blockRenderData{false, 0, 0, 0}});
    defaultBlockData.push_back(staticBlockData{"dirt", 1, 2, 1, blockRenderData{true, 2, 1, 2}});
    defaultBlockData.push_back(staticBlockData{"rock", 1, 5, 2, blockRenderData{true, 3, 3, 3}});

}




bool world::getMesh(const PolyVox::Region &block, PolyVox::SurfaceMesh<PolyVox::PositionMaterial> *mesh )
{
    sf::Clock timer;

    PolyVox::CubicSurfaceExtractor< PolyVox::LargeVolume<rawBlockData>, isQuadNeeded<rawBlockData> > surfaceExtractor(volume, block, mesh, true, quadMaterial);
    surfaceExtractor.execute();


    return true;
}



bool world::meshNeedUpadte(const PolyVox::Region &region)
{

    for(auto it = voxelUpdated.begin(); it != voxelUpdated.end(); it++)
    {
        if(region.containsPoint(*it))
        {
            return true;
        }

    }

    return false;


}

void world::tick()
{
    voxelUpdated.clear();
}

void world::save()
{

    volume->flushAll();

}


class RaycastTestFunctor
{
public:
	//RaycastTestFunctor(){;}


	bool operator()(const PolyVox::LargeVolume<rawBlockData>::Sampler& sampler)
	{
	    lastMiss = hit;
	    hit = sampler.getPosition();
		if(sampler.getVoxel())
            return false;
        return true;
	}

	PolyVox::Vector3DInt32 hit;
    PolyVox::Vector3DInt32 lastMiss;
};



bool world::raycast(const PolyVox::Vector3DFloat &startPoint, const PolyVox::Vector3DFloat &ray, PolyVox::Vector3DInt32 &blockPosition)
{

    RaycastTestFunctor test;
    PolyVox::RaycastResult raycastResult = PolyVox::raycastWithDirection(volume, startPoint, ray, test);

    if(raycastResult == PolyVox::RaycastResults::Interupted)
    {
        blockPosition = test.hit;
        return true;
    }
    return false;
}


bool world::raycast(const PolyVox::Vector3DFloat &startPoint, const PolyVox::Vector3DFloat &ray, PolyVox::Vector3DInt32 &blockPosition, PolyVox::Vector3DInt32 &lastMismatch)
{

    RaycastTestFunctor test;
    PolyVox::RaycastResult raycastResult = PolyVox::raycastWithDirection(volume, startPoint, ray, test);

    if(raycastResult == PolyVox::RaycastResults::Interupted)
    {
        blockPosition = test.hit;
        lastMismatch = test.lastMiss;
        return true;
    }
    return false;
}

block world::getBlock(const PolyVox::Vector3DInt32 &position)
{
        rawBlockData raw = volume->getVoxelAt(position);
        blockData data;
        data.rawData = raw;
        return block(raw , position, defaultBlockData[data.id]);
}

bool world::hitBlock(const PolyVox::Vector3DInt32 &position)
{
    block b = getBlock(position);
    if (b.hit())
    {
        volume->setVoxelAt(position, b.getRawData());
        poke(position);
        return true;
    }
    else return false;
}

bool world::useBlock(const PolyVox::Vector3DInt32 &position)
{
    block b = getBlock(position);
    if (b.use())
    {
        volume->setVoxelAt(position, b.getRawData());
        poke(position);
        return true;
    }
    else return false;
}

bool world::placeBlock(const PolyVox::Vector3DInt32 &position, const int id)
{
    block b = getBlock(position);
    if (!b.getRawData())
    {
        b = block(id, defaultBlockData[id]);
        volume->setVoxelAt(position, b.getRawData());
        poke(position);
        return true;
    }
    else return false;



}


void world::poke(const PolyVox::Vector3DInt32 &voxel)
{

    voxelUpdated.push_back(voxel);

    PolyVox::Vector3DInt32 vox = voxel;
    vox.setX(voxel.getX() + 1);
    voxelUpdated.push_back(vox);

    vox = voxel;
    vox.setY(voxel.getY() + 1);
    voxelUpdated.push_back(vox);

    vox = voxel;
    vox.setZ(voxel.getZ() + 1);
    voxelUpdated.push_back(vox);
}


bool world::getBoundingBox(const PolyVox::Vector3DInt32 &position, boundingBoxData& boundingBox)
{

    rawBlockData raw = volume->getVoxelAt(position);
    blockData data;
    data.rawData = raw;


    if(data.type == 1)
    {
        glm::vec3 currentPosition = castToVec3(position);
        boundingBox.max = currentPosition + glm::vec3(0.5, 0.5, 0.5);
        boundingBox.min = currentPosition - glm::vec3(0.5, 0.5, 0.5);


        return true;
    }

    return false;

}


