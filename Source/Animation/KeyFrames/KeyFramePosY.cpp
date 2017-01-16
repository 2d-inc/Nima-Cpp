#include "KeyFramePosY.hpp"
#include "../../ActorNode.hpp"

using namespace nima;

void KeyFramePosY::setValue(ActorNode* node, float value, float mix)
{
	node->y(node->y() * (1.0f - mix) + value * mix);
}