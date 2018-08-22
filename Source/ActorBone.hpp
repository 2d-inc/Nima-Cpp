#ifndef _NIMA_ACTORBONE_HPP_
#define _NIMA_ACTORBONE_HPP_

#include "ActorBoneBase.hpp"

namespace nima
{
	class Actor;
	class BlockReader;
	class JellyComponent;

	class ActorBone : public ActorBoneBase
	{
		typedef ActorBoneBase Base;
		friend class JellyComponent;
		
		protected:
			ActorBone* m_FirstBone;
			JellyComponent* m_Jelly;

		public:
			ActorBone();
			ActorComponent* makeInstance(Actor* resetActor) override;
			void completeResolve() override;
			static ActorBone* read(Actor* actor, BlockReader* reader, ActorBone* node = nullptr);
	};
}
#endif