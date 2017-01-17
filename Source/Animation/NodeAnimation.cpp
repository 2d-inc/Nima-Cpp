#include "NodeAnimation.hpp"
#include "../Actor.hpp"
#include "../BlockReader.hpp"

using namespace nima;

NodeAnimation::NodeAnimation() :
	m_Properties(NULL),
	m_PropertiesCount(0)
{

}

NodeAnimation::~NodeAnimation()
{
	delete [] m_Properties;
}

int NodeAnimation::nodeIndex() const
{
	return m_NodeIndex;
}

void NodeAnimation::apply(float time, Actor* actor, float mix)
{
	ActorNode* node = actor->getNode(m_NodeIndex);
	for (int i = 0; i < m_PropertiesCount; i++)
	{
		m_Properties[i].apply(time, node, mix);
	}
}

void NodeAnimation::read(BlockReader* reader, ActorNode** nodes)
{
	m_NodeIndex = reader->readUnsignedShort();
	m_PropertiesCount = (int)reader->readUnsignedShort();
	m_Properties = new PropertyAnimation[m_PropertiesCount];
	ActorNode* node = nodes[m_NodeIndex];
	for (int i = 0; i < m_PropertiesCount; i++)
	{
		m_Properties[i].read(reader, node);
	}
}