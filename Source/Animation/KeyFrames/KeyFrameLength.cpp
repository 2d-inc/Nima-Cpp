#include "KeyFrameLength.hpp"
#include "../../ActorBone.hpp"

using namespace nima;

void KeyFrameLength::setValue(ActorNode* node, float value, float mix)
{
	// Hard assumption this is a bone.
	ActorBone* bone = reinterpret_cast<ActorBone*>(node);
	bone->length(bone->length() * (1.0f - mix) + value * mix);
}