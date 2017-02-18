#include "Actor.hpp"
#include "ActorBone.hpp"
#include "ActorRootBone.hpp"
#include "ActorIKTarget.hpp"
#include "ActorEvent.hpp"
#include "BinaryReader.hpp"
#include "BlockReader.hpp"
#include "Exceptions/OverflowException.hpp"
#include "Exceptions/UnsupportedVersionException.hpp"
#include "Exceptions/MissingFileException.hpp"
#include <stdio.h>
#include <algorithm>

using namespace nima;

Actor::Actor() :
	m_Flags(IsImageDrawOrderDirty|IsVertexDeformDirty),
	m_ComponentCount(0),
	m_NodeCount(0),
	m_Components(nullptr),
	m_Nodes(nullptr),
	m_Root(nullptr),
	m_MaxTextureIndex(0),
	m_ImageNodeCount(0),
	m_SolverNodeCount(0),
	m_AnimationsCount(0),
	m_ImageNodes(nullptr),
	m_Solvers(nullptr),
	m_Animations(nullptr)
{

}

Actor::~Actor()
{
	dispose();
}

void Actor::dispose()
{
	for (int i = 0; i < m_ComponentCount; i++)
	{
		delete m_Components[i];
	}
	delete [] m_Components;
	delete [] m_Nodes;
	delete [] m_ImageNodes;
	delete [] m_Solvers;
	if((m_Flags & IsInstance) != 0)
	{
		delete [] m_Animations;	
	}

	m_ComponentCount = 0;
	m_NodeCount = 0;
	m_MaxTextureIndex = 0;
	m_ImageNodeCount = 0;
	m_SolverNodeCount = 0;
	m_AnimationsCount = 0;
	m_Components = nullptr;
	m_Nodes = nullptr;
	m_ImageNodes = nullptr;
	m_Solvers = nullptr;
	m_Animations = nullptr;
	m_Root = nullptr;
}

ActorNode* Actor::root() const
{
	return m_Root;
}

ActorComponent* Actor::component(unsigned int index) const
{
	return m_Components[index];
}

ActorComponent* Actor::component(unsigned short index) const
{
	return m_Components[index];
}

ActorComponent* Actor::component(const std::string& name) const
{
	for(int i = 0; i < m_ComponentCount; i++)
	{
		ActorComponent* a = m_Components[i];
		if(a->name() == name)
		{
			return a;
		}
	}
	return nullptr;
}

ActorAnimation* Actor::animation(const std::string& name) const
{
	for(int i = 0; i < m_AnimationsCount; i++)
	{
		ActorAnimation& a = m_Animations[i];
		if(a.name() == name)
		{
			return &a;
		}
	}
	return nullptr;
}

void Actor::load(unsigned char* bytes, unsigned int length)
{
	dispose();

	BlockReader reader(bytes, length);

	unsigned char N = reader.readByte();
	unsigned char I = reader.readByte();
	unsigned char M = reader.readByte();
	unsigned char A = reader.readByte();
	unsigned int version = reader.readUnsignedInt();

	// Make sure it's a nima file.
	if (N != 78 || I != 73 || M != 77 || A != 65)
	{
		throw UnsupportedVersionException("Unsupported file version", 0, 12);
	}
	// And of supported version...
	if (version != 12)
	{
		throw UnsupportedVersionException("Unsupported file version", version, 12);
	}

	m_Root = new ActorNode();
	BlockReader* block = nullptr;
	while ((block = reader.readNextBlock()) != nullptr)
	{
		switch (block->blockType<BlockType>())
		{
			case BlockType::Components:
				readComponentsBlock(block);
				break;
			case BlockType::Animations:
				readAnimationsBlock(block);
				break;
			default:
				break;
		}
		block->close();
	}
}

void Actor::load(const std::string& filename)
{
	size_t index = filename.rfind('.');
	if (index == std::string::npos)
	{
		m_BaseFilename = filename;
	}
	else
	{
		m_BaseFilename = std::string(filename, 0, index);
	}

	FILE* fp = fopen(filename.c_str(), "rb");
	if(fp == nullptr)
	{
		throw MissingFileException("nima file is missing", filename);
	}
	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	unsigned char* bytes = new unsigned char[length];
	fread(bytes, length, 1, fp);
	fclose(fp);

	try
	{
		load(bytes, (unsigned int)length);
		delete [] bytes;
	}
	catch (OverflowException ex)
	{
		delete [] bytes;
		throw ex;
	}
}

