#ifndef _NIMA_ACTORANIMATION_HPP_
#define _NIMA_ACTORANIMATION_HPP_

#include <string>
#include "ComponentAnimation.hpp"

namespace nima
{
	class BlockReader;
	class ActorNode;
	
	class ActorAnimation
	{
		private:
			std::string m_Name;
			int m_FPS;
			float m_Duration;
			bool m_IsLooping;
			ComponentAnimation* m_AnimatedComponents;
			int m_AnimatedComponentsCount;

		public:
			ActorAnimation();
			~ActorAnimation();
			const std::string& name() const;
			float duration() const;
			bool isLooping() const;

			void read(BlockReader* reader, ActorComponent** components);

			void apply(float time, Actor* actor, float mix);

	};
}
#endif