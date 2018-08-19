#ifndef _NIMA_ACTORSCALECONSTRAINT_HPP_
#define _NIMA_ACTORSCALECONSTRAINT_HPP_

#include "ActorAxisConstraint.hpp"

namespace nima
{
    class ActorScaleConstraint : public ActorAxisConstraint
    {
        typedef ActorAxisConstraint Base;
        private:
            TransformComponents m_ComponentsA;
            TransformComponents m_ComponentsB;

        public:
            ActorScaleConstraint();
            ActorComponent* makeInstance(Actor* resetActor) override;
            static ActorScaleConstraint* read(Actor* actor, BlockReader* reader, ActorScaleConstraint* constraint = nullptr);
            void constrain(ActorNode* node) override;
    };
}

#endif