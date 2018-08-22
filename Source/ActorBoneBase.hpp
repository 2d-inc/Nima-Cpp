#ifndef _NIMA_ACTORBONEBASE_HPP_
#define _NIMA_ACTORBONEBASE_HPP_

#include "ActorNode.hpp"
#include <nima/Vec2D.hpp>

namespace nima
{
	class Actor;
	class BlockReader;
	class ActorNode;

	class ActorBoneBase : public ActorNode
	{
		typedef ActorNode Base;
		protected:
			float m_Length;
			bool m_IsConnectedToImage;

		public:
			ActorBoneBase(ComponentType type);
			float length() const;
			void length(float l);
			bool isConnectedToImage() const;
			void isConnectedToImage(bool isIt);
			void tipWorldTranslation(Vec2D& result);
			Vec2D tipWorldTranslation();
			void copy(ActorBoneBase* node, Actor* resetActor);
			static ActorBoneBase* read(Actor* actor, BlockReader* reader, ActorBoneBase* node = NULL);
	};
}
#endif