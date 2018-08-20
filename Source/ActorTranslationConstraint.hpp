#ifndef _NIMA_ACTORTRANSLATIONCONSTRAINT_HPP_
#define _NIMA_ACTORTRANSLATIONCONSTRAINT_HPP_

#include "ActorAxisConstraint.hpp"

namespace nima
{
    class ActorTranslationConstraint : public ActorAxisConstraint
    {
        typedef ActorAxisConstraint Base;

        public:
            ActorTranslationConstraint();
            ActorComponent* makeInstance(Actor* resetActor) override;
            static ActorTranslationConstraint* read(Actor* actor, BlockReader* reader, ActorTranslationConstraint* constraint = nullptr);
            void constrain(ActorNode* node) override;
    };
}

#endif