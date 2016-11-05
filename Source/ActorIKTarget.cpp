#include "ActorIKTarget.hpp"
#include "BlockReader.hpp"

using namespace nima;

ActorIKTarget::InfluencedBone::InfluencedBone() : boneIndex(0), bone(NULL)
{

}

ActorIKTarget::ActorIKTarget() :
		ActorNode(Node::Type::ActorIKTarget),

		m_NumInfluencedBones(0),
		m_InfluencedBones(NULL),
		m_InvertDirection(false),
		m_Strength(0.0f),
		m_Order(0),
		m_Bone1(NULL),
		m_Bone1Child(NULL),
		m_Bone2(NULL),
		m_Chain(NULL)
{

}

ActorIKTarget::~ActorIKTarget()
{
	delete m_InfluencedBones;
	delete m_Chain;
}

ActorNode* ActorIKTarget::makeInstance(Actor* resetActor)
{
	ActorIKTarget* instanceNode = new ActorIKTarget();
	instanceNode->copy(this, resetActor);
	return instanceNode;
}

void ActorIKTarget::copy(ActorIKTarget* node, Actor* resetActor)
{
	Base::copy(node, resetActor);

	m_Order = node->m_Order;
	m_InvertDirection = node->m_InvertDirection;
	m_Strength = node->m_Strength;
	m_NumInfluencedBones = node->m_NumInfluencedBones;
	m_InfluencedBones = new InfluencedBone[m_NumInfluencedBones];
	for(int i = 0; i < m_NumInfluencedBones; i++)
	{
		InfluencedBone& ib = m_InfluencedBones[i];
		ib.boneIndex = node->m_InfluencedBones[i].boneIndex;
	}
}

ActorIKTarget* ActorIKTarget::read(Actor* actor, BlockReader* reader, ActorIKTarget* node)
{
	if(node == NULL)
	{
		node = new ActorIKTarget();
	}

	Base::read(actor, reader, node);

	node->m_Order = reader->readUnsignedShort();
	node->m_Strength = reader->readFloat();
	node->m_InvertDirection = reader->readByte() == 1;	

	node->m_NumInfluencedBones = (int)reader->readByte();
	if(node->m_NumInfluencedBones > 0)
	{
		node->m_InfluencedBones = new InfluencedBone[node->m_NumInfluencedBones];
		for(int i = 0; i < node->m_NumInfluencedBones; i++)
		{
			InfluencedBone& ib = node->m_InfluencedBones[i];
			ib.boneIndex = reader->readUnsignedShort();
		}
	}

	return node;
}

void ActorIKTarget::resolveNodeIndices(ActorNode** nodes)
{
	Base::resolveNodeIndices(nodes);
	if(m_InfluencedBones != NULL)
	{
		for(int i = 0; i < m_NumInfluencedBones; i++)
		{
			InfluencedBone& ib = m_InfluencedBones[i];
			ib.bone = reinterpret_cast<ActorBone*>(nodes[ib.boneIndex]);
			ib.bone->addDependent(this);
		}

		m_Bone1 = m_InfluencedBones[0].bone;
		m_Bone2 = m_InfluencedBones[m_NumInfluencedBones-1].bone;
		ActorBone* b1c = m_Bone2;
		ActorBone* b1 = m_Bone1;
		while(b1c != NULL && b1c->parent() != b1)
		{
			ActorNode* n = b1c->parent();
			if(n != NULL && n->type() == Node::Type::ActorBone)
			{
				b1c = reinterpret_cast<ActorBone*>(n);
			}
			else
			{
				b1c = NULL;
			}
		}
		m_Bone1Child = b1c;

		int chainCount = 0;
		ActorNode* end = m_Bone2;
		while(end != NULL && end != b1->parent())
		{
			chainCount++;

			ActorNode* n = end->parent();
			if(n != NULL && n->type() == Node::Type::ActorBone)
			{
				end = n;
			}
			else
			{
				end = NULL;
			}
		}

		m_Chain = new BoneChain[chainCount];
		end = m_Bone2;
		int chainIndex = 0;
		while(end != NULL && end != b1->parent())
		{
			BoneChain& bc = m_Chain[chainIndex];
			bc.bone = reinterpret_cast<ActorBone*>(end);
			ActorNode* n = end->parent();
			if(n != NULL && n->type() == Node::Type::ActorBone)
			{
				end = n;
			}
			else
			{
				end = NULL;
			}

			bc.included = doesInfluence(bc.bone) || doesInfluence(reinterpret_cast<ActorBone*>(end)); // end is either null or an actorbone (for sure) here.
			bc.angle = 0.0f;
		}
	}
}

bool ActorIKTarget::doesInfluence(ActorBone* bone)
{
	if(bone == NULL)
	{
		return false;
	}
	for(int i = 0; i < m_NumInfluencedBones; i++)
	{
		if(m_InfluencedBones[i].bone == bone)
		{
			return true;
		}
	}
	return false;
}

int ActorIKTarget::order()
{
	return m_Order;
}

bool ActorIKTarget::needsSolve()
{
	return isWorldDirty() || isDirty();
}

float ActorIKTarget::strength()
{
	return m_Strength;
}

void ActorIKTarget::strength(float s)
{
	if(m_Strength != s)
	{
		m_Strength = s;
		markDirty();
	}
}

bool ActorIKTarget::suppressMarkDirty()
{
	return Base::suppressMarkDirty();
}

void ActorIKTarget::suppressMarkDirty(bool suppressIt)
{
	Base::suppressMarkDirty(suppressIt);
}

void ActorIKTarget::solveStart()
{

}

void ActorIKTarget::solve()
{

}