#include "Actor.hpp"
#include "BinaryReader.hpp"
#include "BlockReader.hpp"
#include "Exceptions/OverflowException.hpp"
#include <stdio.h>

using namespace nima;

Actor::Actor() : m_NodeCount(0), m_Nodes(NULL), m_Root(new ActorNode())
{

}

Actor::~Actor()
{
	delete m_Root;
	for(int i = 1; i < m_NodeCount; i++)
	{
		delete m_Nodes[i];	
	}
	delete [] m_Nodes;
}

Actor* Actor::fromBytes(unsigned char* bytes, unsigned int length)
{
	BlockReader reader(bytes, length);

	unsigned char N = reader.readByte();
	unsigned char I = reader.readByte();
	unsigned char M = reader.readByte();
	unsigned char A = reader.readByte();
	unsigned int version = reader.readUnsignedInt();

	if(N != 78 || I != 73 || M != 77 || A != 65)
	{
		printf("NOT A NIMA FILE\n");
		return NULL;
	}
	if(version != 11)
	{
		printf("NOT THE RIGHT VERSION\n");
		return NULL;
	}
	printf("OK.\n");

	Actor* actor = new Actor();
	BlockReader* block = NULL;
	while((block = reader.readNextBlock()) != NULL)
	{
		switch(block->blockType())
		{
			case BlockReader::Nodes:
				actor->readNodesBlock(block);
				break;
			case BlockReader::Animations:
				printf("GOT ANIMATIONS\n");
				break;
			default:
				break;
		}
		delete block;
	}

	return actor;
}

Actor* Actor::fromFile(const char* filename)
{
	FILE* fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	unsigned char* bytes = new unsigned char[length];
	fread(bytes, length, 1, fp);
	fclose(fp);
	
	try
	{
		Actor* actor = Actor::fromBytes(bytes, (unsigned int)length);	
		delete [] bytes;
		return actor;
	}
	catch(OverflowException ex)
	{
		delete [] bytes;
		throw ex;
	}
}

void Actor::readNodesBlock(BlockReader* block)
{
	m_NodeCount = block->readUnsignedShort()+1;
	m_Nodes = new ActorNode*[m_NodeCount];
	m_Nodes[0] = m_Root;
	printf("NUM NODES %i\n", m_NodeCount);
	BlockReader* nodeBlock = NULL;
	int nodeIndex = 1;
	while((nodeBlock=block->readNextBlock()) != NULL)
	{
		ActorNode* node = NULL;
		switch(nodeBlock->blockType())
		{
			default:
				// Name is first thing in each block.
				{
					std::string name = nodeBlock->readString();
					printf("NAME IS %s\n", name.c_str());
				}
				break;
		}
		m_Nodes[nodeIndex] = node;
		nodeIndex++;
	}
}