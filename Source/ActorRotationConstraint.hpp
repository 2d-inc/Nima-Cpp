#ifndef _NIMA_ACTORROTATIONCONSTRAINT_HPP_
#define _NIMA_ACTORROTATIONCONSTRAINT_HPP_

#include "ActorTargetedConstraint.hpp"
#include "TransformSpace.hpp"
#include "nima/TransformComponents.hpp"

namespace nima
{
    class ActorRotationConstraint : public ActorTargetedConstraint
    {
        typedef ActorTargetedConstraint Base;
        private:
            bool m_Copy;
            float m_Scale;
            bool m_EnableMin;
            bool m_EnableMax;
            float m_Min;
            float m_Max;
            bool m_Offset;
            TransformSpace m_SourceSpace;
            TransformSpace m_DestSpace;
            TransformSpace m_MinMaxSpace;
            TransformComponents m_ComponentsA;
            TransformComponents m_ComponentsB;

        public:
            ActorRotationConstraint();
            void copy(ActorRotationConstraint* node, Actor* resetActor);
            ActorComponent* makeInstance(Actor* resetActor) override;
            static ActorRotationConstraint* read(Actor* actor, BlockReader* reader, ActorRotationConstraint* constraint = nullptr);
            void constrain(ActorNode* node) override;
    };
}

#endif