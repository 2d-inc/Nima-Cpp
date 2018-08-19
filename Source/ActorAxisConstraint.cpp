#include "ActorAxisConstraint.hpp"
#include "Actor.hpp"
#include <cmath>

using namespace nima;

ActorAxisConstraint::ActorAxisConstraint(Actor* actor, ComponentType type) : Base(actor, type),
        m_CopyX(0.0f),
        m_CopyY(0.0f),
        m_ScaleX(1.0f),
        m_ScaleY(1.0f),
        m_EnableMinX(false),
        m_EnableMinY(false),
        m_EnableMaxX(false),
        m_EnableMaxY(false),
        m_MaxX(0.0f),
        m_MaxY(0.0f),
        m_MinX(0.0f),
        m_MinY(0.0f),
        m_Offset(false),
        m_SourceSpace(TransformSpace::World),
        m_DestSpace(TransformSpace::World),
        m_MinMaxSpace(TransformSpace::World)
{
}

void ActorAxisConstraint::copy(ActorAxisConstraint* constraint, Actor* resetActor)
{
    Base::copy(constraint, resetActor);

    m_CopyX = constraint->m_CopyX;
    m_CopyY = constraint->m_CopyY;
    m_ScaleX = constraint->m_ScaleX;
    m_ScaleY = constraint->m_ScaleY;
    m_EnableMinX = constraint->m_EnableMinX;
    m_EnableMinY = constraint->m_EnableMinY;
    m_EnableMaxX = constraint->m_EnableMaxX;
    m_EnableMaxY = constraint->m_EnableMaxY;
    m_MinX = constraint->m_MinX;
    m_MinY = constraint->m_MinY;
    m_MaxX = constraint->m_MaxX;
    m_MaxY = constraint->m_MaxY;
    m_Offset = constraint->m_Offset;
    m_SourceSpace = constraint->m_SourceSpace;
    m_DestSpace = constraint->m_DestSpace;
    m_MinMaxSpace = constraint->m_MinMaxSpace;
}

ActorAxisConstraint* ActorAxisConstraint::read(Actor* actor, BlockReader* reader, ActorAxisConstraint* constraint)
{
    Base::read(actor, reader, constraint);

    // X Axis
    if((constraint->m_CopyX = reader->readByte() == 1))
    {
        constraint->m_ScaleX = reader->readFloat();
    }
    if((constraint->m_EnableMinX = reader->readByte() == 1))
    {
        constraint->m_MinX = reader->readFloat();
    }
    if((constraint->m_EnableMaxX = reader->readByte() == 1))
    {
        constraint->m_MaxX = reader->readFloat();
    }

    // Y Axis
    if((constraint->m_CopyY = reader->readByte() == 1))
    {
        constraint->m_ScaleY = reader->readFloat();
    }
    if((constraint->m_EnableMinY = reader->readByte() == 1))
    {
        constraint->m_MinY = reader->readFloat();
    }
    if((constraint->m_EnableMaxY = reader->readByte() == 1))
    {
        constraint->m_MaxY = reader->readFloat();
    }

    constraint->m_Offset = reader->readByte() == 1;
    constraint->m_SourceSpace = (TransformSpace)reader->readByte();
    constraint->m_DestSpace = (TransformSpace)reader->readByte();
    constraint->m_MinMaxSpace = (TransformSpace)reader->readByte();

    return constraint;
}