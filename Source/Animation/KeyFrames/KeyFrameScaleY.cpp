#include "KeyFrameScaleY.hpp"
#include "../../ActorNode.hpp"

using namespace nima;

void KeyFrameScaleY::setValue(ActorNode* node, float value, float mix)
{
	node->scaleY(node->scaleY() * (1.0f - mix) + value * mix);
}