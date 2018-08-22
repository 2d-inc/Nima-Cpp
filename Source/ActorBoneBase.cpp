#include "ActorBoneBase.hpp"
#include "BlockReader.hpp"

using namespace nima;

ActorBoneBase::ActorBoneBase(ComponentType type) : ActorNode(type), m_Length(0.0f), m_IsConnectedToImage(false)
{
}

float ActorBoneBase::length() const
{
	return m_Length;
}

void ActorBoneBase::length(float l)
{
	if(m_Length == l)
	{
		return;
	}
	m_Length = l;
	for(ActorNode* node : m_Children)
	{
        ActorBoneBase* bone = dynamic_cast<ActorBoneBase*>(node);
        if(bone == nullptr)
        {
            continue;
        }
		bone->x(l);
	}
}

bool ActorBoneBase::isConnectedToImage() const
{
	return m_IsConnectedToImage;
}

void ActorBoneBase::isConnectedToImage(bool isIt)
{
	m_IsConnectedToImage = isIt;
}

Vec2D ActorBoneBase::tipWorldTranslation()
{
	Mat2D transform;
	transform[4] = m_Length;

	Mat2D::multiply(transform, worldTransform(), transform);

	Vec2D result;
	result[0] = transform[4];
	result[1] = transform[5];

	return result;
}

void ActorBoneBase::tipWorldTranslation(Vec2D& result)
{
	Mat2D transform;
	transform[4] = m_Length;

	Mat2D::multiply(transform, worldTransform(), transform);
	result[0] = transform[4];
	result[1] = transform[5];
}

ActorBoneBase* ActorBoneBase::read(Actor* actor, BlockReader* reader, ActorBoneBase* node)
{
	ActorNode::read(actor, reader, node);

	node->m_Length = reader->readFloat();

	return node;
}

void ActorBoneBase::copy(ActorBoneBase* node, Actor* resetActor)
{
	ActorNode::copy(node, resetActor);
	m_Length = node->m_Length;
	m_IsConnectedToImage = node->m_IsConnectedToImage;
}
