#include "ActorIKConstraint.hpp"
#include "Actor.hpp"

using namespace nima;

ActorIKConstraint::ActorIKConstraint() : Base(nullptr, ComponentType::ActorIKConstraint)
{

}

ActorIKConstraint::ActorIKConstraint(ActorIKConstraint* target) : Base(nullptr, ComponentType::ActorIKConstraint)
{

}

ActorComponent* ActorIKConstraint::makeInstance(Actor* resetActor)
{
	ActorIKConstraint* instanceNode = new ActorIKConstraint();
	instanceNode->copy(this, resetActor);
	return instanceNode;
}

void ActorIKConstraint::copy(ActorIKConstraint* constraint, Actor* resetActor)
{
    Base::copy(constraint, resetActor);

    m_InvertDirection = constraint->m_InvertDirection;
    m_InfluencedBones.resize(constraint->m_InfluencedBones.size());
    for(int i = 0, length = m_InfluencedBones.size(); i < length; i++)
    {
        InfluencedBone& ib = m_InfluencedBones[i];
        ib.boneIndex = constraint->m_InfluencedBones[i].boneIndex;
    }
}

void ActorIKConstraint::resolveComponentIndices(ActorComponent** components)
{
    Base::resolveComponentIndices(components);
    if(m_Parent != nullptr)
    {
        // This works because nodes are exported in hierarchy order, so we are assured constraints get added in order as we resolve indices.
        m_Parent->addConstraint(this);
    }

    for(InfluencedBone& influenced : m_InfluencedBones)
    {
        influenced.bone = static_cast<ActorBone*>(components[influenced.boneIndex]);
    }
}

void ActorIKConstraint::completeResolve()
{
    Base::completeResolve();
    if(m_InfluencedBones.size() == 0)
    {
        return;
    }

    // Initialize solver.
    ActorBone* start = m_InfluencedBones[0].bone;
    ActorBone* end = m_InfluencedBones[m_InfluencedBones.size()-1].bone;
    int count = 0;
    while(end != nullptr && end != start->parent())
    {
        count++;
        end = dynamic_cast<ActorBone*>(end->parent());
    }

    bool allIn = count < 3;
    end = m_InfluencedBones[m_InfluencedBones.size()-1].bone;
    m_FKChain.resize(count);
    // Make sure bone data is cleared as it holds pointers to entries in the fk chain.
    m_BoneData.clear();

    int idx = count-1;
    while(end != nullptr && end != start->parent())
    {
        BoneChain& bc = m_FKChain[idx--];
        bc.bone = end;
        bc.angle = 0.0f;
        bc.included = allIn;
        bc.index = idx+1;
        end = dynamic_cast<ActorBone*>(end->parent());
    }

    // Make sure bones are good.
    for(InfluencedBone& influenced : m_InfluencedBones)
    {
        auto result = std::find_if(m_FKChain.begin(), m_FKChain.end(),
            [influenced](const BoneChain& chainItem) -> bool 
            { 
                return chainItem.bone == influenced.bone; 
            });
        if(result == m_FKChain.end())
        {
            printf("Bone not in chain %s\n", influenced.bone->name().c_str());
            continue;
        }
        // Note this indirection here, bone data and fk chain are linked and must be treated accordingly.
        m_BoneData.push_back(&(*result));
    }
    
    if(!allIn)
    {
        // Influenced bones in bone data are in the IK chain.
        for(BoneChain* bone : m_BoneData)
        {
            bone->included = true;
        }
    }
    
    // Finally mark dependencies.
    for(InfluencedBone& influenced : m_InfluencedBones)
    {
        // Don't mark dependency on parent as ActorComponent already does this.
        if(influenced.bone == m_Parent)
        {
            continue;
        }

        m_Actor->addDependency(this, influenced.bone);
    }

    if(m_Target != nullptr)
    {
        m_Actor->addDependency(this, m_Target);
    }

    // All the first level children of the influenced bones should depend on the final bone.
    BoneChain& tip = *(m_FKChain.rbegin());
    //BoneChain tip = m_FKChain[m_FKChain.Length-1];
    for(BoneChain& fk : m_FKChain)
    {
        if(&fk == &tip)
        {
            continue;
        }

        ActorBone* bone = fk.bone;
        for(ActorNode* boneChild : bone->children())
        {
            auto result = std::find_if(m_FKChain.begin(), m_FKChain.end(),
                [boneChild](const BoneChain& chainItem) -> bool 
                { 
                    return chainItem.bone == boneChild; 
                });
            
            if(result != m_FKChain.end())
            {
                // node is in the FK chain and is already dependent.
                continue;
            }
            
            m_Actor->addDependency(boneChild, tip.bone);
        }
    }
}

ActorIKConstraint* ActorIKConstraint::read(Actor* actor, BlockReader* reader, ActorIKConstraint* node)
{
    Base::read(actor, reader, node);

    return node;
}

void ActorIKConstraint::constrain(ActorNode* node)
{

}