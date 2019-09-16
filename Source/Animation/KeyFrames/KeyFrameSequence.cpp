
#include "KeyFrameSequence.hpp"
#include "ActorImage.hpp"

#include <math.h>
#include <cmath>
#include <iostream>

using namespace nima;

bool KeyFrameSequence::read(BlockReader* reader, ActorComponent* component)
{
    if(KeyFrameNumeric::read(reader, component))
    {
        return true;
    }

    return false;
}

void KeyFrameSequence::setValue(ActorComponent* component, float value, float mix)
{
    ActorImage* node = static_cast<ActorImage*>(component);
    int v = static_cast<int>(std::floor(value));
    int c = node->sequenceFramesCount();
    int frameIdx = v % c;
    if(frameIdx < 0)
    {
        frameIdx += node->sequenceFramesCount();
    }
    node->sequenceFrame(frameIdx);
}