void Actor::readAnimationsBlock(BlockReader* block)
{
	m_AnimationsCount = (int)block->readUnsignedShort();
	m_Animations = new ActorAnimation[m_AnimationsCount];

	BlockReader* animationBlock = nullptr;
	int animationIndex = 0;

	while ((animationBlock = block->readNextBlock()) != nullptr)
	{
		switch (animationBlock->blockType<BlockType>())
		{
			case BlockType::Animation:
				// Sanity check.
				if (animationIndex < m_AnimationsCount)
				{
					m_Animations[animationIndex++].read(animationBlock, m_Components);
				}
				break;
			default:
				break;
		}

		animationBlock->close();
	};
}

ActorImage* Actor::makeImageNode()
{
	return new ActorImage();
}

void Actor::readComponentsBlock(BlockReader* block)
{
	m_ComponentCount = block->readUnsignedShort() + 1;
	m_Components = new ActorComponent*[m_ComponentCount];
	m_Components[0] = m_Root;
	
	BlockReader* componentBlock = nullptr;
	int componentIndex = 1;
	m_NodeCount = 1;
	while ((componentBlock = block->readNextBlock()) != nullptr)
	{
		ActorComponent* component = nullptr;
		switch (componentBlock->blockType<BlockType>())
		{
			case BlockType::ActorNode:
				component = ActorNode::read(this, componentBlock);
				break;
			case BlockType::ActorBone:
				component = ActorBone::read(this, componentBlock);
				break;
			case BlockType::ActorRootBone:
				component = ActorRootBone::read(this, componentBlock);
				break;
			case BlockType::ActorImage:
			{
				m_ImageNodeCount++;
				component = ActorImage::read(this, componentBlock, makeImageNode());
				ActorImage* imageNode = static_cast<ActorImage*>(component);
				if (imageNode->textureIndex() > m_MaxTextureIndex)
				{
					m_MaxTextureIndex = imageNode->textureIndex();
				}
				break;
			}
			case BlockType::ActorIKTarget:
				m_SolverNodeCount++;
				component = ActorIKTarget::read(this, componentBlock);
				break;
			case BlockType::ActorEvent:
				component = ActorEvent::read(this, componentBlock);
				break;
			default:
				// Not handled/expected block.
				break;
		}
		if(component != nullptr && component->isNode())
		{
			m_NodeCount++;
		}
		m_Components[componentIndex] = component;
		componentIndex++;

		componentBlock->close();
	}

	m_Nodes = new ActorNode*[m_NodeCount];
	m_ImageNodes = new ActorImage*[m_ImageNodeCount];
	m_Solvers = new Solver*[m_SolverNodeCount];
	m_Nodes[0] = m_Root;

	// Resolve nodes.
	int imdIdx = 0;
	int slvIdx = 0;
	int ndeIdx = 1;
	for (int i = 1; i < m_ComponentCount; i++)
	{
		ActorComponent* component = m_Components[i];
		if (component != nullptr)
		{
			component->resolveComponentIndices(m_Components);

			switch (component->type())
			{
				case ComponentType::ActorImage:
					m_ImageNodes[imdIdx++] = static_cast<ActorImage*>(component);
					break;
				case ComponentType::ActorIKTarget:
					m_Solvers[slvIdx++] = static_cast<ActorIKTarget*>(component);
					break;
				default:
					break;
			}

			if(component->isNode())
			{
				m_Nodes[ndeIdx++] = static_cast<ActorNode*>(component);
			}
		}
	}
}

static bool ImageDrawOrderComparer(ActorImage* a, ActorImage* b)
{
	return a->drawOrder() < b->drawOrder();
}

static bool SolverComparer(Solver* a, Solver* b)
{
	return a->order() < b->order();
}

