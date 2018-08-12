#include "ActorTargetedConstraint.hpp"
#include "BlockReader.hpp"
#include "Actor.hpp"

using namespace nima;

ActorTargetedConstraint::ActorTargetedConstraint(Actor* actor, ComponentType type) : Base(actor, type), m_TargetIdx(0), m_Target(nullptr)
{

}

void ActorTargetedConstraint::resolveComponentIndices(ActorComponent** components)
{
    Base::resolveComponentIndices(components);
    if(m_TargetIdx != 0)
    {
        m_Target = components[m_TargetIdx];
        if(m_Target != nullptr)
        {
            m_Actor->addDependency(m_Parent, m_Target);
        }
    }
}

void ActorTargetedConstraint::copy(ActorTargetedConstraint* constraint, Actor* resetActor)
{
    Base::copy(constraint, resetActor);

    m_TargetIdx = constraint->m_TargetIdx;
}

ActorTargetedConstraint* ActorTargetedConstraint::read(Actor* actor, BlockReader* reader, ActorTargetedConstraint* constraint)
{
    Base::read(actor, reader, constraint);
    constraint->m_TargetIdx = reader->readUnsignedShort();

    return constraint;
}