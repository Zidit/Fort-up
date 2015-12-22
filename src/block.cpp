#include "block.h"

block::block(const rawBlockData rawData, const PolyVox::Vector3DInt32 &position, const staticBlockData& staticData)
{
    data.rawData = rawData;
    this->position = position;
    this->staticData = staticData;
}

block::block(const uint16_t ID, const staticBlockData& staticData)
{
    data.id = ID;
    data.type = staticData.type;
    data.value = staticData.value;
}

PolyVox::Vector3DInt32 block::getPosition()
{
    return position;
}

rawBlockData block::getRawData()
{
    return data.rawData;
}

int block::getID()
{
    return data.id;
}

int block::getType()
{
    return data.type;
}

int block::getValue()
{
    return data.value;
}

blockRenderData block::getRenderData()
{
    return staticData.renderData;
}

bool block::hit()
{
    if(staticData.toughness == 0) return false;

    int damage = 2;
    int dmg = damage / staticData.toughness;
    if (dmg >= data.value )
    {
        onBreak();
        data.rawData = 0;
        return true;
    }

    else
    {
        data.value -= dmg;
        return true;
    }
}

bool block::use()
{
    return false;
}
bool block::update()
{
    return false;
}

void block::onBreak()
{

}



block::~block()
{
    //dtor
}


