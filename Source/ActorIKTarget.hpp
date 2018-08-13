#ifndef _NIMA_ACTORIKTARGET_HPP_
#define _NIMA_ACTORIKTARGET_HPP_

#include "ActorNode.hpp"
#include "ActorBone.hpp"

namespace nima
{
	class Actor;
	class BlockReader;
	class ActorNode;

	class ActorIKTarget : public ActorNode
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

			// bool doesInfluence(ActorBone* bone);
			// void solve1(ActorBone* b1, Vec2D& worldTargetTranslation);
			// void solve2(ActorBone* b1, ActorBone* b2, Vec2D& worldTargetTranslation, bool invert);

		public:
			ActorIKTarget();
			~ActorIKTarget();
			ActorNode* makeInstance(Actor* resetActor) override;
			void copy(ActorIKTarget* node, Actor* resetActor);

			float strength() const;
			void strength(float s);
			void resolveComponentIndices(ActorComponent** nodes) override;

			static ActorIKTarget* read(Actor* actor, BlockReader* reader, ActorIKTarget* node = NULL);
	};
}
#endif