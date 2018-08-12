#ifndef _NIMA_ACTORTARGETEDCONSTRAINT_HPP_
#define _NIMA_ACTORTARGETEDCONSTRAINT_HPP_

#include "ActorConstraint.hpp"

namespace nima
{
    class ActorTargetedConstraint : public ActorConstraint
	{
		typedef ActorConstraint Base;
        protected:
            unsigned short m_TargetIdx;
            ActorComponent* m_Target;
            ActorTargetedConstraint(Actor* actor, ComponentType type);

        public:
            
            ActorComponent* target() const { return m_Target; }
            
            void resolveComponentIndices(ActorComponent** components) override;
            void copy(ActorTargetedConstraint* constraint, Actor* resetActor);
            static ActorTargetedConstraint* read(Actor* actor, BlockReader* reader, ActorTargetedConstraint* constraint = nullptr);
    };
}

#endif