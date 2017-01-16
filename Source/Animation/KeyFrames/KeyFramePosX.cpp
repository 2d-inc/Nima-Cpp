#include "KeyFramePosX.hpp"
#include "../../ActorNode.hpp"

using namespace nima;

void KeyFramePosX::setValue(ActorNode* node, float value, float mix)
{
	node->x(node->x() * (1.0f - mix) + value * mix);
}