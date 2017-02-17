#include "ActorComponent.hpp"
#include "ActorNode.hpp"
#include "BlockReader.hpp"
#include <algorithm>
#include <cassert>
using namespace nima;

ActorComponent::ActorComponent(Actor* actor, ComponentType type) : 
			m_Type(type),
			m_Parent(nullptr),
			m_Actor(actor),
			m_ParentIdx(0),
			m_Idx(0)
{

}

ActorComponent::~ActorComponent()
{

}

Actor* ActorComponent::actor() const
{
	return m_Actor;
}

const std::string& ActorComponent::name() const
{
	return m_Name;
}

ComponentType ActorComponent::type() const
{
	return m_Type;
}

ActorNode* ActorComponent::parent() const
{
	return m_Parent;	
}

unsigned short ActorComponent::parentIdx() const
{
	return m_ParentIdx;
}

unsigned short ActorComponent::idx() const
{
		return m_Idx;
}

void ActorComponent::resolveComponentIndices(ActorComponent** components)
{
	ActorComponent* component = components[m_ParentIdx];
	if(component != nullptr && component->isNode())
	{
		m_Parent = static_cast<ActorNode*>(component);
		if(this->isNode())
		{
			m_Parent->addChild(static_cast<ActorNode*>(this));
		}
	}
}

void ActorComponent::copy(ActorComponent* component, Actor* resetActor)
{
	m_Name = component->m_Name;
	m_Actor = resetActor;
	m_ParentIdx = component->m_ParentIdx;
	m_Idx = component->m_Idx;
}

ActorComponent* ActorComponent::read(Actor* actor, BlockReader* reader, ActorComponent* component)
{
	component->m_Actor = actor;
	component->m_Name = reader->readString();
	component->m_ParentIdx = reader->readUnsignedShort();

	return component;
}