void Actor::copy(const Actor& actor)
{
	m_Flags = actor.m_Flags;
	m_Flags |= IsInstance;
	m_Animations = actor.m_Animations;
	m_AnimationsCount = actor.m_AnimationsCount;
	m_MaxTextureIndex = actor.m_MaxTextureIndex;
	m_ImageNodeCount = actor.m_ImageNodeCount;
	m_SolverNodeCount = actor.m_SolverNodeCount;
	m_ComponentCount = actor.m_ComponentCount;
	m_NodeCount = actor.m_NodeCount;
	m_BaseFilename = actor.m_BaseFilename;

	if (m_ComponentCount != 0)
	{
		m_Components = new ActorComponent*[m_ComponentCount];
	}
	if (m_NodeCount != 0)
	{
		m_Nodes = new ActorNode*[m_NodeCount];
	}
	if (m_ImageNodeCount != 0)
	{
		m_ImageNodes = new ActorImage*[m_ImageNodeCount];
	}
	if (m_SolverNodeCount != 0)
	{
		m_Solvers = new Solver*[m_SolverNodeCount];
	}

	if (m_ComponentCount > 0)
	{
		int idx = 0;
		int imgIdx = 0;
		int slvIdx = 0;
		int ndeIdx = 0;

		for (int i = 0; i < m_ComponentCount; i++)
		{
			ActorComponent* component = actor.m_Components[i];
			if (component == nullptr)
			{
				m_Components[idx++] = nullptr;
				continue;
			}
			ActorComponent* instanceComponent = component->makeInstance(this);
			m_Components[idx++] = instanceComponent;
			switch (instanceComponent->type())
			{
				case ComponentType::ActorImage:
					m_ImageNodes[imgIdx++] = static_cast<ActorImage*>(instanceComponent);
					break;
				case ComponentType::ActorIKTarget:
					m_Solvers[slvIdx++] = static_cast<ActorIKTarget*>(instanceComponent);
					break;
				default:
					break;
			}

			if(instanceComponent->isNode())
			{
				m_Nodes[ndeIdx++] = static_cast<ActorNode*>(instanceComponent);
			}
		}

		// Resolve indices.
		m_Root = m_Nodes[0];
		for (int i = 1; i < m_ComponentCount; i++)
		{
			ActorComponent* component = m_Components[i];
			if (component == nullptr)
			{
				continue;
			}
			component->resolveComponentIndices(m_Components);
		}

		if (m_Solvers != nullptr)
		{
			std::sort(m_Solvers, m_Solvers + m_SolverNodeCount, SolverComparer);
		}
	}
}

const int Actor::textureCount() const
{
	return m_MaxTextureIndex + 1;
}

const std::string& Actor::baseFilename() const
{
	return m_BaseFilename;
}

void Actor::markImageDrawOrderDirty()
{
	m_Flags |= IsImageDrawOrderDirty;
}

void Actor::advance(float elapsedSeconds)
{
	bool runSolvers = false;
	for(int i = 0; i < m_SolverNodeCount; i++)
	{
		Solver* solver = m_Solvers[i];
		if(solver != nullptr && solver->needsSolve())
		{
			runSolvers = true;
			break;
		}
	}

	for(int i = 0; i < m_NodeCount; i++)
	{
		ActorNode* node = m_Nodes[i];
		if(node != nullptr)
		{
			node->updateTransforms();
		}
	}

	if(runSolvers)
	{

		for(int i = 0; i < m_SolverNodeCount; i++)
		{
			Solver* solver = m_Solvers[i];
			if(solver != nullptr)
			{
				solver->solveStart();
			}
		}

		for(int i = 0; i < m_SolverNodeCount; i++)
		{
			Solver* solver = m_Solvers[i];
			if(solver != nullptr)
			{
				solver->solve();
			}
		}

		for(int i = 0; i < m_SolverNodeCount; i++)
		{
			Solver* solver = m_Solvers[i];
			if(solver != nullptr)
			{
				solver->suppressMarkDirty(true);
			}
		}

		for(int i = 0; i < m_NodeCount; i++)
		{
			ActorNode* node = m_Nodes[i];
			if(node != nullptr)
			{
				node->updateTransforms();
			}
		}

		for(int i = 0; i < m_SolverNodeCount; i++)
		{
			Solver* solver = m_Solvers[i];
			if(solver != nullptr)
			{
				solver->suppressMarkDirty(false);
			}
		}
	}

	if((m_Flags & IsImageDrawOrderDirty) != 0)
	{
		m_Flags &= ~IsImageDrawOrderDirty;

		if (m_ImageNodes != nullptr)
		{
			std::sort(m_ImageNodes, m_ImageNodes + m_ImageNodeCount, ImageDrawOrderComparer);
		}
	}
	if((m_Flags & IsVertexDeformDirty) != 0)
	{
		m_Flags &= ~IsVertexDeformDirty;
		for(int i = 0; i < m_ImageNodeCount; i++)
		{
			ActorImage* imageNode = m_ImageNodes[i];
			if(imageNode != nullptr && imageNode->isVertexDeformDirty())
			{
				imageNode->isVertexDeformDirty(false);
				updateVertexDeform(imageNode);
			}
		}
	}
}