#include "ActorConstraint.hpp"
#include "Actor.hpp"
using namespace nima;

ActorConstraint::ActorConstraint(Actor* actor, ComponentType type) :
    ActorComponent(actor, type),
    m_IsEnabled(false),
    m_Strength(1.0f)
{

}

bool ActorConstraint::isEnabled() const
{
    return m_IsEnabled;
}

float ActorConstraint::strength() const
{
    return m_Strength;
}

void ActorConstraint::strength(float value)
{
    if(m_Strength == value)
    {
        return;
    }
    m_Strength = value;
    m_Parent->markTransformDirty();
}

void ActorConstraint::onDirty(unsigned char dirt)
{
    m_Parent->markTransformDirty();
}

void ActorConstraint::resolveComponentIndices(ActorComponent** components)
{
    Base::resolveComponentIndices(components);
    if(m_Parent != nullptr)
    {
        // This works because nodes are exported in hierarchy order, so we are assured constraints get added in order as we resolve indices.
        m_Parent->addConstraint(this);
    }
}

void ActorConstraint::copy(ActorConstraint* constraint, Actor* resetActor)
{
    Base::copy(constraint, resetActor);

    m_IsEnabled = constraint->m_IsEnabled;
    m_Strength = constraint->m_Strength;
}

ActorConstraint* ActorConstraint::read(Actor* actor, BlockReader* reader, ActorConstraint* constraint)
{
    Base::read(actor, reader, constraint);
    constraint->m_Strength = reader->readFloat();
    constraint->m_IsEnabled = reader->readByte() == 1;

    return constraint;
}