#ifndef _NIMA_NODEANIMATION_HPP_
#define _NIMA_NODEANIMATION_HPP_

#include <string>
#include "PropertyAnimation.hpp"

namespace nima
{
	class BlockReader;
	class ActorNode;
	class Actor;
	
	class NodeAnimation
	{
		private:
			unsigned short m_NodeIndex;
			PropertyAnimation* m_Properties;
			int m_PropertiesCount;

		public:
			NodeAnimation();
			~NodeAnimation();
			int nodeIndex() const;

			void read(BlockReader* reader, ActorNode** nodes);
			void apply(float time, Actor* actor, float mix);

	};
}
#endif