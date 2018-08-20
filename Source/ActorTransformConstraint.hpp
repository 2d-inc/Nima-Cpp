#ifndef _NIMA_ACTORTRANSFORMCONSTRAINT_HPP_
#define _NIMA_ACTORTRANSFORMCONSTRAINT_HPP_

#include "ActorTargetedConstraint.hpp"
#include "nima/Mat2D.hpp"
#include "nima/TransformComponents.hpp"
#include "TransformSpace.hpp"
#include <vector>

namespace nima
{
	class Actor;

    class ActorTransformConstraint : public ActorTargetedConstraint
	{
		typedef ActorTargetedConstraint Base;

		private:
            TransformSpace m_SourceSpace;
            TransformSpace m_DestSpace;
            TransformComponents m_ComponentsA;
            TransformComponents m_ComponentsB;


        public:
            ActorTransformConstraint();
            
            ActorComponent* makeInstance(Actor* resetActor) override;
			void copy(ActorTransformConstraint* node, Actor* resetActor);
            void constrain(ActorNode* node) override;

			static ActorTransformConstraint* read(Actor* actor, BlockReader* reader, ActorTransformConstraint* node = nullptr);
    };
}

#endif