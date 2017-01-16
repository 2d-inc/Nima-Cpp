#include "KeyFrameScaleX.hpp"
#include "../../ActorNode.hpp"

using namespace nima;

void KeyFrameScaleX::setValue(ActorNode* node, float value, float mix)
{
	node->scaleX(node->scaleX() * (1.0f - mix) + value * mix);
}