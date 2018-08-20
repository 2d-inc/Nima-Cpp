#ifndef _NIMA_ACTORIKCONSTRAINT_HPP_
#define _NIMA_ACTORIKCONSTRAINT_HPP_

#include "ActorTargetedConstraint.hpp"
#include "ActorBone.hpp"
#include "nima/Mat2D.hpp"
#include "nima/TransformComponents.hpp"
#include <vector>

namespace nima
{
	class Actor;

    class ActorIKConstraint : public ActorTargetedConstraint
	{
			typedef ActorTargetedConstraint Base;
		public:
			struct InfluencedBone
			{
				unsigned short boneIndex;
				ActorBone* bone;

				InfluencedBone();
			};

            struct BoneChain
            {
                int index;
                ActorBone* bone;
                float angle;
                bool included;
                TransformComponents transformComponents;
                Mat2D parentWorldInverse;
            };

		private:
			std::vector<InfluencedBone> m_InfluencedBones;
            std::vector<BoneChain> m_FKChain;
            std::vector<BoneChain*> m_BoneData;
			bool m_InvertDirection;

            void solve1(BoneChain* fk1, const Vec2D& worldTargetTranslation);
            void solve2(BoneChain* fk1, BoneChain* fk2, const Vec2D& worldTargetTranslation);
            void constrainRotation(BoneChain* fk, float rotation);

        public:
            ActorIKConstraint();
            ActorIKConstraint(ActorIKConstraint* target); // Support old system.
            
            ActorComponent* makeInstance(Actor* resetActor) override;
			void copy(ActorIKConstraint* node, Actor* resetActor);
			void resolveComponentIndices(ActorComponent** nodes) override;
            void completeResolve() override;
            void constrain(ActorNode* node) override;

			static ActorIKConstraint* read(Actor* actor, BlockReader* reader, ActorIKConstraint* node = nullptr);
    };
}

#endif