#include "BlockReader.hpp"
#include "Exceptions/OverflowException.hpp"

using namespace nima;


BlockReader::BlockReader(unsigned char* data, unsigned int length) : BinaryReader(data, length, BinaryReader::LittleEndian)
{

}

BlockReader::BlockReader(BlockTypes type, unsigned char* data, unsigned int length) : BinaryReader(data, length, BinaryReader::LittleEndian), m_BlockType(type)
{
}

BlockReader* BlockReader::readNextBlock()
{
	if(m_DataPosition == m_DataLength)
	{
		return NULL;
	}
	unsigned char blockType = readByte();
	unsigned int length = readUnsignedInt();

	if(m_DataPosition + length > m_DataLength)
	{
		throw OverflowException("Block length is invalid and would cause overflow in BlockReader::readNextBlock.");
	}
	unsigned char* blockData = m_Data + m_DataPosition;

	m_DataPosition += length;
	return new BlockReader((BlockTypes)blockType, blockData, length);
}