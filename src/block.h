#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>
#include <string>
#include <PolyVoxCore/LargeVolume.h>


typedef  uint32_t rawBlockData;


#pragma pack(push)
#pragma pack(1)
typedef union
{
    struct
    {
        uint8_t value;
        uint8_t type;
        uint16_t id;
    };
    rawBlockData rawData;
} blockData;
#pragma pack(pop)

typedef struct {
    bool useDeafultRender;
    uint32_t materialSide;
    uint32_t materialTop;
    uint32_t materialBottom;
} blockRenderData;

typedef struct {
    std::string blockName;

    uint8_t type;
    uint8_t value;
    uint8_t toughness;

    blockRenderData renderData;
} staticBlockData;




class block
{
    public:
        block(){;}
        block(const rawBlockData rawData, const PolyVox::Vector3DInt32 &position, const staticBlockData& staticData);
        block(const uint16_t ID, const staticBlockData& staticData);

        PolyVox::Vector3DInt32 getPosition();
        rawBlockData getRawData();
        int getID();
        int getType();
        int getValue();
        blockRenderData getRenderData();

        bool hit();
        bool use();
        bool update();

        virtual ~block();
    protected:
        blockData data;
        staticBlockData staticData;
        PolyVox::Vector3DInt32 position;

    private:
        void onBreak();
};



#endif // BLOCK_H
