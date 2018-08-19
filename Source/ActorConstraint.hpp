#ifndef _NIMA_ACTORCONSTRAINT_HPP_
#define _NIMA_ACTORCONSTRAINT_HPP_

#include "ActorComponent.hpp"

namespace nima
{
    class ActorConstraint : public ActorComponent
	{
		typedef ActorComponent Base;
        protected:
            bool m_IsEnabled;
            float m_Strength;

        protected:
            ActorConstraint(Actor* actor, ComponentType type);

        public:
            bool isEnabled() const;
            float strength() const;
            void strength(float value);
            
            void onDirty(unsigned char dirt) override;
            virtual void constrain(ActorNode* node) = 0;
            void resolveComponentIndices(ActorComponent** components) override;
            void copy(ActorConstraint* constraint, Actor* resetActor);
            static ActorConstraint* read(Actor* actor, BlockReader* reader, ActorConstraint* constraint = nullptr);
    };
}

#endif