#ifndef _NIMA_ACTORAXISCONSTRAINT_HPP_
#define _NIMA_ACTORAXISCONSTRAINT_HPP_

#include "ActorTargetedConstraint.hpp"
#include "ActorBone.hpp"
#include "TransformSpace.hpp"
#include "nima/Mat2D.hpp"
#include "nima/TransformComponents.hpp"
#include <vector>

namespace nima
{
	class Actor;

    class ActorAxisConstraint : public ActorTargetedConstraint
	{
        typedef ActorTargetedConstraint Base;

		protected:
			bool m_CopyX;
            bool m_CopyY;
            float m_ScaleX;
            float m_ScaleY;
            bool m_EnableMinX;
            bool m_EnableMinY;
            bool m_EnableMaxX;
            bool m_EnableMaxY;
            float m_MaxX;
            float m_MaxY;
            float m_MinX;
            float m_MinY;
            bool m_Offset;
            TransformSpace m_SourceSpace;
            TransformSpace m_DestSpace;
            TransformSpace m_MinMaxSpace;

        public:
            ActorAxisConstraint(Actor* actor, ComponentType type);
			void copy(ActorAxisConstraint* node, Actor* resetActor);

			static ActorAxisConstraint* read(Actor* actor, BlockReader* reader, ActorAxisConstraint* node);
    };
}

#endif