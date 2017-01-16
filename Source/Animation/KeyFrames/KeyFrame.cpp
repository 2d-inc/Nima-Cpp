#include "KeyFrame.hpp"
#include "../../BlockReader.hpp"

using namespace nima;

KeyFrame::KeyFrame() :
	m_Time(0.0f)
{

}

KeyFrame::~KeyFrame()
{

}

float KeyFrame::time() const
{
	return m_Time;
}

bool KeyFrame::read(BlockReader* reader)
{
	m_Time = (float)reader->readDouble();

	return true;
}

