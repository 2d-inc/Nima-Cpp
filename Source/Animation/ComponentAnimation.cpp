#include "ComponentAnimation.hpp"
#include "../Actor.hpp"
#include "../BlockReader.hpp"

using namespace nima;

ComponentAnimation::ComponentAnimation() :
	m_Properties(NULL),
	m_PropertiesCount(0)
{

}

ComponentAnimation::~ComponentAnimation()
{
	delete [] m_Properties;
}

int ComponentAnimation::componentIndex() const
{
	return m_ComponentIndex;
}

void ComponentAnimation::apply(float time, Actor* actor, float mix)
{
	ActorComponent* component = actor->component(m_ComponentIndex);
	for (int i = 0; i < m_PropertiesCount; i++)
	{
		m_Properties[i].apply(time, component, mix);
	}
}

void ComponentAnimation::read(BlockReader* reader, ActorComponent** components)
{
	m_ComponentIndex = reader->readUnsignedShort();
	m_PropertiesCount = (int)reader->readUnsignedShort();
	m_Properties = new PropertyAnimation[m_PropertiesCount];
	ActorComponent* component = components[m_ComponentIndex];
	for (int i = 0; i < m_PropertiesCount; i++)
	{
		m_Properties[i].read(reader, component);
	}
}