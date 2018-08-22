#include "ActorNode.hpp"
#include "BlockReader.hpp"
#include "Actor.hpp"
#include <algorithm>
#include <cassert>
using namespace nima;

ActorNode::ActorNode(Actor* actor) : ActorNode(actor, ComponentType::ActorNode)
{

			
}

ActorNode::ActorNode(ComponentType type) : ActorNode(nullptr, type)
{

			
}

ActorNode::ActorNode(Actor* actor, ComponentType type) : 
		ActorComponent(actor, type),
		m_Rotation(0.0f),
		m_Scale(1.0f, 1.0f),
		m_Opacity(1.0f),
		m_RenderOpacity(1.0f),
		m_OverrideWorldTransform(false),
		m_IsCollapsedVisibility(false),
		m_RenderCollapsed(false)
{

}

ActorNode::ActorNode() : ActorNode(nullptr, ComponentType::ActorNode)
{

}

ActorNode::~ActorNode()
{

}

const Mat2D& ActorNode::transform()
{
	return m_Transform;
}

const Mat2D& ActorNode::worldTransform()
{
	return m_WorldTransform;
}

Mat2D& ActorNode::mutableWorldTransform()
{
	return m_WorldTransform;
}

Mat2D& ActorNode::mutableTransform()
{
	return m_Transform;
}

void ActorNode::overrideWorldTransform(const Mat2D& transform)
{
	m_OverrideWorldTransform = true;
	Mat2D::copy(m_WorldTransform, transform);
	markTransformDirty();
}

void ActorNode::clearWorldTransformOverride()
{
	if(!m_OverrideWorldTransform)
	{
		return;
	}
	m_OverrideWorldTransform = false;
	markTransformDirty();
}

const Vec2D& ActorNode::translation() const
{
	return m_Translation;
}

void ActorNode::translation(const Vec2D& v)
{
	if(m_Translation[0] == v[0] && m_Translation[1] == v[1])
	{
		return;
	}
	Vec2D::copy(m_Translation, v);
	markTransformDirty();
}

float ActorNode::x() const
{
	return m_Translation[0];
}

void ActorNode::x(float v)
{
	if(m_Translation[0] == v)
	{
		return;
	}
	m_Translation[0] = v;
	markTransformDirty();
}

float ActorNode::y() const
{
	return m_Translation[1];
}

void ActorNode::y(float v)
{
	if(m_Translation[1] == v)
	{
		return;
	}
	m_Translation[1] = v;
	markTransformDirty();
}

float ActorNode::scaleX() const
{
	return m_Scale[0];
}

void ActorNode::scaleX(float v)
{
	if(m_Scale[0] == v)
	{
		return;
	}
	m_Scale[0] = v;
	markTransformDirty();
}

float ActorNode::scaleY() const
{
	return m_Scale[1];
}

void ActorNode::scaleY(float v)
{
	if(m_Scale[1] == v)
	{
		return;
	}
	m_Scale[1] = v;
	markTransformDirty();
}

float ActorNode::rotation() const
{
	return m_Rotation;
}

void ActorNode::rotation(float v)
{
	if(m_Rotation == v)
	{
		return;
	}
	m_Rotation = v;
	markTransformDirty();
}

float ActorNode::opacity() const
{
	return m_Opacity;
}

void ActorNode::opacity(float v)
{
	if(m_Opacity == v)
	{
		return;
	}
	m_Opacity = v;
	markTransformDirty();
}

float ActorNode::renderOpacity() const
{
	return m_RenderOpacity;
}

bool ActorNode::collapsedVisibility() const
{
	return m_IsCollapsedVisibility;
}

void ActorNode::collapsedVisibility(bool v)
{
	if(m_IsCollapsedVisibility != v)
	{
		m_IsCollapsedVisibility = v;
		markTransformDirty();
	}
}

bool ActorNode::renderCollapsed() const
{
	return m_RenderCollapsed;
}

void ActorNode::markTransformDirty()
{
	if(m_Actor == nullptr)
	{
		// Still loading?
		return;
	}
	if(!m_Actor->addDirt(this, TransformDirty))
	{
		return;
	}
	m_Actor->addDirt(this, WorldTransformDirty, true);
}

