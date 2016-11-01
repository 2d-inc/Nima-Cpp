#include "ActorImage.hpp"
#include "BlockReader.hpp"

using namespace nima;

ActorImage::ActorImage() : ActorNode(Node::Type::ActorImage)
{

}
ActorNode* ActorImage::makeInstance(Actor* resetActor)
{
	ActorImage* instanceNode = new ActorImage();
	instanceNode->copy(this, resetActor);
	return instanceNode;
}

void ActorImage::copy(ActorImage* node, Actor* resetActor)
{

}

ActorImage* ActorImage::read(Actor* actor, BlockReader* reader, ActorImage* node)
{
	if(node == NULL)
	{
		node = new ActorImage();
	}

	ActorNode::read(actor, reader, node);

	bool isVisible = reader->readByte() != 0;
	if(isVisible)
	{
		node->m_BlendMode = (BlendModes)reader->readByte();
		node->m_DrawOrder = (int)reader->readUnsignedShort();
		node->m_TextureIndex = (int)reader->readByte();

		int numConnectedBones = (int)reader->readByte();
		if(numConnectedBones != 0)
		{
			node->m_BoneConnections = new BoneConnection[numConnectedBones];
			for(int i = 0; i < numConnectedBones; i++)
			{
				BoneConnection& bc = node->m_BoneConnections[i];
				bc->boneIndex = reader->readUnsignedShort();
				reader->read(bc->bind);
				Mat2D::invert(bc->ibind, bc->bind);
			}

			Mat2D worldOverride;
			reader->read(worldOverride);
			node->overrideWorldTransform(worldOverride);
		}
	}
	return node;
}