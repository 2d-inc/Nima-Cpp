#include "KeyFrameOpacity.hpp"
#include "../../ActorNode.hpp"

using namespace nima;

void KeyFrameOpacity::setValue(ActorNode* node, float value, float mix)
{
	node->opacity(node->opacity() * (1.0f - mix) + value * mix);
}