Vec2D ActorNode::worldTranslation()
{
	Vec2D result;
	result[0] = m_WorldTransform[4];
	result[1] = m_WorldTransform[5];
	return result;
}

void ActorNode::worldTranslation(Vec2D& result)
{
	result[0] = m_WorldTransform[4];
	result[1] = m_WorldTransform[5];
}

void ActorNode::updateTransform()
{
	Mat2D::fromRotation(m_Transform, m_Rotation);
	m_Transform[4] = m_Translation[0];
	m_Transform[5] = m_Translation[1];
	Mat2D::scale(m_Transform, m_Transform, m_Scale);
}

void ActorNode::updateWorldTransform()
{
	m_RenderOpacity = m_Opacity;

	if(m_Parent != nullptr)
	{
		m_RenderCollapsed = (m_IsCollapsedVisibility || m_Parent->renderCollapsed());
		m_RenderOpacity *= m_Parent->renderOpacity();
		if(!m_OverrideWorldTransform)
		{
			Mat2D::multiply(m_WorldTransform, m_Parent->m_WorldTransform, m_Transform);
		}
	}
	else
	{
		Mat2D::copy(m_WorldTransform, m_Transform);
	}
}

void ActorNode::addChild(ActorNode* node)
{
	assert(node != nullptr);
	if(node->m_Parent != nullptr)
	{
		node->m_Parent->removeChild(node);
	}
	node->m_Parent = this;
	m_Children.push_back(node);
}

void ActorNode::removeChild(ActorNode* node)
{
	auto itr = std::find(m_Children.begin(), m_Children.end(), node);
	if(itr == m_Children.end())
	{
		return;
	}
	m_Children.erase(itr);
	node->m_Parent = nullptr;

}

void ActorNode::resolveComponentIndices(ActorComponent** components)
{
	Base::resolveComponentIndices(components);
}

ActorComponent* ActorNode::makeInstance(Actor* resetActor)
{
	ActorNode* instanceNode = new ActorNode();
	instanceNode->copy(this, resetActor);
	return instanceNode;
}

void ActorNode::copy(ActorNode* node, Actor* resetActor)
{
	Base::copy(node, resetActor);
	Mat2D::copy(m_Transform, node->m_Transform);
	Mat2D::copy(m_WorldTransform, node->m_WorldTransform);
	Vec2D::copy(m_Translation, node->m_Translation);
	Vec2D::copy(m_Scale, node->m_Scale);
	m_Rotation = node->m_Rotation;
	m_Opacity = node->m_Opacity;
	m_RenderOpacity = node->m_RenderOpacity;
	m_OverrideWorldTransform = node->m_OverrideWorldTransform;
}

ActorNode* ActorNode::read(Actor* actor, BlockReader* reader, ActorNode* node)
{
	if(node == nullptr)
	{
		node = new ActorNode();
	}

	Base::read(actor, reader, node);

	reader->read(node->m_Translation);
	node->m_Rotation = reader->readFloat();
	reader->read(node->m_Scale);
	node->m_Opacity = reader->readFloat();
	node->m_IsCollapsedVisibility = (reader->readByte() == 1);

	return node;
}

bool ActorNode::addConstraint(ActorConstraint* constraint)
{
	auto itr = std::find(m_Constraints.begin(), m_Constraints.end(), constraint);
	if(itr != m_Constraints.end())
	{
		return false;
	}
	m_Constraints.push_back(constraint);
	return true;
}

void ActorNode::update(unsigned char dirt)
{
	if((dirt & TransformDirty) == TransformDirty)
	{
		updateTransform();
	}
	if((dirt & WorldTransformDirty) == WorldTransformDirty)
	{
		updateWorldTransform();
		for(auto constraint : m_Constraints)
		{
			if(constraint->isEnabled())
			{
				constraint->constrain(this);
			}
		}
		// if(m_Constraints != nullptr)
		// {
		// 	foreach(ActorConstraint constraint in m_Constraints)
		// 	{
		// 		if(constraint.IsEnabled)
		// 		{
		// 			constraint.Constrain(this);
		// 		}
		// 	}
		// }
	}
}