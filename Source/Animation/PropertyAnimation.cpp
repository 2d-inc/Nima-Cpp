#include "PropertyAnimation.hpp"
#include "../BlockReader.hpp"

using namespace nima;

PropertyAnimation::PropertyAnimation() :
	m_Type(PropertyTypes::Unknown)
{

}

PropertyAnimation::~PropertyAnimation()
{

}

void PropertyAnimation::read(BlockReader* reader, ActorNode* node)
{
	m_Type = (PropertyTypes)reader->readByte();
}