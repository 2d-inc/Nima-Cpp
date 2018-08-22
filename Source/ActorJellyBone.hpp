#ifndef _NIMA_ACTORJELLYBONE_HPP_
#define _NIMA_ACTORJELLYBONE_HPP_

#include "ActorBoneBase.hpp"

namespace nima
{
	class Actor;
	class BlockReader;

	class ActorJellyBone : public ActorBoneBase
	{
		typedef ActorBoneBase Base;

		public:
			ActorJellyBone();
			ActorComponent* makeInstance(Actor* resetActor) override;
			static ActorJellyBone* read(Actor* actor, BlockReader* reader, ActorJellyBone* node = nullptr);
	};
}
#endif