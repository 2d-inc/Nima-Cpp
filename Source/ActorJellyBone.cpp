#include "ActorJellyBone.hpp"
#include "BlockReader.hpp"

using namespace nima;

ActorJellyBone::ActorJellyBone() : Base(ComponentType::ActorJellyBone)
{

}

ActorComponent* ActorJellyBone::makeInstance(Actor* resetActor)
{
	ActorJellyBone* instanceNode = new ActorJellyBone();
	instanceNode->copy(this, resetActor);
	return instanceNode;
}

ActorJellyBone* ActorJellyBone::read(Actor* actor, BlockReader* reader, ActorJellyBone* node)
{
    if(node == nullptr)
    {
        node = new ActorJellyBone();
    }

    // The Jelly Bone has a specialized read that doesn't go down the typical node path, this is because majority of the transform properties
    // of the Jelly Bone are controlled by the Jelly Controller and are unnecessary for serialization.
    ActorComponent::read(actor, reader, node);
    node->m_Opacity = reader->readFloat();
    node->m_IsCollapsedVisibility = reader->readByte() == 1;
    return node;
}