#include "Actor.hpp"
#include "ActorBone.hpp"
#include "ActorRootBone.hpp"
#include "ActorIKTarget.hpp"
#include "BinaryReader.hpp"
#include "BlockReader.hpp"
#include "Exceptions/OverflowException.hpp"
#include <stdio.h>

using namespace nima;

Actor::Actor() : 
			m_NodeCount(0), 
			m_Nodes(NULL), 
			m_Root(new ActorNode()),
			m_MaxTextureIndex(0),
			m_ImageNodeCount(0),
			m_SolverNodeCount(0),
			m_AnimationsCount(0),
			m_ImageNodes(NULL),
			m_Solvers(NULL),
			m_Animations(NULL)
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
	delete [] m_ImageNodes;
	delete [] m_Solvers;
	delete [] m_Animations;
}

Actor* Actor::fromBytes(unsigned char* bytes, unsigned int length)
{
	BlockReader reader(bytes, length);

	unsigned char N = reader.readByte();
	unsigned char I = reader.readByte();
	unsigned char M = reader.readByte();
	unsigned char A = reader.readByte();
	unsigned int version = reader.readUnsignedInt();

	// Make sure it's a nima file.
	if(N != 78 || I != 73 || M != 77 || A != 65)
	{
		return NULL;
	}
	// And of supported version...
	if(version != 11)
	{
		return NULL;
	}

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
				actor->readAnimationsBlock(block);
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

void Actor::readAnimationsBlock(BlockReader* block)
{
	int animationCount = (int)block->readUnsignedShort();
	m_Animations = new ActorAnimation[animationCount];

	printf("NUM ANIMATIONS %i\n", animationCount);
	BlockReader* animationBlock = NULL;
	int animationIndex = 0;
	
	while((animationBlock=block->readNextBlock()) != NULL)
	{
		switch(animationBlock->blockType())
		{
			case BlockReader::Animation:
				// Sanity check.
				if(animationIndex < animationCount)
				{
					m_Animations[animationIndex].read(animationBlock, m_Nodes);
				}
				break;
			default:
				break;
		}
	};
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
			case BlockReader::ActorNode:
				node = ActorNode::read(this, nodeBlock);
				break;
			case BlockReader::ActorBone:
				node = ActorBone::read(this, nodeBlock);
				break;
			case BlockReader::ActorRootBone:
				node = ActorRootBone::read(this, nodeBlock);
				break;
			case BlockReader::ActorImage:
			{
				m_ImageNodeCount++;
				node = ActorImage::read(this, nodeBlock);
				ActorImage* imageNode = reinterpret_cast<ActorImage*>(node);
				if(imageNode->textureIndex() > m_MaxTextureIndex)
				{
					m_MaxTextureIndex = imageNode->textureIndex();
				}
				break;
			}
			case BlockReader::ActorIKTarget:
				m_SolverNodeCount++;
				node = ActorIKTarget::read(this, nodeBlock);
				break;

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

	m_ImageNodes = new ActorImage*[m_ImageNodeCount];
	m_Solvers = new Solver*[m_SolverNodeCount];

	// Resolve nodes.
	int imdIdx = 0;
	int slvIdx = 0;
	for(int i = 1; i < m_NodeCount; i++)
	{
		ActorNode* n = m_Nodes[i];
		if(n != NULL)
		{
			n->resolveNodeIndices(m_Nodes);

			switch(n->type())
			{
				case Node::Type::ActorImage:
					m_ImageNodes[imdIdx++] = reinterpret_cast<ActorImage*>(n);
					break;
				case Node::Type::ActorIKTarget:
					m_Solvers[slvIdx++] = reinterpret_cast<Solver*>(n);
					break;
				default:
					break;
			}
		}
	}
}