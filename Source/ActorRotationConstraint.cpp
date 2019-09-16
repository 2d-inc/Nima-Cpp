#include "ActorRotationConstraint.hpp"
#include "BlockReader.hpp"
#include "ActorNode.hpp"

#include <cmath>
#include <MathUtils.hpp>

using namespace nima;

ActorRotationConstraint::ActorRotationConstraint() : Base(nullptr, ComponentType::ActorRotationConstraint),
    m_Copy(false),
    m_Scale(1.0f),
    m_EnableMin(false),
    m_EnableMax(false),
    m_Min(0.0f),
    m_Max(0.0f),
    m_Offset(false),
    m_SourceSpace(TransformSpace::World),
    m_DestSpace(TransformSpace::World),
    m_MinMaxSpace(TransformSpace::World)
{

}

void ActorRotationConstraint::copy(ActorRotationConstraint* node, Actor* resetActor)
{
    Base::copy(node, resetActor);

    m_Copy = node->m_Copy;
    m_Scale = node->m_Scale;
    m_EnableMin = node->m_EnableMin;
    m_EnableMax = node->m_EnableMax;
    m_Min = node->m_Min;
    m_Max = node->m_Max;

    m_Offset = node->m_Offset;
    m_SourceSpace = node->m_SourceSpace;
    m_DestSpace = node->m_DestSpace;
    m_MinMaxSpace = node->m_MinMaxSpace;
}

ActorComponent* ActorRotationConstraint::makeInstance(Actor* resetActor)
{
    ActorRotationConstraint* instance = new ActorRotationConstraint();
    instance->copy(this, resetActor);
    return instance;
}

ActorRotationConstraint* ActorRotationConstraint::read(Actor* actor, BlockReader* reader, ActorRotationConstraint* constraint)
{
    if(constraint == nullptr)
    {
        constraint = new ActorRotationConstraint();
    }
    Base::read(actor, reader, constraint);

    if((constraint->m_Copy = reader->readByte() == 1))
    {
        constraint->m_Scale = reader->readFloat();
    }
    if((constraint->m_EnableMin = reader->readByte() == 1))
    {
        constraint->m_Min = reader->readFloat();
    }
    if((constraint->m_EnableMax = reader->readByte() == 1))
    {
        constraint->m_Max = reader->readFloat();
    }

    constraint->m_Offset = reader->readByte() == 1;
    constraint->m_SourceSpace = (TransformSpace)reader->readByte();
    constraint->m_DestSpace = (TransformSpace)reader->readByte();
    constraint->m_MinMaxSpace = (TransformSpace)reader->readByte();

    return constraint;
}

void ActorRotationConstraint::constrain(ActorNode* node)
{
    // TODO: Should ActorTargetedConstraint just store targets as nodes?
    ActorNode* target = static_cast<ActorNode*>(m_Target);
    ActorNode* grandParent = m_Parent->parent();

    const Mat2D& transformA = m_Parent->worldTransform();
    Mat2D transformB;
    Mat2D::decompose(m_ComponentsA, transformA);
    if(target == nullptr)
    {
        Mat2D::copy(transformB, transformA);
        TransformComponents::copy(m_ComponentsB, m_ComponentsA);
    }
    else
    {
        Mat2D::copy(transformB, target->worldTransform());
        if(m_SourceSpace == TransformSpace::Local)
        {
            ActorNode* sourceGrandParent = target->parent();
            if(sourceGrandParent != nullptr)
            {
                Mat2D inverse;
                if(!Mat2D::invert(inverse, sourceGrandParent->worldTransform()))
                {
                    return;
                }
                Mat2D::multiply(transformB, inverse, transformB);
            }
        }
        Mat2D::decompose(m_ComponentsB, transformB);

        if(!m_Copy)
        {
            m_ComponentsB.rotation(m_DestSpace == TransformSpace::Local ? 1.0f : m_ComponentsA.rotation());
        }
        else
        {
            m_ComponentsB.rotation(m_ComponentsB.rotation() * m_Scale);
            if(m_Offset)
            {
                m_ComponentsB.rotation(m_ComponentsB.rotation() + m_Parent->rotation());
            }
        }

        if(m_DestSpace == TransformSpace::Local)
        {
            // Destination space is in parent transform coordinates.
            // Recompose the parent local transform and get it in world, then decompose the world for interpolation.
            if(grandParent != nullptr)
            {
                Mat2D::compose(transformB, m_ComponentsB);
                Mat2D::multiply(transformB, grandParent->worldTransform(), transformB);
                Mat2D::decompose(m_ComponentsB, transformB);
            }
        }
    }
    
    bool clampLocal = m_MinMaxSpace == TransformSpace::Local && grandParent != nullptr;
    if(clampLocal)
    {
        // Apply min max in local space, so transform to local coordinates first.
        Mat2D::compose(transformB, m_ComponentsB);
        Mat2D inverse;
        if(!Mat2D::invert(inverse, grandParent->worldTransform()))
        {
            return;
        }
        Mat2D::multiply(transformB, inverse, transformB);
        Mat2D::decompose(m_ComponentsB, transformB);
    }
    if(m_EnableMax && m_ComponentsB.rotation() > m_Max)
    {
        m_ComponentsB.rotation(m_Max);	
    }
    if(m_EnableMin && m_ComponentsB.rotation() < m_Min)
    {
        m_ComponentsB.rotation(m_Min);	
    }
    if(clampLocal)
    {
        // Transform back to world.
        Mat2D::compose(transformB, m_ComponentsB);
        Mat2D::multiply(transformB, grandParent->worldTransform(), transformB);
        Mat2D::decompose(m_ComponentsB, transformB);
    }

    float angleA = std::fmod(m_ComponentsA.rotation(), piOver2);
    float angleB = std::fmod(m_ComponentsB.rotation(), piOver2);
    float diff = angleB - angleA;
    
    if(diff > pi)
    {
        diff -= static_cast<float>(piOver2);
    }
    else if(diff < -pi)
    {
        diff +=  static_cast<float>(piOver2);
    }

    m_ComponentsB.rotation(m_ComponentsA.rotation() + diff * m_Strength);
    m_ComponentsB.x(m_ComponentsA.x());
    m_ComponentsB.y(m_ComponentsA.y());
    m_ComponentsB.scaleX(m_ComponentsA.scaleX());
    m_ComponentsB.scaleY(m_ComponentsA.scaleY());
    m_ComponentsB.skew(m_ComponentsA.skew());

    Mat2D::compose(m_Parent->mutableWorldTransform(), m_ComponentsB);
}