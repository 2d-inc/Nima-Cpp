#include "ActorBone.hpp"
#include "BlockReader.hpp"

using namespace nima;

ActorBone::ActorBone() : Base(ComponentType::ActorBone), m_FirstBone(nullptr), m_Jelly(nullptr)
{
}

ActorBone* ActorBone::read(Actor* actor, BlockReader* reader, ActorBone* node)
{
	if(node == nullptr)
	{
		node = new ActorBone();
	}

	Base::read(actor, reader, node);

	return node;
}

ActorComponent* ActorBone::makeInstance(Actor* resetActor)
{
	ActorBone* instanceNode = new ActorBone();
	instanceNode->copy(this, resetActor);
	return instanceNode;
}

void ActorBone::completeResolve()
{
	Base::completeResolve();
	for(ActorNode* node : m_Children)
	{
		if(node->type() == ComponentType::ActorBone)
		{
			ActorBone* bone = static_cast<ActorBone*>(node);	
			if(bone != nullptr)
			{
				m_FirstBone = bone;
				break;
			}
		}
	}
}