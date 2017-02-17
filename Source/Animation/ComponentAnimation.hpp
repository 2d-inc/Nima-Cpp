#ifndef _NIMA_COMPONENTANIMATION_HPP_
#define _NIMA_COMPONENTANIMATION_HPP_

#include <string>
#include "PropertyAnimation.hpp"

namespace nima
{
	class BlockReader;
	class ActorComponent;
	class Actor;
	
	class ComponentAnimation
	{
		private:
			unsigned short m_ComponentIndex;
			PropertyAnimation* m_Properties;
			int m_PropertiesCount;

		public:
			ComponentAnimation();
			~ComponentAnimation();
			int componentIndex() const;

			void read(BlockReader* reader, ActorComponent** components);
			void apply(float time, Actor* actor, float mix);

	};
}
#endif