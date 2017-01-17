#include "ActorAnimation.hpp"
#include "../BlockReader.hpp"

using namespace nima;

ActorAnimation::ActorAnimation() :
			m_FPS(60),
			m_Duration(0.0f),
			m_IsLooping(false),
			m_AnimatedNodes(nullptr),
			m_AnimatedNodesCount(0)
{

}

ActorAnimation::~ActorAnimation()
{
	delete [] m_AnimatedNodes;
}

const std::string& ActorAnimation::name() const
{
	return m_Name;
}

float ActorAnimation::duration() const
{
	return m_Duration;
}

bool ActorAnimation::isLooping() const
{
	return m_IsLooping;
}

void ActorAnimation::apply(float time, Actor* actor, float mix)
{
	for(int i = 0; i < m_AnimatedNodesCount; i++)
	{
		m_AnimatedNodes[i].apply(time, actor, mix);
	}
}

void ActorAnimation::read(BlockReader* reader, ActorNode** nodes)
{
	m_Name = reader->readString();
	m_FPS = (int)reader->readByte();
	m_Duration = reader->readFloat();
	m_IsLooping = reader->readByte() != 0;

	m_AnimatedNodesCount = (int)reader->readUnsignedShort();
	m_AnimatedNodes = new NodeAnimation[m_AnimatedNodesCount];

	for(int i = 0; i < m_AnimatedNodesCount; i++)
	{
		m_AnimatedNodes[i].read(reader, nodes);
	}
}