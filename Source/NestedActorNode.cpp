#include "NestedActorNode.hpp"
#include "BlockReader.hpp"
#include "Actor.hpp"

using namespace nima;

NestedActorNode::NestedActorNode() :
	ActorRenderNode(ComponentType::NestedActorNode),
	m_Asset(nullptr),
	m_ActorInstance(nullptr)
{

}

NestedActorNode::~NestedActorNode()
{
	delete m_ActorInstance;
}

ActorComponent* NestedActorNode::makeInstance(Actor* resetActor)
{
	NestedActorNode* instanceNode = resetActor->makeNestedActorNode();
	instanceNode->copy(this, resetActor);
	return instanceNode;
}

void NestedActorNode::copy(NestedActorNode* node, Actor* resetActor)
{
	Base::copy(node, resetActor);

	m_DrawOrder = node->m_DrawOrder;
	m_Asset = node->m_Asset;
	/*Actor* actor = m_Asset->actor();
	if(actor != nullptr)
	{
		m_ActorInstance = m_Asset->actor()
	}*/
}

void NestedActorNode::updateWorldTransform()
{
	Base::updateWorldTransform();
	if(m_ActorInstance != nullptr)
	{
		m_ActorInstance->root()->overrideWorldTransform(worldTransform());
	}
}

NestedActorNode* NestedActorNode::read(Actor* actor, BlockReader* reader, NestedActorNode* node)
{
	if (node == nullptr)
	{
		node = new NestedActorNode();
	}

	Base::read(actor, reader, node);

	bool isVisible = reader->readByte() != 0;
	if (isVisible)
	{
		node->m_DrawOrder = (int)reader->readUnsignedShort();
		int assetIndex = (int)reader->readUnsignedShort();
		node->m_Asset = actor->nestedActorAsset(assetIndex);
	}
	return node;
}