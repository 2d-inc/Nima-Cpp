#ifndef _NIMA_ACTORANIMATION_HPP_
#define _NIMA_ACTORANIMATION_HPP_

#include <string>
#include <vector>
#include "ComponentAnimation.hpp"

namespace nima
{
	class BlockReader;
	class ActorNode;
	class ActorEvent;

	struct ActorAnimationEvent
	{
		ActorEvent* actorEvent;
		float keyFrameTime;
		float elapsedTime;

		ActorAnimationEvent(ActorEvent* av, float time, float elapsed) :
			actorEvent(av),
			keyFrameTime(time),
			elapsedTime(elapsed)
		{

		}
	};

	class ActorAnimation
	{
		private:
			std::string m_Name;
			int m_FPS;
			float m_Duration;
			bool m_IsLooping;
			ComponentAnimation* m_AnimatedComponents;
			int m_AnimatedComponentsCount;

			std::vector<ComponentAnimation*> m_TriggerComponents;

		public:

			ActorAnimation();
			~ActorAnimation();
			const std::string& name() const;
			float duration() const;
			bool isLooping() const;

			void read(BlockReader* reader, ActorComponent** components);

			void apply(float time, Actor* actor, float mix);

			void triggerEvents(ActorComponent** components, float fromTime, float toTime, std::vector<ActorAnimationEvent>& events);

	};
}
#endif