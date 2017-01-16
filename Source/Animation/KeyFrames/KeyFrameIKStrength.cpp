#include "KeyFrameIKStrength.hpp"
#include "../../ActorIKTarget.hpp"

using namespace nima;

void KeyFrameIKStrength::setValue(ActorNode* node, float value, float mix)
{
	// Hard assumption this is a bone.
	ActorIKTarget* ikTarget = reinterpret_cast<ActorIKTarget*>(node);
	ikTarget->strength(ikTarget->strength() * (1.0f - mix) + value * mix);
}