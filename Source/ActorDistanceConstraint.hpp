#ifndef _NIMA_ACTORDISTANCECONSTRAINT_HPP_
#define _NIMA_ACTORDISTANCECONSTRAINT_HPP_

#include "ActorTargetedConstraint.hpp"

namespace nima
{
    class ActorDistanceConstraint : public ActorTargetedConstraint
    {
        typedef ActorTargetedConstraint Base;
        private:
            enum class Mode
            {
                Closer = 0,
                Further = 1,
                Exact = 2
            };
            Mode m_Mode;
            float m_Distance;

        public:
            ActorDistanceConstraint();
            void copy(ActorDistanceConstraint* node, Actor* resetActor);
            ActorComponent* makeInstance(Actor* resetActor) override;
            static ActorDistanceConstraint* read(Actor* actor, BlockReader* reader, ActorDistanceConstraint* constraint = nullptr);
            void constrain(ActorNode* node) override;
    };
}

#endif