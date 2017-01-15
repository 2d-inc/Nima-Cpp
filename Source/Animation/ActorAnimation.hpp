#ifndef _NIMA_ACTORANIMATION_HPP_
#define _NIMA_ACTORANIMATION_HPP_

#include <string>
#include "NodeAnimation.hpp"

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
			NodeAnimation* m_AnimatedNodes;
			int m_AnimatedNodesCount;

		public:
			ActorAnimation();
			~ActorAnimation();
			const std::string& name() const;
			float duration() const;

			void read(BlockReader* reader, ActorNode** nodes);

	};
}
#endif