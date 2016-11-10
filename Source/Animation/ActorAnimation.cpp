#include "ActorAnimation.hpp"
#include "../BlockReader.hpp"

using namespace nima;

const std::string& ActorAnimation::name() const
{
	return m_Name;
}

float ActorAnimation::duration() const
{
	return m_Duration;
}

ActorAnimation* ActorAnimation::read(BlockReader* reader, ActorNode** nodes)
{
	ActorAnimation* animation = new ActorAnimation();
	animation->m_Name = reader->readString();
	animation->m_FPS = (int)reader->readByte();
	animation->m_Duration = reader->readFloat();
	animation->m_IsLooping = reader->readByte() != 0;

	//int numKeyedNodes = (int)reader->readUnsignedShort();
	return animation;
}