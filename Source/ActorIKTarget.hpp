#ifndef _NIMA_ACTORIKTARGET_HPP_
#define _NIMA_ACTORIKTARGET_HPP_

#include "ActorNode.hpp"
#include "ActorBone.hpp"
#include "Solver.hpp"

namespace nima
{
	class Actor;
	class BlockReader;
	class ActorNode;

	class ActorIKTarget : public ActorNode, public Solver
	{
		typedef ActorNode Base;
		public:
			struct InfluencedBone
			{
				unsigned short boneIndex;
				ActorBone* bone;

				InfluencedBone();
			};
		private:
			int m_NumInfluencedBones;
			InfluencedBone* m_InfluencedBones;
			bool m_InvertDirection;
			float m_Strength;
			int m_Order;

			ActorBone* m_Bone1;
			ActorBone* m_Bone1Child;
			ActorBone* m_Bone2;

			struct BoneChain
			{
				ActorBone* bone;
				float angle;
				bool included;
			};

			int m_ChainLength;
			BoneChain* m_Chain;
			bool doesInfluence(ActorBone* bone);
			void solve1(ActorBone* b1, Vec2D& worldTargetTranslation);
			void solve2(ActorBone* b1, ActorBone* b2, Vec2D& worldTargetTranslation, bool invert);

		public:
			ActorIKTarget();
			~ActorIKTarget();
			ActorNode* makeInstance(Actor* resetActor);
			void copy(ActorIKTarget* node, Actor* resetActor);

			int order();
			bool needsSolve();
			bool suppressMarkDirty();
			void suppressMarkDirty(bool suppressIt);
			void solveStart();
			void solve();
			float strength();
			void strength(float s);
			void resolveNodeIndices(ActorNode** nodes);

			static ActorIKTarget* read(Actor* actor, BlockReader* reader, ActorIKTarget* node = NULL);
	};
}
#endif