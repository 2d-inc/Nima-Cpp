#include "KeyFrame.hpp"
#include "../BlockReader.hpp"

using namespace nima;

float KeyFrame::time() const
{
	return m_Time;
}

bool KeyFrame::read(BlockReader* reader, KeyFrame* frame)
{
	frame->m_Time = (float)reader->readDouble();
	return true;
}