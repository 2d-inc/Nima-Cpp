#include "KeyFrameRotation.hpp"
#include "../../ActorNode.hpp"

using namespace nima;

void KeyFrameRotation::setValue(ActorNode* node, float value, float mix)
{
	node->rotation(node->rotation() * (1.0f - mix) + value * mix);
}